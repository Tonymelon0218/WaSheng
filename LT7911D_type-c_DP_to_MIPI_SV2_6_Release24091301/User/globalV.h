#ifndef _GLOBAL_V_H
#define _GLOBAL_V_H

#define OFFSET  5

#define HDCP_En	  0     //1: HDCP EN

#define Traindown_Flag  BKD2_12_REG

#define	ERRCNT_LANE0_H 	chip_read_i2c(0xDB11)
#define	ERRCNT_LANE0_L	chip_read_i2c(0xDB10)
#define	ERRCNT_LANE1_H 	chip_read_i2c(0xDB13)
#define	ERRCNT_LANE1_L	chip_read_i2c(0xDB12)
#define	ERRCNT_LANE2_H 	chip_read_i2c(0xDB15)
#define	ERRCNT_LANE2_L	chip_read_i2c(0xDB14)
#define	ERRCNT_LANE3_H 	chip_read_i2c(0xDB17)
#define	ERRCNT_LANE3_L	chip_read_i2c(0xDB16)

typedef enum
{
	LT7911,
	LT7911D
}_CHIP_MODEL_TYPEDEF;

typedef enum
{
	RGB,
	YUV422,
	YUV444,
}_OUTPUT_MODE_TYPEDEF;

typedef enum
{
	Full_Range = 0x01,
	Limited_Range = 0x00
}_QUANTIZATION_RANGE_TYPEDEF;

typedef enum
{
	RGB888,
	//RGB666,
	//RGB666L,
	//RGB565,
	YUV422_8bit,
	//YUV422_10bit,
	//YUV422_12bit,
	//YUV420
}_MIPI_FORMAT_TYPEDEF;

typedef enum
{
	DSI = 0x00,
	CSI = 0x08 
}_MIPI_TYPE_TYPEDEF;

typedef enum
{
	Port_1lane = 0x01,
	Port_2lane = 0x02,
	Port_3lane = 0x03,	
	Port_4lane = 0x04,
}_PORTLANE_NUM_TYPEDEF;

typedef enum
{
	NonBurst_SyncPulse_Mode = 0x01,//0x09
	NonBurst_SyncEvent_Mode = 0x02,//0x0A
	Burst_Mode = 0x07,//0x0F
}_MIPI_VIDEO_TYPEDEF;

typedef enum
{
	ContinuousClock = 0x20,
	NonContinuousClock = 0x00
}_CLOCK_MODE_TYPEDEF;

typedef enum
{
	VideoCopyMode = 0x01,
	SideBySideMode = 0x02,
}_DISPLAY_MODE_TYPEDEF;

typedef enum
{
	GPIO_AS_OUTPUT = 0x00,
	GPIO_AS_INPUT = 0x01
}_GPIO_MODE_TYPEDEF;
	

typedef struct
{
	u32 PixelClock;
	u16 Htotal;
	u16 Hactive;
	u16 Hfp;
	u16 Hsw;
	u16 Hbp;
	u16 Vtotal;
	u16 Vactive;
	u8 Vfp;
	u8 Vsw;
	u8 Vbp;
	u8 Hspol;
	u8 Vspol;
}TIMING;

typedef struct 
{
	u8 SetPortLaneNum;
	u8 SetVideoMode;
	u8 SetClockMode;
}MIPI;

typedef enum
{
	Typec_Source,
	Dp_Source
}_INPUT_SOURCE_TYPEDEF;

typedef struct
{
	u8 MaxLinkRate;
	u8 MaxLinkCount;
	u8 SSC;
}DPCD;

extern u8 g_InputType ;
extern u16 g_timer1_4scnt;
extern TIMING g_TimingStr ;
extern MIPI g_MipiSetStr;
extern DPCD g_DpcdSetStr;

extern u8 g_ChipModel ;
extern u8 g_DisplayMode;
extern u8 g_OutputMode ;
extern u8 g_MipiFormat ;
extern u8 g_MipiType;
extern u8 g_GpioMode;
extern u8 g_EdidBlockCalEnable;
extern u8 time1_100ms;

extern u32 g_MipiByteClock;
extern u32 g_MipiClock ;
extern u32 g_MipiDatarata ;
extern u8 g_FlagHdcpEn;
extern bool g_FlagVideoChange;
extern bool Flag_Aux_Sleep;
extern u8 DP_HDCP_EN;
extern u32 g_RdDly;
extern u16 g_SampleRate;
#endif