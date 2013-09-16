/************************************
name:MMA7660 operation for 128g
*************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "globalVerble.h"

#define SCL PORTA_PA0 
#define SDA PORTA_PA1 
#define SCL_dir DDRA_DDRA0
#define SDA_dir DDRA_DDRA1

#define  BUS_CLOCK		   32000000	   //����Ƶ��
#define  OSC_CLOCK		   16000000	   //����Ƶ��

#define somenop(); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");

signed char X_value,Y_value,Z_value;
signed char X_value_final,Y_value_final,Z_value_final;   //������ٶȵ�����ֵ


/*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void IICdelay(void) 
{
 unsigned int i;
 for(i=0;i<5000;i++);
}

/*************************************************************/
/*                        ��ʼ��IIC                          */
/*************************************************************/
void INIT_IIC(void) 
{

 SCL_dir = 1;
 SCL_dir = 1;
 SCL = 1;
 SDA = 1;
}


/*************************************************************/
/*                         ����IIC                           */
/*************************************************************/
void I2Cstart(void) 
{
  SCL_dir = 1;
  SDA_dir = 1;
  SDA = 1;
  somenop();
  SCL = 1;
  somenop();
  somenop();
  SDA = 0;
  somenop();
  somenop();
  SCL = 0;
}


/*************************************************************/
/*                       IIC��������                         */
/*************************************************************/
void I2Csend(byte data) 
{
 unsigned char i=8;
 SCL_dir = 1;
 SDA_dir = 1;
 while(i) 
 {
      SCL = 0;  
      somenop();
      SDA=(data&0x80)>>7; 
      data<<=1; 
      somenop();
      SCL = 1;
      somenop();
      somenop();
      i--;     
 }
 SCL = 0;
 SDA_dir = 0;
}

/*************************************************************/
/*                       IIC��������                         */
/*************************************************************/
signed char I2Creceive(void) 
{
 unsigned char i=8;
 unsigned char data=0;

 SCL_dir = 1;
 SDA_dir = 0;
 while(i) 
 {
      SCL = 0;  
      somenop();
      somenop();
      SCL = 1;
      somenop();
      data<<=1;
      data|=SDA;
      somenop();
      i--;     
 }
 SCL = 0;
 return(data);
}

/*************************************************************/
/*                      IIC��ȡӦ��λ                        */
/*************************************************************/
void I2Creadack(void) 
{
  SCL_dir = 1;
  SDA_dir = 0;
  SCL = 0;
  somenop();
  somenop();
  SCL = 1;
  somenop();
  if(SDA == 1) 
  {
     for(;;) ;  
  }
  somenop();
  SCL = 0;
  somenop();
  somenop();
}

/*************************************************************/
/*                      IIC����Ӧ��λ                        */
/*************************************************************/
void I2Csendack(void) 
{
  SCL_dir = 1;
  SDA_dir = 1;
  SCL = 0;
  somenop();
  SDA = 0;
  somenop();
  SCL = 1;
  somenop();
  somenop();
  SCL = 0;
  somenop();
  somenop();
}

/*************************************************************/
/*                         ֹͣIIC                           */
/*************************************************************/
void I2Cstop(void) 
{
  SCL_dir = 1;
  SDA_dir = 1;
  SCL = 0;
  SDA = 0;
  somenop(); 
  somenop();
  SCL = 1;
  somenop();
  SDA = 1; 
  somenop(); 
  somenop();
  SCL_dir = 0;
  SDA_dir = 0;
}

/*************************************************************/
/*                    ��ʼ�����ٶȴ�����                     */
/*************************************************************/
void INIT_MMA7660(void) 
{
    I2Cstart();
    I2Csend(0x98);    //���ʹӻ���ַ��д�����
    I2Creadack();
    I2Csend(0x07);          //д��Ĵ�����ַ
    I2Creadack();
    I2Csend(0x01);          //���üĴ�����ֵ,��������2g�����ò���ģʽ
    I2Creadack();
    I2Cstop();
}

/*************************************************************/
/*                       ��ȡ3����ٶ�                       */
/*************************************************************/
void read3axle(void) 
{
      I2Cstart();
      I2Csend(0x98);               //���ʹӻ���ַ��д�����
      I2Creadack();
      I2Csend(0x00);               //д�����ȡ�ĵ�һ���Ĵ�����ַ
      I2Creadack();
      I2Cstart();
      I2Csend(0x99);               //���ʹӻ���ַ����ȡ����
      I2Creadack();
      X_value = I2Creceive();      //��ȡX����ٶ�
      I2Csendack();
      Y_value = I2Creceive();      //��ȡY����ٶ�
      I2Csendack();
      Z_value = I2Creceive();      //��ȡZ����ٶ�
      I2Cstop();
      //���ɼ���������ת����-32~31֮��
      X_value= X_value<<2;
      X_value_final = X_value /4;
      Y_value= Y_value<<2;
      Y_value_final = Y_value /4;
      Z_value= Z_value<<2;
      Z_value_final = Z_value /4;
}

void Init_MMA(void){
  INIT_IIC();
  INIT_MMA7660();
}