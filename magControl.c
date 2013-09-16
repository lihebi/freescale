/*电磁检测*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "tools.h"
#include "globalVerble.h"
int DirDelta = 0;   //电磁检测偏差。直接返回值



void magControl(){
  DirDelta = ADC_GetValue(1); 
  
  
  //电磁参数修改处   
  g_nDirControlOut = DirDelta*1;   //这个里面的1是参数，你调试一下。决定了电磁的影响有多大，值越大转到越猛。
                                   //注意正负
}
