/******************************
name:AngleControl.c
*******************************/
#include "globalVerble.h"
#include "stdtypes.h"
#include "SCI.h"
extern int g_speed;
extern int SpeedBybianmaqi;
long DistanceBybianmaqi=0;
extern int speedPorN;
extern int readSpeedOrNot;
unsigned long ykl=0;
extern long plan;
void AngleControl(void){
//陀螺仪处理
  int Delta = 0;
 // int acc;
  g_nRealGyro = GYRO*400-GYRORef;       //前正
  AngularGyro += g_nRealGyro;

  //加速度计处理
  //acc = AccRef - Acc;                             //前正
  //误差处理
 // Delta = acc*1 - AngularGyro;
  //////////////////////////
  //AngularGyro += Delta/5;
  //SCI0_SendByte(AngularGyro);
 
 // SCI0_SendByte(acc);              
}                                                   
void AngleControlOutput(void){
//////////////////////////
  ykl++;
  if (ykl%10==0)
    DistanceBybianmaqi -= 5+plan;
  g_lnAngleControlOut = AngularGyro/2000+ g_nRealGyro/200 + DistanceBybianmaqi + SpeedBybianmaqi*0;
}