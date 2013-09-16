/*速度控制*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "globalVerble.h"
  int g_naimSpeed = 0;
void speedControl(){
  g_naimSpeed = 20;    //目标速度，可以调的（*速度控制修改处*）
                       //就是设置初速度，直接加到电机上，相当于直接给他加个速度
                       //数值小一点，保证能往前进就行了
  
}

void speedControlOutput(){
  g_nSpeedControlOut = g_naimSpeed;
}