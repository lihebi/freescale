/***************************
name:GYRO.c
****************************/
#include "derivative.h"
#include "SPI.h"

byte GYRO_ReadData(byte address)
{
	word command = (word)address;	// 设置所读寄存器地址
	
	command <<= 8;
	command |= 0x8000;				// 设置为"读"指令
	command &= 0xBFFF;				// 设置为"非扩展"模式(8bit)
	
	return (byte)SPI_RdWr_Word(command);
}

byte GYRO_WriteData(byte address, byte data)
{
	word command = (word)address;	// 设置所写寄存器地址
	
	command <<= 8;
	command &= 0x3FFF;				// 设置为"写"指令,"非扩展"模式
	command |= (word)data;			// 设置所写数据
	
	return (byte)SPI_RdWr_Word(command);
}

void GYRO_Init()
{
	(void)GYRO_WriteData(0x20,0x0F);	// 设为普通模式(上电为"低功耗模式")
}

int GYRO_ReadX()					// 读取X方向的角速度
{
	int data;
	data = (word)GYRO_ReadData(0x29);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x28);
	return data;
}

int GYRO_ReadY()					// 读取Y方向的角速度
{
	int data;
	data = (word)GYRO_ReadData(0x2B);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x2A);
	return data;
}

int GYRO_ReadZ()					// 读取Y方向的角速度
{
	int data;
	data = (word)GYRO_ReadData(0x2D);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x2C);
	return data;
}