#include "include.h"

void chip_write_i2c(u8 xdata *p, u8 val)
{
	*p = val;
}

u8 chip_read_i2c(u8 xdata *p)
{
	return *p;
}

void DelayMs(u16 var)
{
	u16 i;
	while (var--)
	{
		for (i = 0; i < 350; i++)
			;
	}
}

bool VideoCheck(void)
{
	u32 rd_PixelClock;
	u16 rd_Htotal, rd_Hactive, rd_Hstart, rd_Hfp, rd_Hsw, rd_Hbp;
	u16 rd_Vtotal, rd_Vactive, rd_Vstart;
	u8 rd_Vfp, rd_Vsw, rd_Vbp;
	u8 rd_Hspol, rd_Vspol;

	chip_write_i2c(0xD283, 0x10);

	chip_write_i2c(0xA034, 0x21);
	DelayMs(50);
	chip_write_i2c(0x9052, 0xE7); // close frequency meter
	rd_PixelClock = chip_read_i2c(0xB8B1);
	rd_PixelClock = (rd_PixelClock << 8) + chip_read_i2c(0xB8B2);
	rd_PixelClock = (rd_PixelClock << 8) + chip_read_i2c(0xB8B3);
	rd_PixelClock = 2 * rd_PixelClock;
	chip_write_i2c(0x9052, 0xFF); // open frequency mete

	chip_write_i2c(0xA034, 0x01);

#if 0 // take video from video check
	rd_Htotal = chip_read_i2c(0xD289) << 8;
	rd_Htotal = rd_Htotal + chip_read_i2c(0xD28A);
	rd_Htotal = rd_Htotal*2;

	rd_Hactive = chip_read_i2c(0xD28B) << 8;
	rd_Hactive = rd_Hactive + chip_read_i2c(0xD28C);
	rd_Hactive = rd_Hactive*2;

	rd_Hfp = chip_read_i2c(0xD29C) << 8;
	rd_Hfp = rd_Hfp + chip_read_i2c(0xD29D);
	rd_Hfp = rd_Hfp*2;
	
	rd_Hsw = chip_read_i2c(0xD294) << 8;
	rd_Hsw = rd_Hsw + chip_read_i2c(0xD295);
	rd_Hsw = rd_Hsw*2;

	rd_Hbp = chip_read_i2c(0xD298) << 8;
	rd_Hbp = rd_Hbp + chip_read_i2c(0xD299);
	rd_Hbp = rd_Hbp*2;

	rd_Vtotal =  chip_read_i2c(0xD29E) << 8;
	rd_Vtotal = rd_Vtotal + chip_read_i2c(0xD29F);
	
	rd_Vactive =  chip_read_i2c(0xD296) << 8;
	rd_Vactive = rd_Vactive + chip_read_i2c(0xD297);
	
	rd_Vfp = chip_read_i2c(0xD288);
	rd_Vsw = chip_read_i2c(0xD286);
	rd_Vbp = chip_read_i2c(0xD287);

	rd_Hspol = (chip_read_i2c(0xD2A0) & 0x02) >> 1;
	rd_Vspol = chip_read_i2c(0xD2A0) & 0x01;
#endif
	// printf("\n[pixel clock] : %d MHZ\n", rd_PixelClock);
	// printf("\n[H] : %d (active %d, sync:%d, fp:%d, bp:%d)\n",  rd_Htotal, rd_Hactive, rd_Hsw, rd_Hfp, rd_Hbp);
	// printf("\n[V] : %d (active %d, sync:%d, fp:%d, bp:%d)\n",  rd_Vtotal, rd_Vactive, rd_Vsw, rd_Vfp, rd_Vbp);

#if 1 ////take video from MSA
	rd_Htotal = chip_read_i2c(0xD1DB) << 8;
	rd_Htotal = rd_Htotal + chip_read_i2c(0xD1DC);

	rd_Hactive = chip_read_i2c(0xD1E7) << 8;
	rd_Hactive = rd_Hactive + chip_read_i2c(0xD1E8);

	rd_Hsw = (chip_read_i2c(0xD1DF) & 0x7F) << 8;
	rd_Hsw = rd_Hsw + chip_read_i2c(0xD1E0);

	rd_Hstart = chip_read_i2c(0xD1E1) << 8;
	rd_Hstart = rd_Hstart + chip_read_i2c(0xD1E2);

	rd_Hbp = rd_Hstart - rd_Hsw;
	rd_Hfp = rd_Htotal - rd_Hactive - rd_Hstart;

	rd_Vtotal = chip_read_i2c(0xD1DD) << 8;
	rd_Vtotal = rd_Vtotal + chip_read_i2c(0xD1DE);

	rd_Vactive = chip_read_i2c(0xD1E9) << 8;
	rd_Vactive = rd_Vactive + chip_read_i2c(0xD1EA);

	rd_Vsw = chip_read_i2c(0xD1E6);

	rd_Vstart = chip_read_i2c(0xD1E3) << 8;
	rd_Vstart = rd_Vstart + chip_read_i2c(0xD1E4);

	rd_Vbp = rd_Vstart - rd_Vsw;
	rd_Vfp = rd_Vtotal - rd_Vactive - rd_Vstart;

	rd_Hspol = !((chip_read_i2c(0xD1DF) & 0x80) >> 7);
	rd_Vspol = !((chip_read_i2c(0xD1E5) & 0x80) >> 7);
#endif

	g_TimingStr.PixelClock = rd_PixelClock;
	g_TimingStr.Htotal = rd_Htotal;
	g_TimingStr.Hactive = rd_Hactive;
	g_TimingStr.Hfp = rd_Hfp;
	g_TimingStr.Hsw = rd_Hsw;
	g_TimingStr.Hbp = rd_Hbp;
	g_TimingStr.Vtotal = rd_Vtotal;
	g_TimingStr.Vactive = rd_Vactive;
	g_TimingStr.Vfp = rd_Vfp;
	g_TimingStr.Vsw = rd_Vsw;
	g_TimingStr.Vbp = rd_Vbp;
	g_TimingStr.Hspol = rd_Hspol;
	g_TimingStr.Vspol = rd_Vspol;

	return TRUE;
}

