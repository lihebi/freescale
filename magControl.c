/*��ż��*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "tools.h"
#include "globalVerble.h"
int DirDelta = 0;   //��ż��ƫ�ֱ�ӷ���ֵ



void magControl(){
  DirDelta = ADC_GetValue(1); 
  
  
  //��Ų����޸Ĵ�   
  g_nDirControlOut = DirDelta*1;   //��������1�ǲ����������һ�¡������˵�ŵ�Ӱ���ж��ֵԽ��ת��Խ�͡�
                                   //ע������
}
