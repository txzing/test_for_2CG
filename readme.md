# 镜像分布
fsbl+elf=update镜像
```
golden      fsbl     elf
0-8fffff  | 900000 | 1200000
8d58a0      80a580   15ee78     32MB
```

# flash容量如果大于16MB，制作bit文件应该开启 32 位寻址模式, 寻址最大到 256 MB
```
set_property BITSTREAM.CONFIG.SPI_32BIT_ADDR Yes [current_design]
```
其他约束参考ug908

# fsbl
这里如果读取elf出错就跳回0地址

# update镜像 tips
write_cfgmem产生的镜像从0开始的空区域(gap)填充了FF，需要把 golden 区的gap去掉
```
dd if=BOOT.bin bs=1 skip=9437184 of=output.bin
```
这个就是可以直接网络升级的update镜像，这里总体展示从0x00900000开始烧写

# 后续改进
需要做命令单独升级golden区，eeprom要记录update区起始地址，flash型号容量也要记录

# 简化分支的输出
启动时候启动 golden 镜像，没有 fallback 状态， 就启动 update 镜像

update 镜像主动触发跳转，成功再次启动 golden 镜像

update 镜像跳转之前给一个很小的timer值，这样跳回 golden 镜像之后才能个 fallback 状态
```

***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00000001
isFallbacked = 0


***************************
this is update image

Jul 11 2024, UTC 05:37:51
hardware ver = 0x00000003
software ver = 0x24071113
***************************


***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00000D03
isFallbacked = 1

```

如果用二进制编辑器比如uex编辑update镜像，修改一些数值，能触发crc错误，打印信息如下
```
***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00000001
isFallbacked = 0


***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00002503
isFallbacked = 1

```

# fsbl 问题修改

由于flash大于16MB，所以进入了4BAddrMode，转跳之前要退出4BAddrMode，否则就不能跳回0地址

打印符合预期
```
***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00000001
isFallbacked = 0

SPI ELF Bootloader
Copying ELF image from SPI flash @ 0x01100000 to RAM
 sizeof(hdr) = 00000034
Invalid ELF header

***************************
this is golden image

Jul 11 2024, UTC 04:48:37
hardware ver = 0x00000003
software ver = 0x24071112
***************************
StsCode = 0x00000D03
isFallbacked = 1

```

# 可靠性实验
已知 break_update_bistream.sh 进行破坏的情况不能启动

## POR
```
StsCode = 0x00000001
isFallbacked = 0
StsCode = 0x00000105
isFallbacked = 0
StsCode = 0x00000505
isFallbacked = 0
StsCode = 0x00000505
isFallbacked = 0
StsCode = 0x00000505
isFallbacked = 0
StsCode = 0x00000505
isFallbacked = 0

```
这个情况可以在 0x01400000 写入一个 timer2.bin 的 barrier Image

另外 写入 update_broken.bin 或者在 elf 末尾加 barrier Image 会出现跳转后无法 fallback 的 情况

## reset_pl
```
StsCode = 0x00000305
isFallbacked = 0
```
没有继续打印了

## POR
```
StsCode = 0x00000001
isFallbacked = 0
```
没有继续打印了


## 针对实在没有 fallback 跳转的情况，应交互方式强制进入golden镜像
这里定义启动时按空格键, 强制进入, 这样就可以再进行烧写。不再需要在第三个地址写 barrier Image

## 指示灯
需要 pl load 指示灯。在bootloader阶段如果断电，再上电会启动很久(1min左右), 再断电上电可以正常。PL指示灯借外壳可以在长时间等待不想等的情况下手动复位。
需要 网络建立的指示灯。网络初始化还是要几秒到十几秒，有效情况下才进行上位机操作。