void ColorSpaceConversion(void)
{
	u8 rd_ColorSpace = 0;
	u8 rd_RangeDetectDone = 0;
	u8 rd_RgbRange = 0;

	/**********CSCRangeDetect*************/
	chip_write_i2c(0xA050, 0x00);
	chip_write_i2c(0xA051, 0x02);
	chip_write_i2c(0xA052, 0x03);
	chip_write_i2c(0xA053, 0x00);
	chip_write_i2c(0xA054, 0xF1);

	chip_write_i2c(0xA050, chip_read_i2c(0xA050) | 0x02); // CSC range detect enable
	DelayMs(200);										  // wait about 6frame
	rd_RangeDetectDone = chip_read_i2c(0xA00C) & 0x02;
	if (rd_RangeDetectDone)
	{
		rd_RgbRange = chip_read_i2c(0xA00C) & 0x01;
	}
	chip_write_i2c(0xA050, chip_read_i2c(0xA050) & 0xFD); // CSC range detect disable
	/**************************************/

	rd_ColorSpace = chip_read_i2c(0xD1EB) & 0x06;

	if (rd_ColorSpace == 0x00) // RGB
	{
		if (g_OutputMode == RGB)
		{
			if (rd_RgbRange == Full_Range)
			{
				chip_write_i2c(0xA050, 0x04);
				chip_write_i2c(0xA055, 0x00);
				chip_write_i2c(0xA057, 0x00);
			}
			else // limited range -> full range
			{
				chip_write_i2c(0xA050, 0x04);
				chip_write_i2c(0xA055, 0x00);
				chip_write_i2c(0xA057, 0x03);
			}
		}
		else if (g_OutputMode == YUV444)
		{
			if (rd_RgbRange == Full_Range)
			{
				chip_write_i2c(0xA050, 0x00);
				chip_write_i2c(0xA055, 0xF0);
				chip_write_i2c(0xA057, 0x00);
			}
			else
			{
				chip_write_i2c(0xA050, 0x00);
				chip_write_i2c(0xA055, 0xE0);
				chip_write_i2c(0xA057, 0x00);
			}
		}
		else if (g_OutputMode == YUV422)
		{
			if (rd_RgbRange == Full_Range)
			{
				chip_write_i2c(0xA050, 0x00);
				chip_write_i2c(0xA055, 0xFC);
				chip_write_i2c(0xA057, 0x00);
			}
			else
			{
				chip_write_i2c(0xA050, 0x00);
				chip_write_i2c(0xA055, 0xEC);
				chip_write_i2c(0xA057, 0x00);
			}
		}
	}
	else if (rd_ColorSpace == 0x02) // YUV422
	{
		if (g_OutputMode == RGB)
		{
			chip_write_i2c(0xA050, 0x00);
			chip_write_i2c(0xA055, 0x03);
			chip_write_i2c(0xA057, 0x3c);
		}
		else if (g_OutputMode == YUV444)
		{
			chip_write_i2c(0xA050, 0x00);
			chip_write_i2c(0xA055, 0x03);
			chip_write_i2c(0xA057, 0x00);
		}
		else if (g_OutputMode == YUV422)
		{
			chip_write_i2c(0xA050, 0x04);
			chip_write_i2c(0xA055, 0x00);
			chip_write_i2c(0xA057, 0x00);
		}
	}
	else if (rd_ColorSpace == 0x04) // YUV444
	{
		if (g_OutputMode == RGB)
		{
			chip_write_i2c(0xA050, 0x00);
			chip_write_i2c(0xA055, 0x00);
			chip_write_i2c(0xA057, 0x3C);
		}
		else if (g_OutputMode == YUV444)
		{
			chip_write_i2c(0xA050, 0x04);
			chip_write_i2c(0xA055, 0x00);
			chip_write_i2c(0xA057, 0x00);
		}
		else if (g_OutputMode == YUV422)
		{
			chip_write_i2c(0xA050, 0x00);
			chip_write_i2c(0xA055, 0x0C);
			chip_write_i2c(0xA057, 0x00);
		}
	}
}

