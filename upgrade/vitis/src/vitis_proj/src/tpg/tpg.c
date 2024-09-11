#include "../bsp.h"
#if defined (XPAR_XV_TPG_NUM_INSTANCES)


#if (XPAR_XV_TPG_NUM_INSTANCES >= 1U)
XV_tpg tpg_inst0;
XVidC_ColorFormat colorFmtIn0 = XVIDC_CSF_RGB;
//XVidC_ColorFormat colorFmtIn0 = XVIDC_CSF_YCRCB_422;
u32 bckgndId0=XTPG_BKGND_COLOR_BARS;
#endif // XPAR_XV_TPG_NUM_INSTANCES == 1U
#if (XPAR_XV_TPG_NUM_INSTANCES >= 2U)
XV_tpg tpg_inst1;
XVidC_ColorFormat colorFmtIn1 = XVIDC_CSF_RGB;
u32 bckgndId1=XTPG_BKGND_CHECKER_BOARD;
#endif // XPAR_XV_TPG_NUM_INSTANCES == 2U
#if (XPAR_XV_TPG_NUM_INSTANCES >= 3U)
XV_tpg tpg_inst2;
XVidC_ColorFormat colorFmtIn2 = XVIDC_CSF_RGB;
u32 bckgndId2=XTPG_BKGND_COLOR_BARS;
#endif // XPAR_XV_TPG_NUM_INSTANCES == 3U
#if (XPAR_XV_TPG_NUM_INSTANCES >= 4U)
XV_tpg tpg_inst3;
XVidC_ColorFormat colorFmtIn3 = XVIDC_CSF_RGB;
u32 bckgndId3=XTPG_BKGND_COLOR_BARS;
#endif // XPAR_XV_TPG_NUM_INSTANCES == 4U

/************************** Function Definitions *****************************/

/*****************************************************************************/
/**
*
* This function configures the TPG core.
* @param	InstancePtr is a pointer to the TPG core instance to be
*		worked on.
* @param	height is the output video height
* @param	width is the output video width
* @param	colorFormat is the output colorFormat
* @param	bckgndId is the ID for the background
*
*
******************************************************************************/
void tpg_cfg(XV_tpg *InstancePtr, u32 height, u32 width, u32 colorFormat, u32 bckgndId)
{
	// Stop TPG
	XV_tpg_DisableAutoRestart(InstancePtr);

	// Set Resolution
    XV_tpg_Set_height(InstancePtr, height);
    XV_tpg_Set_width(InstancePtr, width);

    // Set Color Space
    XV_tpg_Set_colorFormat(InstancePtr, colorFormat);

    // Change the pattern to color bar
    XV_tpg_Set_bckgndId(InstancePtr, bckgndId);

    // Enable overlay
    XV_tpg_Set_ovrlayId(InstancePtr, 0);
}

/*****************************************************************************/
/**
*
* This function sets up the moving box of the TPG core.
* @param	InstancePtr is a pointer to the TPG core instance to be
*		worked on.
* @param	boxSize is the size of the moving box
* @param	motionSpeed is the speed of the moving box
*
*
******************************************************************************/
void tpg_box(XV_tpg *InstancePtr, u32 boxSize, u32 motionSpeed)
{
    // Set Overlay to moving box
    // Set the size of the box
    XV_tpg_Set_boxSize(InstancePtr, boxSize);
    // Set the speed of the box
    XV_tpg_Set_motionSpeed(InstancePtr, motionSpeed);
    // Enable the moving box
    XV_tpg_Set_ovrlayId(InstancePtr, 1);

}


