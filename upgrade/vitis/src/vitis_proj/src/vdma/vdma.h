#ifndef __VDMA_H__

//#include "xparameters.h"
#if defined (XPAR_XAXIVDMA_NUM_INSTANCES)
#define __VDMA_H__

#include "xaxivdma.h"
#include "xil_cache.h"

u32 vdma_init(u16 DeviceID,XAxiVdma *Vdma);
int vdma_read_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
int vdma_write_init(short DeviceID,XAxiVdma *Vdma,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr0,unsigned int FrameStoreStartAddr1,unsigned int FrameStoreStartAddr2);
u32 vdma_version();
void vdma_config(void);
void clear_display(void);


#if (XPAR_XAXIVDMA_NUM_INSTANCES >= 1U)
extern	XAxiVdma Vdma0;
extern int WriteOneFrameEnd;
#endif
#if (XPAR_XAXIVDMA_NUM_INSTANCES >= 2U)
extern	XAxiVdma Vdma1;
#endif
#if (XPAR_XAXIVDMA_NUM_INSTANCES >= 3U)
extern	XAxiVdma Vdma2;
#endif
#if (XPAR_XAXIVDMA_NUM_INSTANCES >= 4U)
extern	XAxiVdma Vdma3;
#endif
#if (XPAR_XAXIVDMA_NUM_INSTANCES >= 5U)
extern	XAxiVdma Vdma4;
#endif

#endif

#endif /* VDMA_H_ */
