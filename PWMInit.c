/****************************
name:PWMInit.c
*****************************/
#include "derivative.h"  
void PWMPERInit(void){//周期为100
/*左*/
  PWMPER0 = 0x64;
  PWMPER1 = 0x64;
  /*右 */
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
  PWME = 0x00;     //禁止所有PWM
  PWMPRCLK = 0;   //预分频系数设置，[6:4]为B，[2:0]为A
  PWMSCLA = 24;   //SA预分频系数 Clock SA=Clock A /(2*PWMSCLA)
  PWMSCLB = 24;
  PWMCTL = 0x00;  //设置非级联
  PWMCLK = 0xff;     //选择时钟为SA,SB
  PWMPOL = 0xff;
  PWMCAE = 0x00;
  PWMPERInit();
  PWMDTYInit();
  PWME = 0xff;
}