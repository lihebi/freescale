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

#define  BUS_CLOCK		   32000000	   //总线频率
#define  OSC_CLOCK		   16000000	   //晶振频率

#define somenop(); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");

signed char X_value,Y_value,Z_value;
signed char X_value_final,Y_value_final,Z_value_final;   //三轴加速度的最终值


/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void IICdelay(void) 
{
 unsigned int i;
 for(i=0;i<5000;i++);
}

/*************************************************************/
/*                        初始化IIC                          */
/*************************************************************/
void INIT_IIC(void) 
{

 SCL_dir = 1;
 SCL_dir = 1;
 SCL = 1;
 SDA = 1;
}


/*************************************************************/
/*                         启动IIC                           */
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
/*                       IIC发送数据                         */
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
/*                       IIC接收数据                         */
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
/*                      IIC读取应答位                        */
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
/*                      IIC发送应答位                        */
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
/*                         停止IIC                           */
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
/*                    初始化加速度传感器                     */
/*************************************************************/
void INIT_MMA7660(void) 
{
    I2Cstart();
    I2Csend(0x98);    //发送从机地址，写入操作
    I2Creadack();
    I2Csend(0x07);          //写入寄存器地址
    I2Creadack();
    I2Csend(0x01);          //设置寄存器的值,设置量程2g，设置测量模式
    I2Creadack();
    I2Cstop();
}

/*************************************************************/
/*                       读取3轴加速度                       */
/*************************************************************/
void read3axle(void) 
{
      I2Cstart();
      I2Csend(0x98);               //发送从机地址，写入操作
      I2Creadack();
      I2Csend(0x00);               //写入待读取的第一个寄存器地址
      I2Creadack();
      I2Cstart();
      I2Csend(0x99);               //发送从机地址，读取操作
      I2Creadack();
      X_value = I2Creceive();      //读取X轴加速度
      I2Csendack();
      Y_value = I2Creceive();      //读取Y轴加速度
      I2Csendack();
      Z_value = I2Creceive();      //读取Z轴加速度
      I2Cstop();
      //将采集到的数据转换到-32~31之间
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