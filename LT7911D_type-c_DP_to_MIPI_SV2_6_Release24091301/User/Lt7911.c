#include "include.h"

void InitTime0Inter(void)
{
	// TMOD &= 0xF0;
	TMOD = 0x11; // time0 16bit
	TR0 = 0;	 // disable
	IT1 = 0;	 // TCON = 0x05;
	TH0 = 0xF7;	 // reloaed 300us
	TL0 = 0x40;	 //

	TR1 = 0; // 1
	TH1 = 0xB1;
	TL1 = 0xE0;

	IE = 0x8e; // EA=1;EX=1;ET1=0;ET0=1;
}

void SystemClk(void)
{
	BK90_62_REG = 0x99; // System clk sel 24M
}

void linkAux_TypecEvb_CC1(void)
{
	BKB0_12_REG = 0x3c;
	BKDA_A3_REG = 0x4b; // rx lane swap
	BKDA_A4_REG = 0x05; // 	PN swap
	BKB0_30_REG = 0x46;
}

void linkAux_TypecEvb_CC2(void)
{
	BKDA_A3_REG = 0xe1; // rx lane swap
	BKDA_A4_REG = 0x05; // polarity swap
	BKB0_30_REG = 0x42;
	BKB0_12_REG = 0x3e;
}

void linkAux_TypecEvb(void)
{
	BKC1_AF_REG = 0xC3; // vconn
	BKDA_FC_REG = 0x0f; // Odd and evern
	BKDA_A3_REG = 0xe1; // rx lane swap
	BKDA_A4_REG = 0x05; // polarity swap
	BKB0_30_REG = 0x42;

	BKD8_00_REG = 0x11 | DP_HDCP_EN; // EQ hardware mode;HDCP disable
	BKB0_12_REG = 0x3e;
	hardmode_flag = 0;
	Dpcd107_Write = 0;
}

void HPD_High(void)
{
	BKD0_05_REG |= 0x40; // AUX HPD
	BKA0_30_REG = 0x80;	 // DP_RX_HPD
	BKC0_06_REG = 0x08;	 // HDMI_RX_HPD
}

void CC_INT(void)
{
	BKA0_90_REG = 0xFB; // disable ucc int mask
	BKB0_05_REG = 0x6F;
	delay1ms1(1);
	BKB0_05_REG = 0xE0;
	delay1ms1(1);
	BKB0_05_REG = 0x2B; // CC TX PHY disable
}

void AUX_INT(void)
{
	BKD0_05_REG |= 0x03; // AUX SOFT MODE
	BKA0_A1_REG = 0xff;
	BKA0_A1_REG = 0x7f; // clear interrupt 2
	BKA0_91_REG = 0x7f; // interupt bit 7: AuxRx_int_mask
}

void Video_INT(void)
{
	BKD2_19_REG = 0x00;	 // Bit[0]set1 :Rg_video_out_int_en
	BKD2_1C_REG = 0xfe;	 // Bit[0]set0 :Rg_video_out_int_clr
	BKA0_90_REG &= 0xfe; // INT0 Mask
	BKA0_A0_REG &= 0xfe; // INT0 Clear
}

void Attention_Send(void)
{
	if (Enter_AltMode == 0x01)
	{
		Enter_AltMode = 0x00;

		if (LastPG == DP_Config)
		{
			Attention_Flag = 1;
			LastPG = Attention;
			send_over = 0;
		}
		if (LastPG == Attention)
		{
			delay1ms1(600);
			DataOrder = 7; // send Request
			TotalData = 10;
			LastPG = 0xFF;
			Send_Message();
			send_over = 0;
			AUX_INT();
			Video_INT();
			HPD_High();
			DPEnable = 1;
		}
	}
}

void RebulidEdid(void)
{
#if 0
	if(g_DisplayMode == VideoCopyMode)
	{
		g_TimingStr.PixelClock = 148500;
		g_TimingStr.Htotal = 2200;
		g_TimingStr.Hactive = 1920;
		g_TimingStr.Hfp = 88;
		g_TimingStr.Hsw = 44;
		g_TimingStr.Hbp = 148;
		g_TimingStr.Vtotal = 1125;
		g_TimingStr.Vactive = 1080;
		g_TimingStr.Vfp = 4;
		g_TimingStr.Vsw = 5;
		g_TimingStr.Vbp = 36;
		g_TimingStr.Hspol = 1;
		g_TimingStr.Vspol = 1;
		 
	

	}
    else 
    {
		g_TimingStr.PixelClock = 297000;
		g_TimingStr.Htotal = 4400;
		g_TimingStr.Hactive = 3840;
		g_TimingStr.Hfp = 176;
		g_TimingStr.Hsw = 88;
		g_TimingStr.Hbp =296;
		g_TimingStr.Vtotal = 1125;
		g_TimingStr.Vactive = 1080;
		g_TimingStr.Vfp = 4;
		g_TimingStr.Vsw = 5;
		g_TimingStr.Vbp = 36;
		g_TimingStr.Hspol = 1;
		g_TimingStr.Vspol = 1;
		
		
	}
#endif

	if (g_EdidBlockCalEnable)
	{
		EDID_Dtb_Block_Calc(Edid + 0x36);
		EDID_Dtb_Block_Calc(Edid + 0x48);
	}
	EDID_CheckSum_Calc(Edid);
}

