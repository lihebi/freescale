/************************
SCIģ��
content:  SCI0_BR(unsigned long)
              SCI0_Init(();
              SCI0_SendByte(char)
              SCI_Interrupt   //�����ж�
*************************/
//���ڳ�ʼ��
#include "derivative.h"
#include "globalVerble.h"

void SCI0_Init(void){
  SCI0CR1 = 0x00;  /* 8 Data Bits, 1 Start Bit, 1 Stop Bit, No Parity *///8λ���ݸ�ʽ����У��

  SCI0CR2 = 0x2C;  /* ʹ�ܽ����ж�;ʹ�� Tx,Rx *///00101100,�����ж�ʹ�ܣ�������ʹ�ܣ�������ʹ��

  /* SCIASR1, SCIACR1, SCIACR2, SCISR1, SCISR2, SCIDRH & SCIDRL left at default values */
}  
//���ڲ���������
void SCI0_BR(unsigned long br) //������Ϊ24MHz������
{
  uint brPrescaler;
  brPrescaler = (uint)(24000000 / (16 * br));

  /* Set the Baud Rate */
  SCI0BDH = (uchar)((brPrescaler>>8));
  SCI0BDL = (uchar)(brPrescaler);   
}
//���ڷ����ֽ�
void SCI0_SendByte(char ch) 
{
	/* check SCI transmit data register is empty */
	while(SCI0SR1_TDRE == 0);
//	kkk++;
	SCI0DRL = ch;	
}

#define AAAAA
#ifndef AAAAA

//�����ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vsci0  SCI0_ISR(void)
{  

  SCI0CR2_RIE=0;                     //�����жϽ�ֹ
  
  while(SCI0SR1_RDRF == 0);
  SCI_Rev = SCI0DRL;
  SCI_Flag = 1;
  
  SCI0CR2_RIE = 1;                  //�����ж�ʹ��
}
#pragma CODE_SEG DEFAULT


                     #endif
