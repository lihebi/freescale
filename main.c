/*斌哥：
你需要修改的地方有两处，一是Sources里的magConrtol.c，一是speedControl.c，总共两个参数
意思我都写在备注里了。
我们的车调试方法：
先放在地上，然后打开电源开关或者复位，大概1秒后，灯第一次亮，然后灭，
这段灯亮的时间是车子在检测陀螺仪平衡位置，所以一定不要动他
灯灭了后可以随便动，这时把车立正，大概3秒钟之后，灯会再一次亮，这时开始工作，放手应该可以立了
再过2秒左右等就开始闪，这是正常工作时的状况，每闪一次是执行了200个周期。
祝你愉快
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
       //    PTT_PTT2 = 1;    //置零
  //for(;;){
   // DDRT_DDRT2 = 1;
   // PTIT_PTIT2 = 1; //置零
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


