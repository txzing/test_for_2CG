#include "bsp.h"


#if defined (PLATFORM_ZYNQMP) || defined (PLATFORM_ZYNQ)
	#define UART_BASEADDR XPAR_XUARTPS_0_BASEADDR
#else
	#define UART_BASEADDR XPAR_UARTLITE_0_BASEADDR
#endif // PLATFORM_ZYNQMP || PLATFORM_ZYNQ

u32 ret32;
u8 ret8;
u8 UserInput;
u8 cerrent_ch;
u8 lock_status = 0;
u8 reconfig_flag_0 = 0;
u8 clear_flag_0 = 0;
u8 reconfig_flag_1 = 0;
u8 clear_flag_1 = 0;

void app_info(void)
{
	xil_printf("----------------------\r\n");
	xil_printf("\r\n%s, UTC %s\r\n",__DATE__,__TIME__);
	xil_printf("----------------------\r\n");
	print("input :\n\r");
	xil_printf("d - detect info\r\n");
	xil_printf("c - clear screen\r\n");
#ifdef XPAR_XAXIS_SWITCH_NUM_INSTANCES
	xil_printf("s - switch video source\r\n");
#endif
	xil_printf("----------------------\r\n");
	xil_printf("\r\n");
}

void video_resolution_print(char *info,u32 baseaddr)
{
	xil_printf("-%s freq: %d -\r\n", info, Xil_In32(baseaddr + 0x8));
	xil_printf("-%s res: %dx%d -\r\n", info, Xil_In32(baseaddr + 0x0), Xil_In32(baseaddr + 0x4));
}



u8 uart_RecvByte(UINTPTR BaseAddress)
{
#if defined (PLATFORM_ZYNQMP) || defined (PLATFORM_ZYNQ)
	return XUartPs_RecvByte(BaseAddress);
#else
	return XUartLite_RecvByte(BaseAddress);
#endif // PLATFORM_ZYNQMP || PLATFORM_ZYNQ
}


