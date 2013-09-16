/****************************
name:globalVerble.c
*****************************/
#include "stdtypes.h"
/*读数相关*/
int time = 0;
uint GYRO;
uint GYROOld;
int AccOld;
int Acc;
int GYRORef = 0;
int g_nRealGyro;
int AccRef = -1;
int g_nRightMotorPulseSigma = 0;
int g_nLeftMotorPulseSigma   = 0;
/*控制相关*/
long g_lnLeftMotorOut           = 0;
long g_lnRightMotorOut         = 0;
long g_lnAngleControlOut      = 0;
int g_nSpeedControlOut      = 0;
int g_nDirControlOut = 0;

long distance = 0;

long AngularGyro = 0;
long AccIntegral = 0;