void DPCD_Parameter(u32 Addr, u8 Data)
{
	// D855: bit[7]: 0:aux mode; 1:reg mode
	// D852: DPCD[19:16]
	// D851: DPCD[15:8]
	// D850: DPCD[7:0]
	// D853: Data
	BKD8_55_REG = 0x80; // Aux reg mode
	BKD8_52_REG = ((Addr >> 16) & 0x0f);
	BKD8_51_REG = ((Addr >> 8) & 0xff);
	BKD8_50_REG = (Addr & 0xff);
	BKD8_53_REG = Data;
}

void DPCD_Init(void)
{
	DPCD_Parameter(0x00000, 0x12);								 // DPCD Rev
	DPCD_Parameter(0x00001, g_DpcdSetStr.MaxLinkRate);			 // Max Lane Rate
	DPCD_Parameter(0x00002, (g_DpcdSetStr.MaxLinkCount | 0x80)); // Max Lane Count
	DPCD_Parameter(0x00003, g_DpcdSetStr.SSC);					 // SSC
	DPCD_Parameter(0x00004, 0x01);								 // Receive port
	DPCD_Parameter(0x00005, 0x00);								 // Downstream port
	DPCD_Parameter(0x00006, 0x00);								 // 8B10B Code
	DPCD_Parameter(0x00007, 0x01);								 // Downstream count
	DPCD_Parameter(0x00008, 0x02);								 // Local EDID
	DPCD_Parameter(0x00009, 0x00);								 // No care
	DPCD_Parameter(0x0000A, 0x00);								 // No care
	DPCD_Parameter(0x0000B, 0x00);								 // No care
	DPCD_Parameter(0x0000D, 0x00);								 // eDP , No care
	DPCD_Parameter(0x0000E, 0x04);								 // Training Time No care
	DPCD_Parameter(0x0000F, 0x00);								 // No care

	DPCD_Parameter(0x00020, 0x00);
	DPCD_Parameter(0x00021, 0x00);
	DPCD_Parameter(0x00200, 0x01); // Sink Count
}

void IRQ_Send(void)
{
	if (g_InputType == Typec_Source)
	{
		DataOrder = 10; // send IRQ
		TotalData = 10;
		Send_Message();
	}
	else
	{
		BKC0_06_REG = 0x00; // RX_HPD low
		delay1ms1(1);
		BKC0_06_REG = 0x08; // RX_HPD high
	}
}

// void PCR_Reset(void)
//{
//	BK90_07_REG = 0xF7;
//	delay1ms1(10);
//	BK90_07_REG = 0xFF;

//	BK90_0D_REG = 0xDF;
//	delay1ms1(10);
//	BK90_0D_REG = 0xFF;
//}

void SET_GPIO5_HIGH(void)
{
	BKA0_46_REG |= 0x80;
	BKA0_46_REG &= 0xBF; // GPIO5 select gpo_out[4]
	BKB0_8C_REG |= 0x70;
	BKA0_48_REG |= 0x04; // High
}

void SET_GPIO5_LOW(void)
{
	BKA0_46_REG |= 0x80;
	BKA0_46_REG &= 0xBF; // GPIO5 select gpo_out[4]
	BKB0_8C_REG |= 0x77;
	BKA0_48_REG &= 0xFB; // Low
}

void ENABLE_VYSNC(void)
{
	BKB0_8D_REG |= 0x07;
	BKA0_46_REG &= 0xF7;
	BKA0_46_REG |= 0x04;
}

void DISABLE_VSYNC(void)
{
	BKB0_8D_REG |= 0x07;
	BKA0_46_REG |= 0x0C;
}

