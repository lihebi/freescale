/***************************
name:GYRO.c
****************************/
#include "derivative.h"
#include "SPI.h"

byte GYRO_ReadData(byte address)
{
	word command = (word)address;	// ���������Ĵ�����ַ
	
	command <<= 8;
	command |= 0x8000;				// ����Ϊ"��"ָ��
	command &= 0xBFFF;				// ����Ϊ"����չ"ģʽ(8bit)
	
	return (byte)SPI_RdWr_Word(command);
}

byte GYRO_WriteData(byte address, byte data)
{
	word command = (word)address;	// ������д�Ĵ�����ַ
	
	command <<= 8;
	command &= 0x3FFF;				// ����Ϊ"д"ָ��,"����չ"ģʽ
	command |= (word)data;			// ������д����
	
	return (byte)SPI_RdWr_Word(command);
}

void GYRO_Init()
{
	(void)GYRO_WriteData(0x20,0x0F);	// ��Ϊ��ͨģʽ(�ϵ�Ϊ"�͹���ģʽ")
}

int GYRO_ReadX()					// ��ȡX����Ľ��ٶ�
{
	int data;
	data = (word)GYRO_ReadData(0x29);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x28);
	return data;
}

int GYRO_ReadY()					// ��ȡY����Ľ��ٶ�
{
	int data;
	data = (word)GYRO_ReadData(0x2B);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x2A);
	return data;
}

int GYRO_ReadZ()					// ��ȡY����Ľ��ٶ�
{
	int data;
	data = (word)GYRO_ReadData(0x2D);
	data <<= 8;
	data |= (word)GYRO_ReadData(0x2C);
	return data;
}