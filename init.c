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
/*������ʱ������Ϊ24MHz���൱�����໷*/
void initPLL(void){			//32M
	CPMUPROT = 0x26;            //����ʱ�����üĴ���   
	CPMUCLKS_PSTP = 0;          //����PLL   
	CPMUCLKS_PLLSEL = 1;        //ѡ��PLL��Ϊϵͳʱ��Դ   
	CPMUOSC_OSCE = 1;           //�ⲿ����ʹ��   
		    
	CPMUSYNR = 0x07;            //fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)   fosc=16MHZ                     
	CPMUREFDIV = 0x03;            
		      
	CPMUPOSTDIV = 0x00;         // PLL CLOCK = VCO CLOCK / (POSTDIV + 1)    
		                              //BUS CLOCK = PLL CLOCK/2   
	_asm(nop);  
	_asm(nop);  
	_asm(nop);
	_asm(nop);	 
  
	CPMUPLL=0x10;               //���໷��Ƶ����,���Լ�������   
		      
	while(CPMUFLG_LOCK == 0);   //�ȴ�PLL�ȶ�      
	CPMUPROT = 0x00;            //�رձ���ʱ��   
}
void SetBusClock_24MHz(void)
{   
  CPMUOSC_OSCE = 1; 
  CPMUSYNR = 0x00 | 0x05;       /* VCOFRQ[7:6], SYNDIV[5:0]����Ƶ���ӣ� */ //��仰����ֿ��������Ĵ�����һ����7~6��һ����5~0.����д����˿ɶ���      
  CPMUREFDIV = 0x20 | 0x03;     /* REFFRQ[7:6], REFDIV[3:0]�����շ�Ƶ���ӣ� */       
  CPMUPOSTDIV = 0x00;           /* POSTDIV = 0 FPLL = FVCO  */ //Frequency ratio between the VCOCLK and PLLCLK
  while(!CPMUFLG_LOCK);         /* wait for VCO to stabilize*/   //�ȴ�ѹ�������ȶ�  voltage controlled oscillator           			 
  Service_WD();                 /*********ΪʲôҪ�������Ź�����������������������������������������������********/
  CPMUCLKS_PLLSEL = 1;          /* Switch clk to use PLL    */   //�ı�ʱ��Ϊ���໷
}

void ADC_Init(void)
{
  ATDCTL1 = 0x3F;  /* 10-Bit resolution ,discharge before sampling. *///10λ�ֱ��ʣ�����ǰ�ŷţ���              
  ATDCTL3 = 0x88;  /* Right Justified Data, Single conversion sequence *///�������Ϊ�Ҷ��롣��һת��˳��              
  ATDCTL4 = 0xE1;  /* 6 MHz, Notice: 12MHz Max ATD Clock, Fatdlk = FBUS/(2*(PRS+1)) */ //����Ƶ��12MHz����
}

void initAPI(void){			//200us
	CPMUAPICTL_APIFE =0;		//���趨ֵ֮ǰ��Ҫ���㣻	                
	CPMUAPICTL_APIE =0;     	//��ʹ���ж�����
	CPMUAPICTL_APICLK=1;  		//0:ʹ��Autonomous Clock;	1:ʹ��BUS CLOCK������ʹ��BUS CLK           
		
	//CPMUACLKTR=0xFC;  		// fACLK is trimmed to 10KHz�����ʹ�õ���Auto Clock ��Ҫ���ô˼Ĵ��� Ϊ0xfc  

	//CPMUAPIR=3199;              //ʹ��BUS CLK, Period = 2*(APIR[15:0] + 1) *(1/32 000 000HZ)�˴���ʱ200 us
	CPMUAPIR=30000;                           	//��ʹ��AUTO CLK ��0.2��x+1��=y ms �綨ʱ10ms ֵΪ49
	                           		
	CPMUAPICTL_APIF=1;      	//�жϱ�־λ���� 
	
	CPMUAPICTL_APIFE = 1;
  CPMUAPICTL_APIE  = 1;
}

void OutputCompare_Init(void)
{
  TSCR1_TEN = 0;      /* Disable Timer module before adjusting registers.    *///�����Ĵ���ǰ��ֹʱ�ӵ���
  TIOS_IOS6 = 1;      /* Set Channel 0 as output compare.                    *///����ͨ��0Ϊ����Ƚ�
  TCTL1_OM6 = 0;      /* Set channel 0 to toggle when a Timer match occurs.  *///����ʱ��ƥ��ʱ����ͨ��0Ϊ����
  TCTL1_OL6 = 1;      /* Set channel 0 to toggle when a Timer match occurs.  */
  TC6       = 0x1D4C; /* Set a value for channel 0 timer compare.            *///����ͨ��0�Ƚϵ�ֵ �����������������ʱ������ж�
  TIE_C6I   = 1;      /* Enable channel 0 interrupt, handled by function TIM0ISR. *///ʹ��ͨ��0�жϣ���TIMOISR��������
  TSCR1_TSWAI = 1;    /* Disables the timer module while in wait mode.    *///�ڵȴ�ģʽ�н�ֹʱ�ӵ���
  TSCR1_TSFRZ = 1;    /* Disables the timer counter while in freeze mode. *///���䶳ģʽ�н�ֹʱ�Ӽ���
  TSCR2_PR    = 0x4;  /* Set prescaler to divide by 16                   *///Ԥ��Ƶϵ��128
  TSCR2_TCRE  = 1;                                                         //ʱ�����������ʹ��
  TSCR1_TEN   = 1;    /* Timer Enable.                                    *///ʱ��ʹ��
  //�ж����ڣ�0x1D4C*16/24MHz = 5ms        f=200
}
void PITInit(void){
  PACTL = 0x52;      //PA������ʹ�ܣ������ز�׽��ֻ��ʹ��IOC7(T7)��)���¼�����ģʽ��ʹ��PACLKΪʱ�ӣ�����ж�ʹ�ܣ������ۼ������жϽ�ֹ
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