void SET_I2S_D2_HIGH(void)
{
	BKA0_46_REG = BKA0_46_REG | 0x08;
	BKB0_8D_REG = 0x07;
	BKA0_48_REG = BKA0_48_REG | 0x10; // High
}

void SET_I2S_D2_LOW(void)
{
	BKA0_46_REG = BKA0_46_REG | 0x08;
	BKB0_8D_REG = 0x07;
	BKA0_48_REG = BKA0_48_REG & 0xef; // Low
}

#if 0
void SavePower(void)
{
	//For C/DP Input 
	BK90_51_REG = 0xfc;//disable CDR clock for data lane based on how many lanes you used 
	BK90_57_REG = 0xf9;//disable DPRX main link lane based on how many lanes you used 
	BK90_58_REG = 0x33;//disable DPRX main link lane cdr clock based on how many lanes you used 
	BK90_5A_REG = 0xfc;//disable HDMI RX Sys_clk and tmds_clk
	BK90_5B_REG = 0x00;//disable HDMI RX...
	BK90_5C_REG = 0x00;//disable HDMI RX...
	BK90_5D_REG = 0x18;//disable HDMI RX and LVDS TX...
	BK90_5E_REG = 0x88;//disable unused MIPITX port...
	BK90_5F_REG = 0x18;//disable unused MIPITX port...
	BK90_61_REG = 0x11;//disable unused MIPITX port...
	
	BKB0_1F_REG = 0x0C;//PD unuse lane PI
	//BKB0_00_REG = 0xc0;//Close Audio
	BKB0_44_REG = 0xc4;//disable port0
	BKB0_55_REG = 0x04;//disable port1
	BKB0_66_REG = 0x04;//disable port2
	
	BKB0_2E_REG = 0x2C;//afe_pd
}
#endif

void VideoChangeDetect(void)
{
	u16 rd_Htotal, rd_Hactive;
	u16 rd_Vtotal, rd_Vactive;

#if 1 ////take video from MSA
	rd_Htotal = chip_read_i2c(0xD1DB) << 8;
	rd_Htotal = rd_Htotal + chip_read_i2c(0xD1DC);

	rd_Hactive = chip_read_i2c(0xD1E7) << 8;
	rd_Hactive = rd_Hactive + chip_read_i2c(0xD1E8);

	rd_Vtotal = chip_read_i2c(0xD1DD) << 8;
	rd_Vtotal = rd_Vtotal + chip_read_i2c(0xD1DE);

	rd_Vactive = chip_read_i2c(0xD1E9) << 8;
	rd_Vactive = rd_Vactive + chip_read_i2c(0xD1EA);

#endif

	if ((g_TimingStr.Htotal != rd_Htotal) ||
		(g_TimingStr.Hactive != rd_Hactive) ||
		(g_TimingStr.Vtotal != rd_Vtotal) ||
		(g_TimingStr.Vactive != rd_Vactive))
	{
		g_FlagVideoChange = TRUE;
	}
	else
	{
		g_FlagVideoChange = FALSE;
	}
}

void FsValueChangeDetect(void)
{
	u16 SampleRate;

	SampleRate = chip_read_i2c(0xD154) << 8;
	SampleRate = SampleRate + chip_read_i2c(0xD155);

	if (((SampleRate < 34) && (SampleRate > 30)) || ((SampleRate < 46) && (SampleRate > 42)) || ((SampleRate < 50) && (SampleRate > 46)) || ((SampleRate < 90) && (SampleRate > 86)) || ((SampleRate < 98) && (SampleRate > 94)) || ((SampleRate < 178) && (SampleRate > 174)) || ((SampleRate < 194) && (SampleRate > 190)))

	{
		if ((SampleRate < (g_SampleRate - 0x02)) || (SampleRate > (g_SampleRate + 0x02)))
		{

			SET_GPIO5_HIGH();
			DelayMs(200);
			SET_GPIO5_LOW();
		}
		g_SampleRate = SampleRate;
	}
	else if (SampleRate == 0)
	{
		if (SampleRate != g_SampleRate)
		{
			g_SampleRate = SampleRate;
			SET_GPIO5_HIGH();
			DelayMs(200);
			SET_GPIO5_LOW();
		}
	}
}

