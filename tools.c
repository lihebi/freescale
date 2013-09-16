/********************************
name:tools.c
*********************************/
#include "stdtypes.h"
#include "derivative.h"      /* derivative-specific definitions */
#include "stdtypes.h"           //可以使用uint等类型了

int i;

int SpeedBybianmaqi = 0;
extern long DistanceBybianmaqi;
extern int speedPorN;
/*delay*/
void delay(long m){
  while(m--);
}
/*Service_WD*/
void Service_WD(void)   //必须按此顺序赋这两个值。重启看门狗
{
   CPMUARMCOP = 0x55; 
   CPMUARMCOP = 0xAA;
}
/*ADC_GetValue*/                                      
uint ADC_GetValue(byte ch)        
{
  ATDCTL5 = 0x0F & ch;  /* Start Continuous Conversions on ch */              //开始对ch持续转换
  while (!ATDSTAT0_SCF);  /* wait for conversion sequence to complete   */    //等待转换完成   
  return ATDDR0;                                                              //返回结果
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
  
