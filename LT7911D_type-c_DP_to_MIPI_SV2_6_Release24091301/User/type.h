
#ifndef _TYPE_H
#define _TYPE_H

#include <stddef.h>

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;


typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}
bool;

typedef  enum
{
	Low    = 0,
	High   = !Low
}
HPD_Status;

typedef  enum
{
	Off    = 0,
	On   = !Off
}
LED_Status,PI_Power_Status;

typedef  enum
{
	Disable    = 0,
	Enable   = !Disable
}
Audio_Status,EDID_Status,INT_Status,INT_CLK_STABLE_Status,TX_Status;

typedef  enum
{
	RGB_3_1=0,
	YCC422_4_1=1,
	YCC422_3_1=2,
	YCC420_3_1=3
}
Color_Space_Ratio_Status;

#ifndef min
#define min(a,b) (((a)<(b))? (a):(b))
#endif

#ifndef max
#define max(a,b) (((a)>(b))? (a):(b))
#endif

//////////////////////////////////////////////
// Keil C
//////////////////////////////////////////////
#define DATA              data
#define BDATA             bdata
#define IDATA             idata//256bytes
#define PDATA             pdata
#define XDATA             xdata///1k
#define RDATA             code

#define CBYTE             ((unsigned char volatile code  *) 0)
#define DBYTE             ((unsigned char volatile data  *) 0)
#define PBYTE             ((unsigned char volatile pdata *) 0)
#define XBYTE             ((unsigned char volatile xdata *) 0)
#define IBYTE             ((unsigned char volatile idata *) 0)

#define BIT_0      0x01
#define BIT_1      0x02
#define BIT_2      0x04
#define BIT_3      0x08
#define BIT_4      0x10
#define BIT_5      0x20
#define BIT_6      0x40
#define BIT_7      0x80

#endif