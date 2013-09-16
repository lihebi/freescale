/****************************
name:PWMInit.c
*****************************/
#include "derivative.h"  
void PWMPERInit(void){//����Ϊ100
/*��*/
  PWMPER0 = 0x64;
  PWMPER1 = 0x64;
  /*�� */
  PWMPER2 = 0x64;
  PWMPER3 = 0x64;
}
void PWMDTYInit(void){
  PWMDTY0 = 0;
  PWMDTY1 = 0;
  PWMDTY2 = 0;
  PWMDTY3 = 0;
}
void PWMInit(void){    
  PWME = 0x00;     //��ֹ����PWM
  PWMPRCLK = 0;   //Ԥ��Ƶϵ�����ã�[6:4]ΪB��[2:0]ΪA
  PWMSCLA = 24;   //SAԤ��Ƶϵ�� Clock SA=Clock A /(2*PWMSCLA)
  PWMSCLB = 24;
  PWMCTL = 0x00;  //���÷Ǽ���
  PWMCLK = 0xff;     //ѡ��ʱ��ΪSA,SB
  PWMPOL = 0xff;
  PWMCAE = 0x00;
  PWMPERInit();
  PWMDTYInit();
  PWME = 0xff;
}