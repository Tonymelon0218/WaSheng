#ifndef _EDID_H
#define _EDID_H

extern u8 Edid[256];

void EDID_Dtb_Block_Calc(u8 *Pbuf);
void EDID_CheckSum_Calc(u8 *pbuf);
void UpdateEdid(void);
#endif