int tpg_config(void)
{
    u32 Status;
#if (XPAR_XV_TPG_NUM_INSTANCES >= 1U)
    // tpg0
    xil_printf("TPG0 Initializing\n\r");

    Status = XV_tpg_Initialize(&tpg_inst0, XPAR_XV_TPG_0_DEVICE_ID);
    if(Status!= XST_SUCCESS)
    {
        xil_printf("TPG0 configuration failed\r\n");
        return(XST_FAILURE);
    }

#if (defined R1080P60)
    tpg_cfg(&tpg_inst0, 1080, 1920, colorFmtIn0, bckgndId0);
#elif  (defined R4K30W)
//    tpg_cfg(&tpg_inst0, 2160, 3840, colorFmtIn0, bckgndId0);
    tpg_cfg(&tpg_inst0, 1440, 2560, colorFmtIn0, bckgndId0);
#else
    tpg_cfg(&tpg_inst0, 2160, 3840, colorFmtIn0, bckgndId0);
#endif

    //Configure the moving box of the TPG0
    tpg_box(&tpg_inst0, 50, 1);

    //Start the TPG0
    XV_tpg_EnableAutoRestart(&tpg_inst0);
    XV_tpg_Start(&tpg_inst0);
    xil_printf("TPG0 started!\r\n");
#endif

#if (XPAR_XV_TPG_NUM_INSTANCES >= 2U)
/*********************************************************************/
    // tpg1
    xil_printf("TPG1 Initializing\n\r");

    Status = XV_tpg_Initialize(&tpg_inst1, XPAR_XV_TPG_1_DEVICE_ID);
    if(Status!= XST_SUCCESS)
    {
        xil_printf("TPG1 configuration failed\r\n");
        return(XST_FAILURE);
    }

#if (defined R1080P60)
    tpg_cfg(&tpg_inst1, 1080, 1920, colorFmtIn1, bckgndId1);
#elif  (defined R4K30W)
//    tpg_cfg(&tpg_inst1, 2160, 3840, colorFmtIn1, bckgndId1);
    tpg_cfg(&tpg_inst1, 1440, 2560, colorFmtIn1, bckgndId1);
#else
    tpg_cfg(&tpg_inst1, 1286, 1920, colorFmtIn1, bckgndId1);
#endif

    //Configure the moving box of the TPG0
    tpg_box(&tpg_inst1, 50, 1);

    //Start the TPG1
    XV_tpg_EnableAutoRestart(&tpg_inst1);
    XV_tpg_Start(&tpg_inst1);
    xil_printf("TPG1 started!\r\n");
#endif

#if (XPAR_XV_TPG_NUM_INSTANCES >= 3U)
/*********************************************************************/
	// tpg2
	xil_printf("TPG2 Initializing\n\r");

	Status = XV_tpg_Initialize(&tpg_inst2, XPAR_XV_TPG_2_DEVICE_ID);
	if(Status!= XST_SUCCESS)
	{
		xil_printf("TPG2 configuration failed\r\n");
		return(XST_FAILURE);
	}

#if (defined R1080P60)
	tpg_cfg(&tpg_inst2, 1080, 1920, colorFmtIn2, bckgndId2);
#elif  (defined R4K30W)
	tpg_cfg(&tpg_inst2, 2160, 3840, colorFmtIn2, bckgndId2);
#else
	tpg_cfg(&tpg_inst2, 1286, 1920, colorFmtIn2, bckgndId2);
#endif

	//Configure the moving box of the TPG0
	tpg_box(&tpg_inst2, 50, 1);

	//Start the TPG2
	XV_tpg_EnableAutoRestart(&tpg_inst2);
	XV_tpg_Start(&tpg_inst2);
	xil_printf("TPG2 started!\r\n");
#endif

#if (XPAR_XV_TPG_NUM_INSTANCES >= 4U)
/*********************************************************************/
	// tpg3
	xil_printf("TPG3 Initializing\n\r");

	Status = XV_tpg_Initialize(&tpg_inst3, XPAR_XV_TPG_3_DEVICE_ID);
	if(Status!= XST_SUCCESS)
	{
		xil_printf("TPG3 configuration failed\r\n");
		return(XST_FAILURE);
	}

#if (defined R1080P60)
	tpg_cfg(&tpg_inst3, 1080, 1920, colorFmtIn3, bckgndId3);
#elif  (defined R4K30W)
	tpg_cfg(&tpg_inst3, 2160, 3840, colorFmtIn3, bckgndId3);
#else
	tpg_cfg(&tpg_inst3, 1286, 1920, colorFmtIn3, bckgndId3);
#endif

	//Configure the moving box of the TPG0
	tpg_box(&tpg_inst3, 50, 1);

	//Start the TPG3
	XV_tpg_EnableAutoRestart(&tpg_inst3);
	XV_tpg_Start(&tpg_inst3);
	xil_printf("TPG3 started!\r\n");
#endif

	return XST_SUCCESS;
}

#endif // XPAR_XV_TPG_NUM_INSTANCES
