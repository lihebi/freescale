/***************************************
name:Pulse.c
****************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "defines.h"
#include "globalVerble.h"
#include "tools.h"
#define RESET PORTB_PB0
int pacnt = 0;
int portc = 0;
 int j0;
 int j1;
 int j2;
 int j3;
 int j4;
 int j5;
 int j6;
 int j7;
void GetPulseR(void){
  //int m = 1;
 // if(LEFT_CW==0)
  //  m=-1;
 // g_nRightMotorPulseSigma += PORTC;
 g_nRightMotorPulseSigma = PTJ_PTJ0+PTJ_PTJ1*2+PTJ_PTJ2*4+PTJ_PTJ3*8;
  j0=PTJ_PTJ0;
  j1=PTJ_PTJ1;
  j2=PTJ_PTJ2;
  j3=PTJ_PTJ3;
  j4=PORTA_PA4;
  j5=PORTA_PA5;
  j6=PORTA_PA6;
  j7=PORTA_PA7;
  //RESET =0;
 // delay(20);                           
  //RESET = 1;  
}

void GetPulsePTL(void){
 // int k = 1;
  //if(LEFT_CW==0)
   // k=-1;
  pacnt = PACNT;
  g_nLeftMotorPulseSigma += pacnt;
  PACNT = 0x0000;   //«Â¡„
}