void SyncPolAdjust(void)
{
	if (g_TimingStr.Hspol != 0x01)
	{
		chip_write_i2c(0xD205, chip_read_i2c(0xD205) | 0x04);
		chip_write_i2c(0xD205, chip_read_i2c(0xD205) & 0xF7);
	}

	if (g_TimingStr.Vspol != 0x01)
	{
		chip_write_i2c(0xD205, chip_read_i2c(0xD205) | 0x10);
		chip_write_i2c(0xD205, chip_read_i2c(0xD205) & 0xDF);
	}
}

void MipiLaneSwap(void)
{
	chip_write_i2c(0xA035, 0x43);
	chip_write_i2c(0xA036, 0x21);
	chip_write_i2c(0xA037, 0x04);
	chip_write_i2c(0xA038, 0x32);
	chip_write_i2c(0xA039, 0x10);
	chip_write_i2c(0xA03A, 0x43);
	chip_write_i2c(0xA03B, 0x21);
	chip_write_i2c(0xA03C, 0x04);
	chip_write_i2c(0xA03D, 0x32);
	chip_write_i2c(0xA03E, 0x10);
}

void MipiPortSet(void)
{

	if (g_DisplayMode == VideoCopyMode)
	{
		chip_write_i2c(0xA043, 0xFF);
	}
	else if (g_DisplayMode == SideBySideMode)
	{
		if (g_ChipModel == LT7911D)
		{
			chip_write_i2c(0xA043, 0xF5);
		}
		else
		{
			chip_write_i2c(0xA043, 0xDD);
		}
	}

	// port1
	chip_write_i2c(0xB055, 0x34);
	chip_write_i2c(0xB05D, 0x9F);
	chip_write_i2c(0xB05F, 0x9F);
	chip_write_i2c(0xB061, 0x8F);
	chip_write_i2c(0xB063, 0x9F);
	chip_write_i2c(0xB065, 0x9F);
	// port3
	chip_write_i2c(0xB077, 0x34);
	chip_write_i2c(0xB07F, 0x9F);
	chip_write_i2c(0xB081, 0x9F);
	chip_write_i2c(0xB083, 0x8F);
	chip_write_i2c(0xB085, 0x9F);
	chip_write_i2c(0xB087, 0x9F);
	if (g_ChipModel == LT7911)
	{
		// port0
		chip_write_i2c(0xB044, 0x34);
		chip_write_i2c(0xB04C, 0x9F);
		chip_write_i2c(0xB04E, 0x9F);
		chip_write_i2c(0xB050, 0x8F);
		chip_write_i2c(0xB052, 0x9F);
		chip_write_i2c(0xB054, 0x9F);
		// port2
		chip_write_i2c(0xB066, 0x34);
		chip_write_i2c(0xB06E, 0x9F);
		chip_write_i2c(0xB070, 0x9F);
		chip_write_i2c(0xB072, 0x8F);
		chip_write_i2c(0xB074, 0x9F);
		chip_write_i2c(0xB076, 0x9F);
	}
}

