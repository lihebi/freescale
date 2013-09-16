/************************
SCI模块
content:  SCI0_BR(unsigned long)
              SCI0_Init(();
              SCI0_SendByte(char)
              SCI_Interrupt   //接收中断
*************************/
//串口初始化
#include "derivative.h"
#include "globalVerble.h"

void SCI0_Init(void){
  SCI0CR1 = 0x00;  /* 8 Data Bits, 1 Start Bit, 1 Stop Bit, No Parity *///8位数据格式，无校验

  SCI0CR2 = 0x2C;  /* 使能接收中断;使能 Tx,Rx *///00101100,接收中断使能，发送器使能，接收器使能

  /* SCIASR1, SCIACR1, SCIACR2, SCISR1, SCISR2, SCIDRH & SCIDRL left at default values */
}  
//串口波特率设置
void SCI0_BR(unsigned long br) //在总线为24MHz基础上
{
  uint brPrescaler;
  brPrescaler = (uint)(24000000 / (16 * br));

  /* Set the Baud Rate */
  SCI0BDH = (uchar)((brPrescaler>>8));
  SCI0BDL = (uchar)(brPrescaler);   
}
//串口发送字节
void SCI0_SendByte(char ch) 
{
	/* check SCI transmit data register is empty */
	while(SCI0SR1_TDRE == 0);
//	kkk++;
	SCI0DRL = ch;	
}

#define AAAAA
#ifndef AAAAA

//串口中断
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vsci0  SCI0_ISR(void)
{  

  SCI0CR2_RIE=0;                     //接收中断禁止
  
  while(SCI0SR1_RDRF == 0);
  SCI_Rev = SCI0DRL;
  SCI_Flag = 1;
  
  SCI0CR2_RIE = 1;                  //接收中断使能
}
#pragma CODE_SEG DEFAULT


                     #endif
