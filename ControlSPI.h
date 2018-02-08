/**
  ******************************************************************************
  * @file    ControlSPI.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   Ginkgo USB-SPI�������ײ�������API��������.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef _CONTROLSPI_H_
#define _CONTROLSPI_H_

#include <stdint.h>
#include "ErrorType.h"

#define             OS_LINUX
#ifndef OS_LINUX
#include <Windows.h>
#endif

//���������Ͷ���
#define VSI_USBSPI		(2)

//1.Ginkgoϵ�нӿڿ���Ϣ���������͡�
typedef  struct  _VSI_BOARD_INFO{
#if false
	uint16_t	dr_Version;			//��������汾�ţ���16 ���Ʊ�ʾ��
	uint16_t	in_Version;			//�ӿڿ�汾�ţ���16 ���Ʊ�ʾ��
    uint8_t     spi_Num;			//��ʾ�м�·SPI ͨ����
    char        str_hw_Name[100];	//Ӳ�����ƣ����硰Ginkgo-SPI-Adaptor����ע�⣺�����ַ�����������\0����
    char        str_fw_Version[100];//�̼��汾�ַ��������硰2.0.0����ע�⣺�����ַ�����������\0����
    char        str_hw_Version[100];//Ӳ���汾�ַ��������硰2.1.0����ע�⣺�����ַ�����������\0����
    char        str_Serial_Num[100];//���������к��ַ���
	uint16_t	Reserved[4];		//ϵͳ������
#endif
    uint8_t     ProductName[32];
    uint8_t     FirmwareVersion[4];
    uint8_t     HardwareVersion[4];
    uint8_t     SerialNumber[12];
} VSI_BOARD_INFO,*PVSI_BOARD_INFO; 


//2.�����ʼ��SPI����������
typedef struct _VSI_INIT_CONFIG{
    uint8_t     ControlMode;	//SPI���Ʒ�ʽ:0-Ӳ�����ƣ�ȫ˫��ģʽ��,1-Ӳ�����ƣ���˫��ģʽ����2-������ƣ���˫��ģʽ��,3-������ģʽ�����������������ΪMOSI
    uint8_t     TranBits;		//���ݴ����ֽڿ�ȣ���8~16֮��ȡֵ
    uint8_t     MasterMode;		//����ѡ�����:0-�ӻ���1-����
    uint8_t     CPOL;			//ʱ�Ӽ��Կ���:0-SCK����Ч��1-SCK����Ч
    uint8_t     CPHA;			//ʱ����λ����:0-��һ��SCKʱ�Ӳ�����1-�ڶ���SCKʱ�Ӳ���
    uint8_t     LSBFirst;		//������λ��ʽ:0-MSB��ǰ��1-LSB��ǰ
    uint8_t     SelPolarity;	//Ƭѡ�źż���:0-�͵�ƽѡ�У�1-�ߵ�ƽѡ��
	uint32_t	ClockSpeed;		//SPIʱ��Ƶ��:��λΪHZ
} VSI_INIT_CONFIG,*PVSI_INIT_CONFIG;

#ifdef __cplusplus
extern "C"
{
#endif
int32_t   VSI_ScanDevice(uint8_t NeedInit=1);
int32_t   VSI_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
int32_t   VSI_CloseDevice(int32_t DevType,int32_t DevIndex);
int32_t   VSI_InitSPI(int32_t DevType, int32_t DevIndex, PVSI_INIT_CONFIG pInitConfig);
int32_t   VSI_ReadBoardInfo(int32_t DevType, PVSI_BOARD_INFO pInfo);
int32_t   VSI_WriteBytes(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t *pData,uint16_t Len);
int32_t   VSI_ReadBytes(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t *pData,uint16_t Len);
int32_t   VSI_WriteReadBytes(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t* pWriteData,uint16_t WriteLen,uint8_t * pReadData,uint16_t ReadLen);
int32_t   VSI_WriteBits(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t *pWriteBitStr);
int32_t   VSI_ReadBits(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t *pReadBitStr,int32_t ReadBitsNum);
int32_t   VSI_WriteReadBits(int32_t DevType,int32_t DevIndex,int32_t SPIIndex,uint8_t *pWriteBitStr,uint8_t *pReadBitStr,int32_t ReadBitsNum);

int32_t   VSI_SlaveReadBytes(int32_t DevType,int32_t DevIndex,uint8_t *pReadData,int32_t *pBytesNum,int32_t WaitTime);
int32_t   VSI_SlaveWriteBytes(int32_t DevType,int32_t DevIndex,uint8_t *pWriteData,int32_t WriteBytesNum);
#ifdef __cplusplus
}
#endif

#endif

