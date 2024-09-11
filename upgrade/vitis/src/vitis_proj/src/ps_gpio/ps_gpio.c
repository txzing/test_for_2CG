/*
 * ps_gpio.c
 *
 *  Created on: 2023年4月28日
 *      Author: fengke
 */

#include "../bsp.h"
#if defined (XPAR_XGPIOPS_NUM_INSTANCES)

XGpioPs Gpio;

int PsGpioSetup(XGpioPs *InstancePtr, u16 DeviceId)
{
	XGpioPs_Config *GPIO_CONFIG ;
	int Status ;

	GPIO_CONFIG = XGpioPs_LookupConfig(DeviceId) ;

	Status = XGpioPs_CfgInitialize(InstancePtr, GPIO_CONFIG, GPIO_CONFIG->BaseAddr) ;
	if (Status != XST_SUCCESS)
	{
		bsp_printf(TXT_RED "XGpioPs_CfgInitialize failed...\r\n" TXT_RST);
		return XST_FAILURE ;
	}
	/* set as output */

	XGpioPs_SetDirectionPin(InstancePtr, RELAY_CUTOFF, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, RELAY_CUTOFF, 1);
	XGpioPs_WritePin(&Gpio, RELAY_CUTOFF, 0) ; // RELAY_CUTOFF: 0-keep; 1-cutoff

	XGpioPs_SetDirectionPin(InstancePtr, PL_LOCK_LED, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, PL_LOCK_LED, 1);
	XGpioPs_WritePin(&Gpio, PL_LOCK_LED, 0) ;

	XGpioPs_SetDirectionPin(InstancePtr, EEPROM_WP, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, EEPROM_WP, 1);
	XGpioPs_WritePin(&Gpio, EEPROM_WP, 0) ; // EEPROM write protect off

	XGpioPs_SetDirectionPin(InstancePtr, SIL_RSTN, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, SIL_RSTN, 1);
	XGpioPs_WritePin(&Gpio, SIL_RSTN, 1) ;

	XGpioPs_SetDirectionPin(InstancePtr, CH0_CFG1_CTL, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, CH0_CFG1_CTL, 1);
	XGpioPs_WritePin(&Gpio, CH0_CFG1_CTL, 0) ;

	XGpioPs_SetDirectionPin(InstancePtr, CH1_CFG1_CTL, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, CH1_CFG1_CTL, 1);
	XGpioPs_WritePin(&Gpio, CH1_CFG1_CTL, 0) ;

	XGpioPs_SetDirectionPin(InstancePtr, CH0_DES_PWR_EN, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, CH0_DES_PWR_EN, 1);
	XGpioPs_WritePin(&Gpio, CH0_DES_PWR_EN, 0) ;

	XGpioPs_SetDirectionPin(InstancePtr, CH1_DES_PWR_EN, 1) ;
	XGpioPs_SetOutputEnablePin(InstancePtr, CH1_DES_PWR_EN, 1);
	XGpioPs_WritePin(&Gpio, CH1_DES_PWR_EN, 0) ;


	usleep(50000);//50ms
	XGpioPs_WritePin(&Gpio, CH0_DES_PWR_EN, 1) ;
	XGpioPs_WritePin(&Gpio, CH1_DES_PWR_EN, 1) ;

	return XST_SUCCESS ;
}

#endif // XPAR_XGPIOPS_NUM_INSTANCES