void uart_receive_process(void)
{

#if defined (PLATFORM_ZYNQMP) || defined (PLATFORM_ZYNQ)
	while(XUartPs_IsReceiveData(UART_BASEADDR))
	{
#else
	if (!XUartLite_IsReceiveEmpty(UART_BASEADDR))
	{
#endif // PLATFORM_ZYNQMP || PLATFORM_ZYNQ

		// Read data from uart
		UserInput = uart_RecvByte(UART_BASEADDR);
		if((UserInput == 'm') || (UserInput == 'M'))
		{
			app_info();
		}
		else if((UserInput == 'd') || (UserInput == 'D'))
		{

			xil_printf("\r\n!!!!!!!!!!!!!!!!!!!!!\r\n");
			xil_printf("------------------------\r\n");
			video_resolution_print("csi_0 in",XPAR_CSI_RX_0_AXIS_PASSTHROUGH_MON_0_S00_AXI_BASEADDR);
			video_resolution_print("csi_0 vpss out",XPAR_CSI_RX_0_AXIS_PASSTHROUGH_MON_1_S00_AXI_BASEADDR);
			video_resolution_print("csi_1 vpss out",XPAR_CSI_RX_1_AXIS_PASSTHROUGH_MON_0_S00_AXI_BASEADDR);
			video_resolution_print("osd out, vdma in",XPAR_MEMORY_SUBSYSTEM_AXIS_PASSTHROUGH_MON_0_S00_AXI_BASEADDR);
			video_resolution_print("video out",XPAR_VIDEO_OUT_AXIS_PASSTHROUGH_MON_0_S00_AXI_BASEADDR);
			xil_printf("------------------------\r\n");
		}
		else if((UserInput == 'k') || (UserInput == 'K'))
		{

			xil_printf("------------test RELAY_CUTOFF------------\r\n");
			XGpioPs_WritePin(&Gpio, RELAY_CUTOFF, 1) ; // RELAY_CUTOFF: 0-keep; 1-cutoff

		}

		else if((UserInput == 'c') || (UserInput == 'C'))
		{

			xil_printf("------------clear vdma start------------\r\n");
			clear_vdma_0();
		}
		else if((UserInput == 'f') || (UserInput == 'F'))
		{

			xil_printf("------------detect info------------\r\n");

			ret32 = xgpio_i2c_reg16_read(I2C_NO_1, 0x50>>1, 0x0013, &ret8, STRETCH_ON);
			xil_printf("0x0013: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_1, 0x50>>1, 0x01fc, &ret8, STRETCH_ON);
			xil_printf("0x01fc: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_1, 0x50>>1, 0x021c, &ret8, STRETCH_ON);
			xil_printf("0x021c: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_1, 0x50>>1, 0x011A, &ret8, STRETCH_ON);
			xil_printf("0x011A: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_1, 0x50>>1, 0x012C, &ret8, STRETCH_ON);
			xil_printf("0x012C: 0x%02x\r\n",ret8);

			xil_printf("------------------------\r\n");

			ret32 = xgpio_i2c_reg16_read(I2C_NO_2, 0x50>>1, 0x0013, &ret8, STRETCH_ON);
			xil_printf("0x0013: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_2, 0x50>>1, 0x01fc, &ret8, STRETCH_ON);
			xil_printf("0x01fc: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_2, 0x50>>1, 0x021c, &ret8, STRETCH_ON);
			xil_printf("0x021c: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_2, 0x50>>1, 0x011A, &ret8, STRETCH_ON);
			xil_printf("0x011A: 0x%02x\r\n",ret8);
			ret32 = xgpio_i2c_reg16_read(I2C_NO_2, 0x50>>1, 0x012C, &ret8, STRETCH_ON);
			xil_printf("0x012C: 0x%02x\r\n",ret8);
		}

#if 1
		else if((UserInput == 's') || (UserInput == 'S'))
		{
			xil_printf("switch video source\r\n");
			xil_printf("1 - channel 1\r\n");
			xil_printf("2 - channel 2\r\n");
			xil_printf("3 - tpg\r\n");

			UserInput = uart_RecvByte(UART_BASEADDR);

			xil_printf("------------------------\r\n");
			if(UserInput == '1')
			{
				AxisSwitch(XPAR_AXIS_SWITCH_0_DEVICE_ID, &AxisSwitch0, 0, 0); //stream
//				AxisSwitch(XPAR_AXIS_SWITCH_1_DEVICE_ID, &AxisSwitch1, 0, 0);
				xil_printf("------------switch to channel 1-----------\r\n");
			}
			else if(UserInput == '2')
			{
//				AxisSwitch(XPAR_AXIS_SWITCH_1_DEVICE_ID, &AxisSwitch1, 1, 0);
			    clear_vdma_0();
			    xil_printf("------------switch to channel 2-----------\r\n");
			}
			else if(UserInput == '3')
			{
			    AxisSwitch(XPAR_AXIS_SWITCH_0_DEVICE_ID, &AxisSwitch0, 1, 0);
//				AxisSwitch(XPAR_AXIS_SWITCH_1_DEVICE_ID, &AxisSwitch1, 0, 0);
			    clear_vdma_0();
			    xil_printf("------------switch to tpg-----------\r\n");
			}
			else if(UserInput == '4')
			{
			    AxisSwitch(XPAR_AXIS_SWITCH_0_DEVICE_ID, &AxisSwitch0, 0, 1);
//			    AxisSwitch(XPAR_AXIS_SWITCH_1_DEVICE_ID, &AxisSwitch1, 0, 0);
			    clear_vdma_0();
			    xil_printf("------------switch to terminate-----------\r\n");
			}
			else if(UserInput == '5')
			{
			    AxisSwitch(XPAR_AXIS_SWITCH_0_DEVICE_ID, &AxisSwitch0, 1, 0);

			    clear_vdma_0();
			    xil_printf("------------switch to terminate-----------\r\n");
			}
			else
			{
				xil_printf("\r input data error \n!!!!!!!!!!!!!");
			}

			xil_printf("------------------------\r\n");
		}
#endif
/****************************************************************************/
/****************************************************************************/

	}
}


void max96792_lock_detect(u8 ch)
{

	u8 reg_0x0013 = 0;
	u8 reg_0x01fc = 0;
	u8 reg_0x011a = 0;
	ret8 = 0;
	xgpio_i2c_reg16_read(ch, 0x28, 0x0013, &ret8, STRETCH_ON);
	reg_0x0013 = ret8;
	xgpio_i2c_reg16_read(ch, 0x28, 0x01fc, &ret8, STRETCH_ON);
	reg_0x01fc = ret8;
	xgpio_i2c_reg16_read(ch, 0x28, 0x011a, &ret8, STRETCH_ON);
	reg_0x011a = ret8;

	if(reg_0x0013 == 0xDA && reg_0x01fc == 0x81 && reg_0x011a == 0x62)
	{
		ret8 = 0;
		usleep(1*1000);
		xgpio_i2c_reg16_read(ch, 0x28, 0x0013, &ret8, STRETCH_ON);
		reg_0x0013 = ret8;
		xgpio_i2c_reg16_read(ch, 0x28, 0x01fc, &ret8, STRETCH_ON);
		reg_0x01fc = ret8;
		xgpio_i2c_reg16_read(ch, 0x28, 0x011a, &ret8, STRETCH_ON);
		reg_0x011a = ret8;
		if(reg_0x0013 == 0xDA && reg_0x01fc == 0x81 && reg_0x011a == 0x62)
		{
//			xil_printf("\r\nch = %d lock_status \r\n",ch);
			lock_status = 1;
		}
		else
		{
	//		xil_printf("\r\n no lock_status !!!\r\n");
			lock_status = 0;
		}
	}
	else
	{
//		xil_printf("\r\n no lock_status !!!\r\n");
		lock_status = 0;
	}
}

void max96792_deal_port1(void)
{
	max96792_lock_detect(I2C_NO_1);

	if(lock_status == 1)
	{
		clear_flag_0 = 0;
		if(reconfig_flag_0 == 0)
		{
			reconfig_flag_0 = 1;
		}
		else
		{
//				reconfig_flag_0 = 2;
		}

	}
	else
	{

		reconfig_flag_0 = 0;
		if(clear_flag_0 == 0)
		{
			clear_flag_0 = 1;
		}
		else
		{
//				clear_flag_0 = 2;
		}

	}

	if(reconfig_flag_0 == 1)
	{
		OsdDrawText(2,100,40,8,0,4,0);  //添加文字
		reconfig_flag_0 = 2;

	}


	if(clear_flag_0 == 1)
	{
		OsdDrawText(2,100,40,8,3,4,0);  //添加文字
		clear_vdma_0();
		clear_flag_0 = 2;

	}

}

void max96792_deal_port2(void)
{
	max96792_lock_detect(I2C_NO_2);
	if(lock_status == 1)
	{
		clear_flag_1 = 0;
		if(reconfig_flag_1 == 0)
		{
			reconfig_flag_1 = 1;
		}
		else
		{
//				reconfig_flag_1 = 2;
		}

	}
	else
	{

		reconfig_flag_1 = 0;
		if(clear_flag_1 == 0)
		{
			clear_flag_1 = 1;
		}
		else
		{
//				clear_flag_1 = 2;
		}

	}

	if(reconfig_flag_1 == 1)
	{
		OsdDrawText(3,2700,40,7,2,4,0);  //添加文字
		reconfig_flag_1 = 2;
	}


	if(clear_flag_1 == 1)
	{
		OsdDrawText(3,2700,40,7,3,4,0);  //添加文字
		clear_vdma_1();
		clear_flag_1 = 2;
	}
}

void display_fresh(void)
{
	if(timer_cnt >= 1)//200ms
	{
		timer_cnt = 0;
		max96792_deal_port1();
		max96792_deal_port2();

	}

}