void MipiClockSet(void)
{
	u16 rd_pixelclk = 0;
	u8 wr_byteclk = 0;
	u8 wr_freq_div = 0;
	u8 wr_mipiclock = 0;
	u8 m = 0;
	rd_pixelclk = (g_TimingStr.PixelClock / 1000);

	switch (g_MipiFormat)
	{
	case RGB888:
		wr_byteclk = (rd_pixelclk * 3) / g_MipiSetStr.SetPortLaneNum / g_DisplayMode;
		break;
	case YUV422_8bit:
		wr_byteclk = (rd_pixelclk * 2) / g_MipiSetStr.SetPortLaneNum / g_DisplayMode;
		break;
	default:
		break;
	}

	wr_byteclk += OFFSET;

	if (wr_byteclk < 50)
	{
		wr_byteclk = 50;
	}

	chip_write_i2c(0xB03A, 0x38);
	chip_write_i2c(0xB03B, 0x01);

	if ((wr_byteclk < 187) && (wr_byteclk >= 80))
	{
		chip_write_i2c(0xB03E, 0x10);
		wr_freq_div = 1;
	}
	else if ((wr_byteclk < 80) && (wr_byteclk >= 40))
	{
		chip_write_i2c(0xB03E, 0x00);
		wr_freq_div = 2;
	}
	else if ((wr_byteclk < 40) && (wr_byteclk >= 20))
	{
		chip_write_i2c(0xB03E, 0x20);
		wr_freq_div = 4;
	}
	else if ((wr_byteclk < 20) && (wr_byteclk >= 10))
	{
		chip_write_i2c(0xB03E, 0x30);
		wr_freq_div = 8;
	}
	chip_write_i2c(0xB03F, 0x10);
	chip_write_i2c(0xB040, 0x10);
	chip_write_i2c(0xB041, (wr_byteclk * wr_freq_div * 8) / 27);

	do
	{
		m++;
		chip_write_i2c(0x900F, 0xDF);
		chip_write_i2c(0xB044, chip_read_i2c(0xB044) & 0xBF);
		DelayMs(1);
		chip_write_i2c(0x900F, 0xFF);
		chip_write_i2c(0xB044, chip_read_i2c(0xB044) | 0x40);
		DelayMs(100);

		chip_write_i2c(0xB81e, 0x00);
		DelayMs(10);
		chip_write_i2c(0xB81e, 0x01);
		DelayMs(10);
		chip_write_i2c(0xB81e, 0x03);
		DelayMs(100);
	} while ((m < 3) && (!(chip_read_i2c(0xB8B0) & 0x10)));

	chip_write_i2c(0xA034, 0x1A);
	DelayMs(10);
	chip_write_i2c(0x9052, 0xE7); // close frequency meter
	g_MipiByteClock = chip_read_i2c(0xB8B1);
	g_MipiByteClock = (g_MipiByteClock << 8) + chip_read_i2c(0xB8B2);
	g_MipiByteClock = (g_MipiByteClock << 8) + chip_read_i2c(0xB8B3);
	chip_write_i2c(0x9052, 0xFF); // open frequency meter

	chip_write_i2c(0xA034, 0x01);
	wr_mipiclock = g_MipiByteClock * 4;
	// printf("\n[MIPI] : %d MHz@ %d  lanes\n", wr_mipiclock , g_MipiSetStr.SetPortLaneNum);
}

