#include "../bsp.h"

#if defined (XPAR_XCLK_WIZ_NUM_INSTANCES)

#if (XPAR_XCLK_WIZ_NUM_INSTANCES == 1U)
XClk_Wiz ClkWiz_Dynamic0;
#elif (XPAR_XCLK_WIZ_NUM_INSTANCES >= 2U)
XClk_Wiz ClkWiz_Dynamic1;
#elif (XPAR_XCLK_WIZ_NUM_INSTANCES >= 3U)
XClk_Wiz ClkWiz_Dynamic3;
#endif

/*****************************************************************************/
/**
 *
 * This is the Wait_For_Lock function, it will wait for lock to settle change
 * frequency value
 *
 * @param	CfgPtr_Dynamic provides pointer to clock wizard dynamic config
 *
 * @return
 *		- Error 0 for pass scenario
 *		- Error > 0 for failure scenario
 *
 * @note		None
 *
 ******************************************************************************/
int Wait_For_Lock(XClk_Wiz_Config *CfgPtr_Dynamic)
{
    u32 Count = 0;
    u32 Error = 0;

    while(!(*(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK))
    {
        if(Count == 1000000)
        {
            Error++;
            break;
        }
        Count++;
    }
    return Error;
}

/*****************************************************************************/
/**
 *
 * XClk_Wiz wizard dynamic reconfig.
 *
 * @param	None.
 *
 * @return
 *		- XST_SUCCESS if XClk_Wiz dynamic reconfig ran successfully.
 *		- XST_FAILURE if XClk_Wiz dynamic reconfig failed.
 *
 * @note		None.
 *
 ****************************************************************************/
int XClk_Wiz_dynamic_reconfig(XClk_Wiz * ClkWizInstance, u32 DeviceId)
{
    XClk_Wiz_Config *CfgPtr_Dynamic;
    u32 Count = 0;
    u32 Divide = 0;
    u32 Multiply_Int = 0;
    u32 Multiply_Frac = 0;
    u32 Divide0_Int = 0;
    u32 Divide0_Frac = 0;
//    u32 Divide1_Int = 0;
//    u32 Divide1_Frac = 0;
//    u32 Divide2_Int = 0;
//    u32 Divide2_Frac = 0;
//    u32 Divide3_Int = 0;
//    u32 Divide3_Frac = 0;
    int Status;

    /*
     * Get the CLK_WIZ Dynamic reconfiguration driver instance
     */
    CfgPtr_Dynamic = XClk_Wiz_LookupConfig(DeviceId);
    if(!CfgPtr_Dynamic)
    {
        return XST_FAILURE;
    }

    /*
     * Initialize the CLK_WIZ Dynamic reconfiguration driver
     */
    Status = XClk_Wiz_CfgInitialize(ClkWizInstance, CfgPtr_Dynamic, CfgPtr_Dynamic->BaseAddr);
    if(Status != XST_SUCCESS)
    {
        return XST_FAILURE;
    }

    Status = Wait_For_Lock(CfgPtr_Dynamic);
    if(Status)
    {
    	bsp_printf(TXT_RED "\n ERROR: Clock is not locked for default frequency"
                   " : 0x%x\n\r"  TXT_RST,
                   *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    	bsp_printf(TXT_RED "\r\n__FILE__:%s, __LINE__:%d\r\n" TXT_RST,__FILE__, __LINE__);
//    	return XST_FAILURE;
    }

    /* SW reset applied */
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x00) = 0xA;

    if(*(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK)
    {
    	bsp_printf(TXT_RED "\n ERROR: Clock is locked : 0x%x \t expected "
                   "0x00\n\r" TXT_RST,
                   *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    	bsp_printf(TXT_RED "\r\n__FILE__:%s, __LINE__:%d\r\n" TXT_RST,__FILE__, __LINE__);
//    	return XST_FAILURE;
    }

    /* Wait cycles after SW reset */
    for(Count = 0; Count < 2000; Count++)
        ;

    Status = Wait_For_Lock(CfgPtr_Dynamic);
    if(Status)
    {
    	bsp_printf(TXT_RED "\n ERROR: Clock is not locked after SW reset :"
                   "0x%x \t Expected  : 0x1\n\r" TXT_RST,
                   *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    	bsp_printf(TXT_RED "\r\n__FILE__:%s, __LINE__:%d\r\n" TXT_RST,__FILE__, __LINE__);
//    	return XST_FAILURE;
    }


//in=200
//out1 297
	Multiply_Int = 111;
	Multiply_Frac = 375;
	Divide = 20;
	Divide0_Int = 3;
	Divide0_Frac = 750;


    /* Configuring Multiply and Divide values */
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x200) = (Multiply_Frac << 16) | (Multiply_Int << 8) | Divide;
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x204) = 0x00;

    /* Configuring Multiply and Divide values */
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x208) = (Divide0_Frac << 8) | Divide0_Int;
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x20C) = 0x00;

//    /* Configuring Multiply and Divide values */
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x214) = (Divide1_Frac << 8) | Divide1_Int;
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x218) = 0x00;
//
//    /* Configuring Multiply and Divide values */
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x220) = (Divide2_Frac << 8) | Divide2_Int;
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x224) = 0x00;
//
//    /* Configuring Multiply and Divide values */
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x22C) = (Divide3_Frac << 8) | Divide3_Int;
//    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x230) = 0x00;

    /* Load Clock Configuration Register values */
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x25C) = 0x07;

    if(*(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK)
    {
    	bsp_printf("\n ERROR: Clock is locked : 0x%x \t expected "
                   "0x00\n\r",
                   *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    	bsp_printf(TXT_RED "\r\n__FILE__:%s, __LINE__:%d\r\n" TXT_RST,__FILE__, __LINE__);
    }

    /* Clock Configuration Registers are used for dynamic reconfiguration */
    *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x25C) = 0x02;

    Status = Wait_For_Lock(CfgPtr_Dynamic);
    if(Status)
    {
    	bsp_printf(TXT_RED "\n ERROR: Clock is not locked : 0x%x \t Expected "
                   ": 0x1\n\r" TXT_RST,
                   *(u32 *) (CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    	bsp_printf(TXT_RED "\r\n__FILE__:%s, __LINE__:%d\r\n" TXT_RST,__FILE__, __LINE__);
    }

    return XST_SUCCESS;
}

int clkwiz_config(void)
{
	int Status;

    // dynamic config clkwiz
    Status = XClk_Wiz_dynamic_reconfig(&ClkWiz_Dynamic0, XPAR_CLK_WIZ_0_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
    	bsp_printf(TXT_RED "XClk_Wiz0 dynamic reconfig failed.\r\n" TXT_RST);
    	return XST_FAILURE;
    }
    bsp_printf("XClk_Wiz0 dynamic reconfig ok\n\r");

    return XST_SUCCESS;
}

int clkwiz_vtc_cfg(void)
{
    u32 Status;
    // dynamic config clkwiz
    Status = XClk_Wiz_dynamic_reconfig(&ClkWiz_Dynamic0, XPAR_CLK_WIZ_0_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
      xil_printf("XClk_Wiz0 dynamic reconfig failed.\r\n");
      return XST_FAILURE;
    }
    xil_printf("XClk_Wiz0 dynamic reconfig ok\n\r");

    // vtc configuration
    XVtc_Config *VtcConfig0;
    VtcConfig0 = XVtc_LookupConfig(XPAR_VTC_0_DEVICE_ID);
    Status = XVtc_CfgInitialize(&VtcInst0, VtcConfig0, VtcConfig0->BaseAddress);
    if(Status != XST_SUCCESS)
    {
      xil_printf("VTC0 Initialization failed %d\r\n", Status);
      return(XST_FAILURE);
    }
    xil_printf("VTC0 Initialization ok\r\n");
#if (defined R1080P60)
    vtiming_gen_run(&VtcInst0, VIDEO_RESOLUTION_1080P, 0);
#else
    vtiming_gen_run(&VtcInst0, VIDEO_RESOLUTION_4K, 0);
#endif
    xil_printf("clkwiz_vtc_cfg done!\r\n");
/*******************************************************************************/
    return XST_SUCCESS;
}


#endif // XPAR_XCLK_WIZ_NUM_INSTANCES


