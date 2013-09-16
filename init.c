/***************************************************
name:init.c
***************************************************/
#include "derivative.h"      /* derivative-specific definitions */
#include "tools.h"
#include "MMA7660.h"
#include "PWMInit.h"
#include "SCI.h"
#include "SPI.h"
#include "GYRO.h"
long plan = 0;
/*把总线时钟设置为24MHz，相当于锁相环*/
void initPLL(void){			//32M
	CPMUPROT = 0x26;            //保护时钟配置寄存器   
	CPMUCLKS_PSTP = 0;          //禁用PLL   
	CPMUCLKS_PLLSEL = 1;        //选择PLL作为系统时钟源   
	CPMUOSC_OSCE = 1;           //外部晶振使能   
		    
	CPMUSYNR = 0x07;            //fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)   fosc=16MHZ                     
	CPMUREFDIV = 0x03;            
		      
	CPMUPOSTDIV = 0x00;         // PLL CLOCK = VCO CLOCK / (POSTDIV + 1)    
		                              //BUS CLOCK = PLL CLOCK/2   
	_asm(nop);  
	_asm(nop);  
	_asm(nop);
	_asm(nop);	 
  
	CPMUPLL=0x10;               //锁相环调频启用,用以减少噪音   
		      
	while(CPMUFLG_LOCK == 0);   //等待PLL稳定      
	CPMUPROT = 0x00;            //关闭保护时钟   
}
void SetBusClock_24MHz(void)
{   
  CPMUOSC_OSCE = 1; 
  CPMUSYNR = 0x00 | 0x05;       /* VCOFRQ[7:6], SYNDIV[5:0]（分频因子） */ //这句话是想分开赋两个寄存器。一个是7~6，一个是5~0.这样写提高了可读性      
  CPMUREFDIV = 0x20 | 0x03;     /* REFFRQ[7:6], REFDIV[3:0]（参照分频因子） */       
  CPMUPOSTDIV = 0x00;           /* POSTDIV = 0 FPLL = FVCO  */ //Frequency ratio between the VCOCLK and PLLCLK
  while(!CPMUFLG_LOCK);         /* wait for VCO to stabilize*/   //等待压控振荡器稳定  voltage controlled oscillator           			 
  Service_WD();                 /*********为什么要重启看门狗？？？？？？？？？？？？？？？？？？？？？？？********/
  CPMUCLKS_PLLSEL = 1;          /* Switch clk to use PLL    */   //改变时钟为锁相环
}

void ADC_Init(void)
{
  ATDCTL1 = 0x3F;  /* 10-Bit resolution ,discharge before sampling. *///10位分辨率，采样前排放？？              
  ATDCTL3 = 0x88;  /* Right Justified Data, Single conversion sequence *///结果调整为右对齐。单一转换顺序              
  ATDCTL4 = 0xE1;  /* 6 MHz, Notice: 12MHz Max ATD Clock, Fatdlk = FBUS/(2*(PRS+1)) */ //总线频率12MHz？？
}

void initAPI(void){			//200us
	CPMUAPICTL_APIFE =0;		//在设定值之前需要清零；	                
	CPMUAPICTL_APIE =0;     	//不使能中断申请
	CPMUAPICTL_APICLK=1;  		//0:使用Autonomous Clock;	1:使用BUS CLOCK，这里使用BUS CLK           
		
	//CPMUACLKTR=0xFC;  		// fACLK is trimmed to 10KHz，如果使用的是Auto Clock 则要设置此寄存器 为0xfc  

	//CPMUAPIR=3199;              //使用BUS CLK, Period = 2*(APIR[15:0] + 1) *(1/32 000 000HZ)此处定时200 us
	CPMUAPIR=30000;                           	//若使用AUTO CLK ，0.2（x+1）=y ms 如定时10ms 值为49
	                           		
	CPMUAPICTL_APIF=1;      	//中断标志位清零 
	
	CPMUAPICTL_APIFE = 1;
  CPMUAPICTL_APIE  = 1;
}

void OutputCompare_Init(void)
{
  TSCR1_TEN = 0;      /* Disable Timer module before adjusting registers.    *///调整寄存器前禁止时钟调制
  TIOS_IOS6 = 1;      /* Set Channel 0 as output compare.                    *///设置通道0为输出比较
  TCTL1_OM6 = 0;      /* Set channel 0 to toggle when a Timer match occurs.  *///当定时器匹配时设置通道0为开关
  TCTL1_OL6 = 1;      /* Set channel 0 to toggle when a Timer match occurs.  */
  TC6       = 0x1D4C; /* Set a value for channel 0 timer compare.            *///设置通道0比较的值 即当计数到这个个数时则进入中断
  TIE_C6I   = 1;      /* Enable channel 0 interrupt, handled by function TIM0ISR. *///使能通道0中断，由TIMOISR函数控制
  TSCR1_TSWAI = 1;    /* Disables the timer module while in wait mode.    *///在等待模式中禁止时钟调制
  TSCR1_TSFRZ = 1;    /* Disables the timer counter while in freeze mode. *///在冷冻模式中禁止时钟计数
  TSCR2_PR    = 0x4;  /* Set prescaler to divide by 16                   *///预分频系数128
  TSCR2_TCRE  = 1;                                                         //时间计数器重置使能
  TSCR1_TEN   = 1;    /* Timer Enable.                                    *///时钟使能
  //中断周期：0x1D4C*16/24MHz = 5ms        f=200
}
void PITInit(void){
  PACTL = 0x52;      //PA计数器使能，上升沿捕捉（只能使用IOC7(T7)口)，事件计数模式，使用PACLK为时钟，溢出中断使能，脉冲累加输入中断禁止
  PACNT = 0x0000; //Clear
}
void select_plan() {
  unsigned long i;
  DDRB = 0xFF;
  DDRT = 0x04;
  PORTB = 0xFF;
  for (i=0; i<6000000; i++) {
    if (PORTA>100) {
      PTT_PTT2 = 1;
      PORTB_PB7 = ~PORTB_PB7;
      plan ++;
     _asm(nop);  
    	_asm(nop);  
    	_asm(nop);
   	_asm(nop);
   	    	_asm(nop);
   	_asm(nop);
   	    	_asm(nop);
   	_asm(nop);
   	    	_asm(nop);
   	_asm(nop);
   	    	_asm(nop);
   	_asm(nop);
    PTT_PTT2 = 0;
    }
  }
  for (i=0; i<1000000; i++) PORTB = 0;
}

void Init_All(void){

 // SetBusClock_24MHz();
   //initPLL();
  //eOSC_SetBusCLK_2nM(24);
  initPLL();
  initAPI();
  PWMInit();
  ADC_Init();
  select_plan();
//  OutputCompare_Init();
//  PITInit();
 // Init_MMA();
  //SCI0_BR(38400);
  //SCI0_Init(); 
  //SPI_Init();
  //GYRO_Init();  
  DDRT_DDRT2 = 1;
}



