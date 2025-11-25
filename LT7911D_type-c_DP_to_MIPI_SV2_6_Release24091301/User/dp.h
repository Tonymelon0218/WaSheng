//////////////////////////////////////
// Project:   LT8712
// Filename:  LT8712.h
// Version:   V1.0
// Copyright: Lontium
//////////////////////////////////////
#ifndef _DP_H
#define _DP_H

#include "type.h"

// #define  2ND_CDR				1
#define Swing_En 1

#define Hsync_Release (BKD2_17_REG & 0x40)

#define CMD_DPCDW 0x80
#define CMD_DPCDR 0x90
#define CMD_I2CW 0x40
#define CMD_I2CR 0x50
#define CMD_I2CD 0x60
#define CMD_I2CS 0x10

#define CMD_I2CLW 0x00
#define CMD_I2CLR 0x10
#define CMD_I2CLD 0x20

#define AUXACK 0x00
#define AUXNACK 0x10
#define AUXDEFER 0x20

extern u8 DPEnable;
extern IDATA u8 AuxEdidOffset;
extern IDATA u8 AuxRxCounter;
extern IDATA u8 AuxRxData[16];
extern IDATA u8 AuxRxSendData[16];
extern IDATA u8 AuxRxCmd;
extern IDATA u8 AuxRxAddress[3];
extern IDATA u8 AuxRxLength;
extern IDATA u8 AuxRxPreCmd;
extern IDATA u8 AuxRxPreAddress[3];
extern IDATA u8 AuxRxPreLength;
extern IDATA bool FlagVideoOK;
extern code EQ_Index[16][2];
extern u8 GetRxAuxData(void);
extern u8 GetDpcdData(void);
extern void ReadDpcd(u8 lenth);
extern void SendAckReply(void);
extern void SendDeferReply(void);
extern void RxAuxSendData(u8 lenth);
extern void WriteDpcd(u8 lenth);
extern void WriteLinkEdid(void);
extern void LastWriteLinkEdid(void);
extern void DcsShortPktWrite(u8 DataID, u8 Data0, u8 Data1);
extern void DcsShortPktWrite_1(u8 DataID, u8 Data0, u8 Data1);
extern void DcsShortPktWrite_2(u8 DataID, u8 Data0, u8 Data1);
extern void DcsLongPkt(u8 DataID, u8 Len);
extern u8 ShortPacketECC(u8 Data_ID, u8 Data_0, u8 Data_1);
extern u8 len;
extern u8 Buf[];
extern IDATA u8 hardmode_flag;
extern IDATA bool Dpcd107_Write;
// extern IDATA bool Traindown_Flag ;
extern u8 Edid[256];
void Dp_Audio(void);
void delay1ms1(u16 var);
void DP_Initial(void);
bool LaneErrorCheck(void);
void EQ_Scan(void);
void MVidCheck(void);
void PCR_Reset(void);
u8 GetDPCDParameter(u8 Addr);
void Training_Reset(void);
#endif
