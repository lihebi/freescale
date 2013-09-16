/********************
name:MotorOutput.c
*********************/
#include "globalVerble.h"
#include "defines.h"
#include "control.h"
int g_speed = 0;
extern long dir;
void MotorSpeedOut(void);
void SetMotorVoltage(int l,int r);
void MotorOutput(void){
  long lnLeft,lnRight;
  lnLeft = g_lnAngleControlOut -dir;
  lnRight = g_lnAngleControlOut +dir;
  g_lnLeftMotorOut = lnLeft;
  g_lnRightMotorOut = lnRight;
  MotorSpeedOut();                
}
void MotorSpeedOut(void){
  long lnLeftVal,lnRightVal;
  lnLeftVal = g_lnLeftMotorOut;
  lnRightVal = g_lnRightMotorOut;
  if(lnLeftVal > 0)
    lnLeftVal += MOTOR_OUT_DEAD_VAL;
  else if(lnLeftVal < 0)
    lnRightVal -= MOTOR_OUT_DEAD_VAL;
  if(lnLeftVal > MOTOR_OUT_MAX)
    lnLeftVal = MOTOR_OUT_MAX;
  if(lnLeftVal < MOTOR_OUT_MIN)
    lnLeftVal = MOTOR_OUT_MIN;
  if(lnRightVal > MOTOR_OUT_MAX)
    lnRightVal = MOTOR_OUT_MAX;
  if(lnRightVal < MOTOR_OUT_MIN)
    lnRightVal = MOTOR_OUT_MIN;
  SetMotorVoltage(lnLeftVal,lnRightVal);
}
void SetMotorVoltage(int l,int r){
g_speed = l;
  LeftSpeed(l);
  RightSpeed(r);
}