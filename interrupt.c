/************************************
name:interrupt.c
*************************************/
#ifdef aaaaa

#include "Pulse.h"
#include "MMA7660.h"
#include "tools.h"
#include "globalVerble.h"
#include "AngleControl.h"
#include "MotorOutput.h"
int Test = 0;
extern int kk;


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vtimch6 TIM6_ISR(void)   
{
 // TFLG1 = TFLG1_C6F_MASK;
    kk++;
   // PORTB = 0x00;
/*  time++;
  if(time<400){
   
  GYRORef += ADC_GetValue(0);
  
  Test = 1;
  //return;
  }
  if(time == 400){
 
    
    GYRORef /= 400;
    PORTB = 0x00;
    Test = 0;
  } 
  */
  if(kk==180)
    PORTB = 0x00;
  if(kk==200) {
    
    kk=0;
    PORTB = 0xff;
  }
  
                
  /*读数阶段*/
  //GetPulseR();
  //GetPulsePTL();
 // AccOld = Acc;    
  //read3axle(); 
  //Acc = Z_value_final;
  //////////////////////
  //Acc = AccOld*3/4+Acc/4;
  //GYROOld = GYRO;       
//  if(Test==0){
//     kk++;
/*  GYRO = ADC_GetValue(0); 
  ////////////////////////
  //GYRO = GYRO/4 + GYROOld*3/4 ; 
  AngleControl();
  AngleControlOutput();
  MotorOutput();
      */
  
//  }                
  /*清除中断标志*/
  TFLG1 = TFLG1_C6F_MASK;
  TCNT = 0x0000;
}
#pragma CODE_SEG DEFAULT
#endif                           
