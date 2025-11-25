//////////////////////////////////////
//Project:   LT8712
//Filename:  type.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _TypeC_H
#define _TypeC_H

//#include "type.h"
#define	SendNoneMeg	0xA0
#define	SendFstMeg	0xAA
#define	SendSndMeg	0xAB
#define	SendThirdMeg	0xAC

#define	CcIdleStatus	0xB0
#define	RvdDataMeg	0xBA
#define	RvdEopMeg	0xBB
#define	SendSopMeg	0xBC

//Control Msg Type
#define   GoodCRC_M     		  	 0x01
#define   GotoMin     		       0x02
#define   Accept     		         0x03
#define   Reject      		       0x04
#define   Ping        		       0x05
#define   PS_RDY      		  		 0x06
#define   Get_Source_Cap    		 0x07
#define   Get_Sink_Cap      		 0x08
#define   DR_Swap           		 0x09
#define   PR_Swap           		 0x0A
#define   VCONN_Swap	   				 0x0B
#define   Wait              	 	 0x0C
#define   Soft_Reset        		 0x0D


//Data Msg Type
#define   Source_Capabilities     0x01
#define   Request     		        0x02
#define   BIST     		            0x03
#define   Sink_Capabilities      	0x04
#define   Vendor_Defined        	0x0f

//SVDM
#define   Discover_Identity     	0x01
#define   Discover_SVIDs     	    0x02
#define   Discover_Modes     		  0x03
#define   Enter_Mode      	      0x04
#define   Exit_Mode      	        0x05
#define   Attention        	      0x06
#define   DP_Status_Updata        0x10 //16
#define   DP_Config              	0x11 //17
#define   DP_Status_Updata_ACK	  0x50 //17
#define   DP_Config_ACK  			    0x51
#define   DP_Config_NACK   			  0x91

#define   InitStart 			 	      0x00
#define   AttentionSend  			    0x01
#define   DPStart 					      0x02
#define   DPEnd 					        0x03

extern u8 TypecRXHeadCount;
extern u8 TypecRXCount;
extern u8 CcRxMsgHeader[2];
extern u8 CcRxRvdData[32];
extern u8 CcRxRvdDatalenth;
extern bool ReadEn;
extern bool GoodCRC;
extern u8 LastPG;
extern bool SendEN;
extern u8 MsgType;
extern u8 TotalData;
extern u8 DataOrder;
extern bool send_over;
extern bool nack_loop;
extern bool loop_send;
extern bool VDM_en;
extern IDATA bool  Attention_Flag;

void TypeC(void);
void TypeCInit(void);
void TypecTmpInit(void);
void Send_Message(void);
void Recive(void);
void UFP_ReadMessage(void);
void delay_us(u16 t);

void Typec_Initial(void);
#endif
