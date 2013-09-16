/****************************************************************
* File Name:	SPI.c
* Discription:	Include SPI bottom layer function.
				Write and read by SPI protocal.
				Offer SPI_RdWr_Word(word value)
				to top layer.
****************************************************************/

#include "derivative.h"



word SPI_RdWr_Word(word value)	// ��дһ����
{
	while (!SPI0SR_SPTEF);		// �ȴ����ݼĴ�����
	SPI0DR = value;				// д����
	while (!SPI0SR_SPIF );		// �ȴ��������
	return SPI0DR;				// ������
}

void SPI_Init(void)		// SPI��ʼ��
{
	//MODRR_MODRR4 = 1;	// ʹ��M��(������S��)
	//DDRM	= 0x38;		// �����ʼ��IO����
    DDRS = 0x30; 
	SPI0CR1	= 0x5E;		// ʹ��SPI���ر�SPI�жϣ���Ϊ"����"ģʽ��ʱ�ӵ���Ч��ż��λ����
	SPI0CR2	= 0x54;		// ����Ϊ16λ������
	SPI0BR  = 0x03;		// ������BR = ����Ƶ��/��Ƶ���� = BusClk / ((SPPR + 1)�� 2^(SPR + 1))=8M/16=250K
						// ��Ƭ����߲������ʲ��ܸ���25M ���������10M
}

