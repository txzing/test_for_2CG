#!/bin/bash
#cd output
source /opt/Xilinx/Vitis/2020.1/settings64.sh
dd if=/dev/zero of=DUMMYBOOT.bin bs=1MiB count=32
program_flash -f DUMMYBOOT.bin -offset 0 -flash_type mt25ql256-spi-x1_x2_x4 -erase_only -cable type xilinx_tcf
#program_flash -f DUMMYBOOT.bin -offset 0x00800000 -flash_type mt25ql256-spi-x1_x2_x4 -erase_only -cable type xilinx_tcf
rm DUMMYBOOT.bin