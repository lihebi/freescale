#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "Pulse.h"
#include "MMA7660.h"
#include "tools.h"
#include "globalVerble.h"
#include "AngleControl.h"
#include "MotorOutput.h"
#include "magControl.h"
#include "speedControl.h"

extern int kk;
int flash = 0;
int readSpeedOrNot = 0;
long L = 0;
long dir = 0;

#pragma CODE_SEG NON_BANKED

void interrupt VectorNumber_Vapi Control(void){  //200us
 readSpeedOrNot++;
 if(readSpeedOrNot%16 == 0){
  //readSpeedOrNot = 0;
readSpeed();
 }
 kk++;
 if(kk==200){
  kk=0;
  if(flash)PORTB =~PORTB; 
 }
 GYRO = ADC_GetValue(0);
 L = (long)ADC_GetValue(1);
 dir = L-60;
  time++;
  if(time<400){
    GYRORef += GYRO;
     CPMUAPICTL_APIF=1;
    return;
  }
  if(time==400){
    //GYRORef /= 399;
    PORTB = 0xff;
    
  }
  if(time<2000){
    CPMUAPICTL_APIF = 1;
    return;
  }
  if(time == 2000)
    PORTB = 0x00;
  if(time == 2600)
    flash = 1;
  AngleControl();
  AngleControlOutput();
 // speedControl();
 // speedControlOutput();
  //magControl();
  MotorOutput();
 
 
 
	CPMUAPICTL_APIF=1;	// clean the Interrupt Flag
}