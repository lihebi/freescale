/******************************
name:control.c
*******************************/
#include "defines.h"
#include "derivative.h"      /* derivative-specific definitions */
#include "globalVerble.h"
int speedPorN = 0;             //速度方向，1为正，-1为负
void RightSpeed(int speed){
  if(speed>=0){
    RIGHT_CCW = 0;
    RIGHT_CW = (byte)speed;
  }
  if(speed<0){
    speed = - speed;
    RIGHT_CW = 0;
    RIGHT_CCW = (byte)speed;
  }
}
void LeftSpeed(int speed){
  distance += speed;
  if(speed>=0){
  speedPorN = 1;
    LEFT_CCW = 0;
    LEFT_CW = (byte)speed;
  }
  if(speed<0){
  speedPorN = -1;
    speed = - speed;
    LEFT_CW = 0;
    LEFT_CCW = (byte)speed;
  }
  
}