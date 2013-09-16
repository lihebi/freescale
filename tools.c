/********************************
name:tools.c
*********************************/
#include "stdtypes.h"
#include "derivative.h"      /* derivative-specific definitions */
#include "stdtypes.h"           //����ʹ��uint��������

int i;

int SpeedBybianmaqi = 0;
extern long DistanceBybianmaqi;
extern int speedPorN;
/*delay*/
void delay(long m){
  while(m--);
}
/*Service_WD*/
void Service_WD(void)   //���밴��˳��������ֵ���������Ź�
{
   CPMUARMCOP = 0x55; 
   CPMUARMCOP = 0xAA;
}
/*ADC_GetValue*/                                      
uint ADC_GetValue(byte ch)        
{
  ATDCTL5 = 0x0F & ch;  /* Start Continuous Conversions on ch */              //��ʼ��ch����ת��
  while (!ATDSTAT0_SCF);  /* wait for conversion sequence to complete   */    //�ȴ�ת�����   
  return ATDDR0;                                                              //���ؽ��
}

void readSpeed(void){
  
  SpeedBybianmaqi = PORTA;
  PTT_PTT2 = 1;
  DistanceBybianmaqi+=SpeedBybianmaqi*speedPorN;
  _asm(nop);  
	_asm(nop);  
	_asm(nop);
	_asm(nop);
  PTT_PTT2 = 0;
}
  