void MipiDphySet(void)
{
	u8 rdbyteclk, wrhslpx, wrhsprep, wrhszero, wrhstrail;
	u8 wrclktrail, wrclkprpr, wrclkzero;

	rdbyteclk = g_MipiByteClock / 1000;

	wrhslpx = rdbyteclk / 10;		// hs lpx > 50ns
	wrhsprep = rdbyteclk / 18 + 2;	// hs prep : (40ns + 4*UI)~(85ns + 6*UI)
	wrhszero = rdbyteclk / 6 + 1;	// hs zero > 145ns + 10UI - hsprep
	wrhstrail = rdbyteclk / 10 + 5; // 60+4UI ~ 100+12UI与测量值符合

	wrclktrail = rdbyteclk / 12 + 1; // 60ns ~ 100+12UI 与测量值符合，Clock post设计有误，写成1防止重叠；
	wrclkprpr = rdbyteclk / 25;		 // 38ns~95ns与实际值符合
	wrclkzero = rdbyteclk / 5;		 // Clkzero > 300ns - clkprpr ;比测量值小2

	chip_write_i2c(0x900A, 0xBE);
	chip_write_i2c(0x900A, 0xBF);

	chip_write_i2c(0xB044, chip_read_i2c(0xB044) | 0x80);
	chip_write_i2c(0xA044, 0xC0);
	chip_write_i2c(0xA049, 0x80);

	chip_write_i2c(0xC200, 0x00);

	chip_write_i2c(0xC201, 0x00);
	chip_write_i2c(0xC256, 0x00);

	chip_write_i2c(0xC220, 0x0F);
	chip_write_i2c(0xC225, 0x11);
	chip_write_i2c(0xC22C, 0x11);

	// chip_write_i2c(0xC221, rdbyteclk/12 + 8);//ck_post  0x05
	chip_write_i2c(0xC222, wrclktrail); // ck_trail	0x05
	chip_write_i2c(0xC223, wrclkprpr);	// ck_prpr 0x07
	chip_write_i2c(0xC224, wrclkzero);	// ck_zero	0x1f

	// Port 1
	chip_write_i2c(0xC22F, wrhsprep); // pt1_hs_prpr
	chip_write_i2c(0xC230, wrhslpx);  // pt1_lpx
	chip_write_i2c(0xC231, 0xAA);	  // pt1_cklane_data
	// Port3
	chip_write_i2c(0xC252, wrhsprep); // pt3_hs_prpr
	chip_write_i2c(0xC253, wrhslpx);  // pt3_lpx
	chip_write_i2c(0xC254, 0xAA);	  // pt3_cklane_data

	if (g_ChipModel == LT7911)
	{
		// Port 0
		chip_write_i2c(0xC226, wrhslpx);  // pt0_lpx
		chip_write_i2c(0xC227, wrhsprep); // pt0_hs_prpr
		chip_write_i2c(0xC22E, 0xAA);	  // pt0_cklane_data
		// Port2
		chip_write_i2c(0xC232, wrhsprep); // pt2_hs_prpr  0x07
		chip_write_i2c(0xC233, wrhslpx);  // pt2_lpx	0x07
		chip_write_i2c(0xC251, 0xAA);	  // pt2_cklane_data
	}

	chip_write_i2c(0xC228, wrhstrail);					   // hs_trail		//Aaron   =0x0a
	chip_write_i2c(0xC22A, wrhslpx + wrhsprep + wrhszero); // hs_rqst_pre_cnt =0x1a

	chip_write_i2c(0xC21B, 0x10);
	chip_write_i2c(0xC21D, 0x50);
	chip_write_i2c(0xC22D, 0x50); // cmd_rqst_len
}

