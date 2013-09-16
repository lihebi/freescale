/****************************************************************
* File Name:	SPI.c
* Discription:	Include SPI bottom layer function.
				Write and read by SPI protocal.
				Offer SPI_RdWr_Word(word value)
				to top layer.
****************************************************************/

#include "derivative.h"



word SPI_RdWr_Word(word value)	// 读写一个字
{
	while (!SPI0SR_SPTEF);		// 等待数据寄存器空
	SPI0DR = value;				// 写数据
	while (!SPI0SR_SPIF );		// 等待传输完成
	return SPI0DR;				// 读数据
}

void SPI_Init(void)		// SPI初始化
{
	//MODRR_MODRR4 = 1;	// 使用M口(而不是S口)
	//DDRM	= 0x38;		// 必须初始化IO方向
    DDRS = 0x30; 
	SPI0CR1	= 0x5E;		// 使能SPI，关闭SPI中断，设为"主机"模式，时钟低有效，偶相位采样
	SPI0CR2	= 0x54;		// 设置为16位传输宽度
	SPI0BR  = 0x03;		// 波特率BR = 总线频率/分频因子 = BusClk / ((SPPR + 1)· 2^(SPR + 1))=8M/16=250K
						// 单片机最高操作速率不能高于25M 陀螺仪最高10M
}

