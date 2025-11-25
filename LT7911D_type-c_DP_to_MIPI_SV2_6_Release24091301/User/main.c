#include "include.h"

TIMING g_TimingStr = 
{ 
	148500	// PixelClock/1000
, 	2200	// Htotal
, 	1920	// Hactive
, 	88		// Hfp
, 	44		// Hsw
, 	148		// Hbp
, 	1125	// Vtotal
, 	1080	// Vactive
, 	4		// Vfp
, 	5		// Vsw
, 	36		// Vbp
, 	1		// Hspol
, 	1		// Vspol
}; 


DPCD g_DpcdSetStr = 
{ 
	0x0A	// 0x14(5.4G)  & 0x0A(2.7G) & 0x06(1.62g)
, 	0x02	// 0x04(dp 4lane) & 0x02(dp 2lane) & 0x01(dp 1lane)
, 	0x00	// 0x01(SSC On) & 0x00(SSC Off)
};

MIPI g_MipiSetStr = 
{ 
	Port_4lane				// Port_4lane & Port_3lane & Port_2lane & Port_1lane
, 	Burst_Mode				// Burst_Mode & NonBurst_SyncPulse_Mode & NonBurst_SyncEvent_Mode 
, 	NonContinuousClock		// ContinuousClock & NonContinuousClock
};

u8 FwVersion[6] = {0x16, 0x05, 0x25, 0x11, 0x25, 0x01};

void Lt7911D_FwVersionSet(void)
{
	BKD2_0C_REG = FwVersion[0]; // chip_write_i2c(0xD20C,FwVersion[0]);
	BKD2_0D_REG = FwVersion[1]; // chip_write_i2c(0xD20D,FwVersion[1]);
	BKD2_0E_REG = FwVersion[2]; // chip_write_i2c(0xD20E,FwVersion[2]);
	BKD2_0F_REG = FwVersion[3]; // chip_write_i2c(0xD20F,FwVersion[3]);
	BKD2_10_REG = FwVersion[4]; // chip_write_i2c(0xD210,FwVersion[4]);
	BKD2_11_REG = FwVersion[5]; // chip_write_i2c(0xD211,FwVersion[5]);
}

void main(void)
{
	g_EdidBlockCalEnable = TRUE;

	g_ChipModel = LT7911D;		   // LT7911D & LT7911
	g_InputType = Typec_Source;	   // Typec_Source & Dp_Source
	g_DisplayMode = VideoCopyMode; // VideoCopyMode & SideBySideMode
	g_OutputMode = YUV422;			   // RGB & YUV422 & YUV444
	g_MipiFormat = YUV422_8bit;		   // RGB888 & YUV422_8bit
	g_MipiType = CSI;			   // DSI & CSI

	Lt7911_InitialSteps();
}