void MipiProtocalSet(void)
{
	chip_write_i2c(0xC20C, g_TimingStr.Hactive / 256);
	chip_write_i2c(0xC20D, g_TimingStr.Hactive % 256);
	chip_write_i2c(0xC235, g_TimingStr.Vsw + g_TimingStr.Vbp);

	chip_write_i2c(0xC206, g_TimingStr.Vactive / 256);
	chip_write_i2c(0xC207, g_TimingStr.Vactive % 256);

	chip_write_i2c(0xC20F, 0x55);
	if (g_DisplayMode == VideoCopyMode)
	{
		switch (g_MipiType)
		{
		case DSI:
			chip_write_i2c(0xC238, g_TimingStr.Hactive / 256);
			chip_write_i2c(0xC239, g_TimingStr.Hactive % 256);
			chip_write_i2c(0xC204, g_TimingStr.Vsw);
			chip_write_i2c(0xC205, g_TimingStr.Vbp);
			chip_write_i2c(0xC208, g_TimingStr.Vfp);
			chip_write_i2c(0xC209, 0x0A);
			chip_write_i2c(0xC20A, 0x0A);
			chip_write_i2c(0xC20B, 0x0A);
			if (g_MipiFormat == RGB888)
			{
				chip_write_i2c(0xC217, 0x26);
				chip_write_i2c(0xC212, 0x3E);
				// printf(">> MIPI format is DSI RGB888 , datetype is 0x3E!\n");
			}
			else if (g_MipiFormat == YUV422_8bit)
			{
				chip_write_i2c(0xC217, 0x24);
				chip_write_i2c(0xC212, 0x1C);
				// printf(">> MIPI format is DSI YUV422 8bit UYVY, datatype is 0x1C! \n");
			}

			break;
		case CSI:
			chip_write_i2c(0xC238, g_TimingStr.Hactive / 256);
			chip_write_i2c(0xC239, g_TimingStr.Hactive % 256);
			chip_write_i2c(0xC204, g_TimingStr.Vsw + g_TimingStr.Vbp - 1);
			chip_write_i2c(0xC205, 0x01);
			chip_write_i2c(0xC208, 0x00);
			chip_write_i2c(0xC209, 0x01);
			chip_write_i2c(0xC20A, 0x01);
			chip_write_i2c(0xC20B, 0x01);
			if (g_MipiFormat == RGB888)
			{
				chip_write_i2c(0xC217, 0x26);
				chip_write_i2c(0xC212, 0x24);
				// printf(">> MIPI format is CSI YUV422 8bit UYVY, datatype is 0x24! \n");
			}
			else if (g_MipiFormat == YUV422_8bit)
			{
				chip_write_i2c(0xC217, 0x24);
				chip_write_i2c(0xC212, 0x1E);
				// printf(">> MIPI format is CSI YUV422 8bit UYVY, datatype is 0x1E! \n");
			}
			break;
		}
	}
	else
	{
		chip_write_i2c(0xC210, (g_TimingStr.Hactive / 4) / 256);
		chip_write_i2c(0xC211, (g_TimingStr.Hactive / 4) % 256);
		switch (g_MipiType)
		{
		case DSI:
			chip_write_i2c(0xC238, (g_TimingStr.Hactive / 2) / 256);
			chip_write_i2c(0xC239, (g_TimingStr.Hactive / 2) % 256);
			chip_write_i2c(0xC204, g_TimingStr.Vsw);
			chip_write_i2c(0xC205, g_TimingStr.Vbp);
			chip_write_i2c(0xC208, g_TimingStr.Vfp);
			chip_write_i2c(0xC209, 0x0A);
			chip_write_i2c(0xC20A, 0x0A);
			chip_write_i2c(0xC20B, 0x0A);
			chip_write_i2c(0xC236, (g_TimingStr.Hactive / 2) / 256);
			chip_write_i2c(0xC237, (g_TimingStr.Hactive / 2) % 256);
			chip_write_i2c(0xC257, g_TimingStr.Vsw);
			chip_write_i2c(0xC258, g_TimingStr.Vbp);
			chip_write_i2c(0xC259, g_TimingStr.Vfp);
			chip_write_i2c(0xC25A, 0x0A);
			chip_write_i2c(0xC25B, 0x0A);
			chip_write_i2c(0xC25C, 0x0A);
			if (g_MipiFormat == RGB888)
			{
				chip_write_i2c(0xC217, 0xA6);
				chip_write_i2c(0xC24C, 0xA6);
				chip_write_i2c(0xC212, 0x3E);
				chip_write_i2c(0xC25D, 0x3E);
				// printf(">> MIPI format is DSI RGB888 , datetype is 0x3E!\n");
			}
			else if (g_MipiFormat == YUV422_8bit)
			{
				chip_write_i2c(0xC217, 0xA4);
				chip_write_i2c(0xC24C, 0xA4);
				chip_write_i2c(0xC212, 0x1C);
				chip_write_i2c(0xC25D, 0x1C);
				// printf(">> MIPI format is DSI YUV422 8bit UYVY, datatype is 0x1C! \n");
			}

			break;
		case CSI:
			chip_write_i2c(0xC238, (g_TimingStr.Hactive / 2) / 256);
			chip_write_i2c(0xC239, (g_TimingStr.Hactive / 2) % 256);
			chip_write_i2c(0xC204, g_TimingStr.Vsw + g_TimingStr.Vbp - 1);
			chip_write_i2c(0xC205, 0x01);
			chip_write_i2c(0xC208, 0x00);
			chip_write_i2c(0xC209, 0x01);
			chip_write_i2c(0xC20A, 0x01);
			chip_write_i2c(0xC20B, 0x01);
			chip_write_i2c(0xC236, (g_TimingStr.Hactive / 2) / 256);
			chip_write_i2c(0xC237, (g_TimingStr.Hactive / 2) % 256);
			chip_write_i2c(0xC257, g_TimingStr.Vsw + g_TimingStr.Vbp - 1);
			chip_write_i2c(0xC258, 0x01);
			chip_write_i2c(0xC259, 0x00);
			chip_write_i2c(0xC25A, 0x01);
			chip_write_i2c(0xC25B, 0x01);
			chip_write_i2c(0xC25C, 0x01);
			if (g_MipiFormat == RGB888)
			{
				chip_write_i2c(0xC217, 0xA6);
				chip_write_i2c(0xC24C, 0xA6);
				chip_write_i2c(0xC212, 0x24);
				chip_write_i2c(0xC25D, 0x24);
				// printf(">> MIPI format is CSI YUV422 8bit UYVY, datatype is 0x24! \n");
			}
			else if (g_MipiFormat == YUV422_8bit)
			{
				chip_write_i2c(0xC217, 0xA4);
				chip_write_i2c(0xC24C, 0xA4);
				chip_write_i2c(0xC212, 0x1E);
				chip_write_i2c(0xC25D, 0x1E);
				// printf(">> MIPI format is CSI YUV422 8bit UYVY, datatype is 0x1E! \n");
			}
			break;
		}
	}
}

