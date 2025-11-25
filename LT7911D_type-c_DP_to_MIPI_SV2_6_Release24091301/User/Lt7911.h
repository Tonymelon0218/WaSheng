#ifndef _LT7911_H
#define _LT7911_H

void DelayMs(u16 var);
void chip_write_i2c(u8 xdata *p ,u8 val);
u8 chip_read_i2c(u8 xdata *p );
void Lt7911_InitialSteps(void);
void DPCD_Parameter(u32 Addr, u8 Data);
extern void IRQ_Send(void);

void SET_GPIO5_HIGH(void);
void SET_GPIO5_LOW(void);
void SET_I2S_D2_HIGH(void);
void SET_I2S_D2_LOW(void);

void linkAux_TypecEvb_CC1(void);
void linkAux_TypecEvb_CC2(void);
#endif
