
#include "include.h"

#define LPK_DI 0x29
#define SPK_DI 0x15

code u8 dcsrst[] = {0x05, 0x01, 0x00};
//*************************************
// Sleep-Out
//*************************************
code u8 Sleep_Out[] = {0x05, 0x11, 0x00};
code u8 Sleep_IN[] = {0x05, 0x10, 0x00};
// DELAY	120
//  Display-On
//*************************************
code u8 Display_On[] = {0x05, 0x29, 0x00};
code u8 Set_address_mode[] = {0x15, 0x36, 0x00};
code u8 Set_pixel_format[] = {0x15, 0x3A, 0x00};
#define CMDNUM (44)

code u8 dcs0[] = {0x58, 0x00};
code u8 dcs1[] = {0x09, 0x01};
code u8 dcs2[] = {0xff, 0x00};
code u8 dcs3[] = {0x0a, 0x0b};
code u8 dcs4[] = {0x0b, 0x28};
code u8 dcs5[] = {0xff, 0x00};
code u8 dcs6[] = {0x10, 0x20};
code u8 dcs7[] = {0x11, 0x00};
code u8 dcs8[] = {0x12, 0x62};
code u8 dcs9[] = {0x13, 0x62};
code u8 dcs10[] = {0x18, 0x6c};
code u8 dcs11[] = {0x19, 0x0f};
code u8 dcs12[] = {0x1a, 0x00};
code u8 dcs13[] = {0x1b, 0x00};
code u8 dcs14[] = {0x20, 0x80};
code u8 dcs15[] = {0x21, 0x07};

code u8 dcs16[] = {0x24, 0xb0};
code u8 dcs17[] = {0x25, 0x04};
code u8 dcs18[] = {0x26, 0x80};
code u8 dcs19[] = {0x27, 0x07};

code u8 dcs20[] = {0x28, 0x20};
code u8 dcs21[] = {0x29, 0x00};
code u8 dcs22[] = {0x2a, 0x20};
code u8 dcs23[] = {0x2b, 0x00};
code u8 dcs24[] = {0x2c, 0x14};
code u8 dcs25[] = {0x2d, 0x00};
code u8 dcs26[] = {0x2e, 0x14};
code u8 dcs27[] = {0x2f, 0x00};
code u8 dcs28[] = {0x30, 0x04};
code u8 dcs29[] = {0x31, 0x00};

code u8 dcs30[] = {0x32, 0x04};
code u8 dcs31[] = {0x33, 0x00};
code u8 dcs32[] = {0x34, 0x0c};
code u8 dcs33[] = {0x35, 0x00};
code u8 dcs34[] = {0x36, 0x14};
code u8 dcs35[] = {0x37, 0x00};
code u8 dcs36[] = {0x38, 0x34};
code u8 dcs37[] = {0x39, 0x00};
code u8 dcs38[] = {0x3a, 0x13};
code u8 dcs39[] = {0x3b, 0x00};

code u8 dcs40[] = {0xff, 0x00};
code u8 dcs41[] = {0x0d, 0x01};
code u8 dcs42[] = {0xff, 0x00};
code u8 dcs43[] = {0x09, 0x00};

code u8 *cmdlist[] = {
	dcs0, dcs1, dcs2, dcs3, dcs4, dcs5, dcs6, dcs7, dcs8, dcs9, dcs10, 
	dcs11, dcs12, dcs13, dcs14, dcs15, dcs16, dcs17, dcs18, dcs19, dcs20, 
	dcs21, dcs22, dcs23, dcs24, dcs25, dcs26, dcs27, dcs28, dcs29, dcs30, 
	dcs31, dcs32, dcs33, dcs34, dcs35, dcs36, dcs37, dcs38, dcs39, dcs40, 
	dcs41, dcs42, dcs43 //,dcs44,dcs45,dcs46,dcs47,dcs48,dcs49
};

code u8 cmdlen[] = {
	sizeof(dcs0), sizeof(dcs1), sizeof(dcs2), sizeof(dcs3), sizeof(dcs4), sizeof(dcs5), 
	sizeof(dcs6), sizeof(dcs7), sizeof(dcs8), sizeof(dcs9), sizeof(dcs10), sizeof(dcs11), 
	sizeof(dcs12), sizeof(dcs13), sizeof(dcs14), sizeof(dcs15), sizeof(dcs16), sizeof(dcs17),
	sizeof(dcs18), sizeof(dcs19), sizeof(dcs20), sizeof(dcs21), sizeof(dcs22), sizeof(dcs23), 
	sizeof(dcs24), sizeof(dcs25), sizeof(dcs26), sizeof(dcs27), sizeof(dcs28), sizeof(dcs29), 
	sizeof(dcs30), sizeof(dcs31), sizeof(dcs32), sizeof(dcs33), sizeof(dcs34), sizeof(dcs35), 
	sizeof(dcs36), sizeof(dcs37), sizeof(dcs38), sizeof(dcs39), sizeof(dcs40), sizeof(dcs41), 
	sizeof(dcs42), sizeof(dcs43) //,sizeof(dcs44),sizeof(dcs45),sizeof(dcs46),sizeof(dcs47),sizeof(dcs48),sizeof(dcs49)
};

void DcsPktWrite(u8 DCS_DI, u8 Len, u8 *Ptr)
{
	u8 i = 0;
	chip_write_i2c(0xC21C, 0x40); // Write enable;
	if (Len == 2)
	{
		chip_write_i2c(0xC218, 0x0C); // Hardware calculate ecc and crc&LP mode send pkt enable&Short pkt
		chip_write_i2c(0xC219, 0x04);
		chip_write_i2c(0xC234, DCS_DI);
		chip_write_i2c(0xC234, *Ptr);
		chip_write_i2c(0xC234, *(Ptr + 1));
	}
	else
	{
		chip_write_i2c(0xC218, 0x0E);
		chip_write_i2c(0xC219, Len + 6);
		chip_write_i2c(0xC234, DCS_DI);
		chip_write_i2c(0xC234, Len);
		chip_write_i2c(0xC234, 0x00);
		for (i = 0; i < Len; i++)
		{
			chip_write_i2c(0xC234, *Ptr);
			Ptr++;
		}
	}
	DelayMs(1);
	chip_write_i2c(0xC218, 0x00);
}

void InitPanel(void)
{
	u8 dcslen = 0, i = 0;
	for (i = 0; i < CMDNUM; i++)
	{
		dcslen = cmdlen[i]; // sizeof(dcs##CMDNUM(i));
		if (dcslen == 2)
			DcsPktWrite(SPK_DI, dcslen, cmdlist[i]); // shot
		else if (dcslen > 2)
			DcsPktWrite(LPK_DI, dcslen, cmdlist[i]); // long
	}
	DcsPktWrite(Sleep_Out[0], (sizeof(Sleep_Out) - 1), &Sleep_Out[1]);
	DelayMs(150);
	//	DcsPktWrite( Set_address_mode[0], ( sizeof( Set_address_mode ) - 1 ), &Set_address_mode[1] );
	//	DelayMs(150);
	//	DcsPktWrite( Set_pixel_format[0], ( sizeof( Set_pixel_format ) - 1 ), &Set_pixel_format[1] );
	DcsPktWrite(Display_On[0], (sizeof(Display_On) - 1), &Display_On[1]);
	DelayMs(200);
}

/************************************** The End Of File **************************************/