void MipiRdDlyCal(void)
{
	u32 rd_dly = 0;
	u16 rd_Hsw, rd_Hbp, rd_Hactive;
	u32 m, x, y = 0;
	u16 rdpixclk = 0;
	u16 rdbyteclk = 0;

	chip_write_i2c(0xA034, 0x1A);
	DelayMs(10);
	g_MipiByteClock = chip_read_i2c(0xB8B1);
	g_MipiByteClock = (g_MipiByteClock << 8) + chip_read_i2c(0xB8B2);
	g_MipiByteClock = (g_MipiByteClock << 8) + chip_read_i2c(0xB8B3);
	chip_write_i2c(0xA034, 0x01);

	rdpixclk = g_TimingStr.PixelClock / 1000 / g_DisplayMode;
	rdbyteclk = g_MipiByteClock / 1000;
	// printf("\n[PixClock]  : %d MHz\n", rdpixclk);
	rd_Hsw = g_TimingStr.Hsw / g_DisplayMode;
	rd_Hbp = g_TimingStr.Hbp / g_DisplayMode;
	rd_Hactive = g_TimingStr.Hactive / g_DisplayMode;
	// printf(" \n[H]  : Hsw:%d  Hbp:%d  Hactive :%d  \n",   rdhsw, rdhbp, rdhactive);

	m = rd_Hsw + rd_Hbp + rd_Hactive;
	x = m * (rdbyteclk + 1);
	y = x / (rdpixclk - 1);

	if (g_MipiFormat == YUV422_8bit)
	{
		rd_dly = y - (2 * rd_Hactive) / g_MipiSetStr.SetPortLaneNum;
	}
	else if (g_MipiFormat == RGB888)
	{
		rd_dly = y - (3 * rd_Hactive) / g_MipiSetStr.SetPortLaneNum;
	}
	g_RdDly = rd_dly;
}