void Lt7911_InitialSteps(void)
{
	volatile u8 count = 0;
	bool FlagIRQSend = 0;
	bool FlagMipiOK = 0;
	g_SampleRate = 0;
	g_FlagHdcpEn = 0;
	DP_HDCP_EN = 0x00;
	delay1ms1(200); // wait sram load flash done;
	// g_timer1_4scnt = 0;
	SystemClk();
	Lt7911D_FwVersionSet();
	SET_GPIO5_LOW();
	InitTime0Inter();
	BKC1_17_REG = 0x01;
	//	UpdateEdid();
	RebulidEdid();
	DP_Initial();
	DPCD_Init();
	//	DISABLE_VSYNC();
	Traindown_Flag = FALSE;
	FlagVideoOK = FALSE;
	Flag_Aux_Sleep = FALSE;
	g_FlagVideoChange = FALSE;
	BKD2_21_REG = 0x8F;
	BKD2_22_REG = 0xFF;
	BKD2_67_REG = 0x22;
	if (g_InputType == Typec_Source)
	{
		CC_INT();
		TypeCInit();
		linkAux_TypecEvb(); // CC2
	}
	else
	{
		EA = 1;
		DPEnable = 1;
		AUX_INT();
		Video_INT();
		HPD_High();
	}
	while (1)
	{
		if (g_InputType == Typec_Source)
		{
			Attention_Send();
		}

		if (Hsync_Release) // Stable Hsync
		{
			count++;
			if (count == 10)
			{
				count = 0;
				if (Traindown_Flag || g_FlagVideoChange || Flag_Aux_Sleep) // Aux Trainning done
				{
					if (((BKB8_B0_REG & 0x20)) && (BKB8_B0_REG & 0x40)) // RXPLL and pixpll lock
					{
						DelayMs(200);
						if (!LaneErrorCheck()) // 100ms内不超过10个error
						{
							Traindown_Flag = FALSE;
							FlagVideoOK = TRUE;
							g_FlagVideoChange = FALSE;
							Flag_Aux_Sleep = FALSE;
							Dp_Audio();
							AUX_INT();
							MipiInitial();
							FlagMipiOK = 1;
							DelayMs(10);
							time1_100ms = 0;
							count = 0;
							ENABLE_VYSNC(); // Enable I2S D2 output Vsync

							g_SampleRate = chip_read_i2c(0xD154) << 8;
							g_SampleRate = g_SampleRate + chip_read_i2c(0xD155);
							SET_GPIO5_HIGH();
							DelayMs(200);
							SET_GPIO5_LOW();
						}
						else
						{
							//							EQ_Scan();
						}
					}
				}
				else
				{
					VideoChangeDetect();
					if (LaneErrorCheck())
					{
						if (!Flag_Aux_Sleep)
						{
							FlagVideoOK = FALSE;
							Flag_Aux_Sleep = TRUE;
							SET_GPIO5_HIGH();
							DelayMs(200);
							SET_GPIO5_LOW();
						}
					}
				}
			}
#if HDCP_En == 1
			if (FlagVideoOK)
			{
				if (LaneErrorCheck())
				{
					if (BKDB_A4_REG & 0x40)
					{
						BKB0_0B_REG = 0xD5;
					}
				}
				if (BKDB_A4_REG & 0x02)
				{
					if (!g_FlagHdcpEn)
					{
						g_FlagHdcpEn = 1;
					}
				}
				else
				{
					if (g_FlagHdcpEn)
					{
						delay1ms1(250);
						g_FlagHdcpEn = 0;
						IRQ_Send();
						delay1ms1(500);
						FlagIRQSend = 1;
					}
				}
				if (FlagIRQSend)
				{
					FlagIRQSend = 0;
				}
			}
#endif
		}
		else
		{
			count = 0;
			if (Traindown_Flag || FlagVideoOK)
			{
				time1_100ms++;
				delay1ms1(1);
				if (time1_100ms == 200) // delay1ms1(100);
				{
					time1_100ms = 0;
					if ((!(BKB8_B0_REG & 0x20)) && (BKB8_B0_REG & 0x40)) // RXPLL Lock but pixpll unlock
					{
						if (!Hsync_Release) // PCR problem
						{
							BKD8_00_REG = 0x01 | DP_HDCP_EN;
							PCR_Reset();
						}
					}
					else if (((BKB8_B0_REG & 0x20)) && (BKB8_B0_REG & 0x40))
					{
						if (!LaneErrorCheck()) // Skew problem
						{
							MVidCheck();
						}
						else
						{
							// EQ_Scan();
							Training_Reset();
						}
					}
				}
				if (FlagVideoOK)
				{
					FlagVideoOK = FALSE;
					if (!Flag_Aux_Sleep)
					{
						FlagVideoOK = FALSE;
						Flag_Aux_Sleep = TRUE;
						SET_GPIO5_HIGH();
						DelayMs(200);
						SET_GPIO5_LOW();
					}
				}
			}
		}
	}
}
