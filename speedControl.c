/*�ٶȿ���*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "globalVerble.h"
  int g_naimSpeed = 0;
void speedControl(){
  g_naimSpeed = 20;    //Ŀ���ٶȣ����Ե��ģ�*�ٶȿ����޸Ĵ�*��
                       //�������ó��ٶȣ�ֱ�Ӽӵ�����ϣ��൱��ֱ�Ӹ����Ӹ��ٶ�
                       //��ֵСһ�㣬��֤����ǰ��������
  
}

void speedControlOutput(){
  g_nSpeedControlOut = g_naimSpeed;
}