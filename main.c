/*��磺
����Ҫ�޸ĵĵط���������һ��Sources���magConrtol.c��һ��speedControl.c���ܹ���������
��˼�Ҷ�д�ڱ�ע���ˡ�
���ǵĳ����Է�����
�ȷ��ڵ��ϣ�Ȼ��򿪵�Դ���ػ��߸�λ�����1��󣬵Ƶ�һ������Ȼ����
��ε�����ʱ���ǳ����ڼ��������ƽ��λ�ã�����һ����Ҫ����
�����˺������㶯����ʱ�ѳ����������3����֮�󣬵ƻ���һ��������ʱ��ʼ����������Ӧ�ÿ�������
�ٹ�2�����ҵȾͿ�ʼ����������������ʱ��״����ÿ��һ����ִ����200�����ڡ�
ף�����
*/







#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Init.h"
#include "control.h"
#include "GYRO.h"
#include "tools.h"
extern int GYRO;
int x=0,y=0,z=0;
int kk = 0;
void main(void) {
  /* put your own code here */
    int i = 0; 
    Init_All();
    DDRB = 0xff;
    PORTB = 0xff;
    
  //  PORTB = 0x00;
    
  /*  PWMDTY0 = 50;
    PWMDTY1 = 0;
    PWMDTY2 = 50;
    PWMDTY3 = 0;
    for(;;);             */
 /*   for(;;){
      
      delay(100);
      x = ADC_GetValue(0);
      //y = ADC_GetValue(15);
      kk++;
    }                                             */
       //    PTT_PTT2 = 1;    //����
  //for(;;){
   // DDRT_DDRT2 = 1;
   // PTIT_PTIT2 = 1; //����
  //  delay(50);
    //PTIT_PTIT2 = 0;
  //  PTT_PTT2 = 0;
  //   PORTB = 0x00;
   // for(;;);
 // }
    //PORTB = 0x00;
  for(i=0;i<500;i++)
   delay(1000);
   PORTB = 0x00;
     
	EnableInterrupts;

     
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