void MipiVideoSet(void)
{
	chip_write_i2c(0xC21C, 0x00);
	switch (g_MipiSetStr.SetPortLaneNum)
	{
	case 4:
		chip_write_i2c(0xC201, 0x00 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC256, 0x00 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC202, 0x01);
		chip_write_i2c(0xC203, 0x55);
		break;
	case 3:
		chip_write_i2c(0xC201, 0x30 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC256, 0x30 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC202, 0x01);
		chip_write_i2c(0xC203, 0x90);
		break;
	case 2:
		chip_write_i2c(0xC201, 0x20 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC256, 0x20 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC202, 0x02);
		chip_write_i2c(0xC203, 0x58);
		break;
	case 1:
		chip_write_i2c(0xC201, 0x10 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC256, 0x10 | g_MipiSetStr.SetVideoMode | g_MipiType);
		chip_write_i2c(0xC202, 0x03);
		chip_write_i2c(0xC203, 0x00);
		break;
	}
	DelayMs(20);
	chip_write_i2c(0xC200, g_MipiSetStr.SetClockMode);
	if (g_MipiType == DSI) // only DSI needs EOTP
	{
		chip_write_i2c(0xC214, chip_read_i2c(0xC214) | 0x80);
		chip_write_i2c(0xC200, chip_read_i2c(0xC200) | 0x80);
	}
	else
	{
		chip_write_i2c(0xC202, g_RdDly / 256);
		chip_write_i2c(0xC203, g_RdDly % 256);
	}
}

void MipiInitial(void)
{
	VideoCheck();
	MipiLaneSwap();
	MipiPortSet();
	MipiClockSet();
	MipiDphySet();
	if (g_MipiType == DSI)
	{
		InitPanel();
	}
	else
	{
		MipiRdDlyCal();
	}
	ColorSpaceConversion();
	SyncPolAdjust();
	MipiProtocalSet();
	MipiVideoSet();
}
