#include "include.h"

u8 g_FlagHdcpEn;
u8 g_ChipModel ;
u8 g_DisplayMode;
u8 g_OutputMode ;
u8 g_MipiFormat ;
u8 g_MipiType;

u8 g_GpioMode;
u8 g_EdidBlockCalEnable;
u8 g_InputType ;
u8 time1_100ms;
u16 g_timer1_4scnt;
u32 g_MipiByteClock = 0;
bool g_FlagVideoChange = FALSE;

bool Flag_Aux_Sleep;
u8 DP_HDCP_EN;
u32 g_RdDly;
u16 g_SampleRate;