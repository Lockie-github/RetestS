/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_usart.c
 * ժҪ��
 *  
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
#include <stdio.h>
#include "main.h"
#include "driver_usart1.h"
/*
 * ����ȫ�ֱ���
*/
UART_HandleTypeDef husart1;

/*
 *  ��������void DEBUG_USART_Init(uint32_t baudrate)
 *  ���������baudrate-���ڲ�����
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��USART�Ĳ����ʣ��շ�ѡ����Ч����λ��
*/
void DEBUG_USART_Init(uint32_t baudrate)
{
    husart1.Instance         = DEBUG_USART;             // ѡ��USART1
    husart1.Init.BaudRate    = baudrate;                // ���ò�����
    husart1.Init.WordLength  = USART_WORDLENGTH_8B;     // ����������ЧλΪ8bit
    husart1.Init.StopBits    = USART_STOPBITS_1;        // ����һλֹͣλ
    husart1.Init.Parity      = USART_PARITY_NONE;       // ����У��λ
    husart1.Init.Mode        = USART_MODE_TX_RX;        // ���տɷ�
    husart1.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
    
    // ʹ�ÿ⺯����ʼ��USART3�Ĳ���
    if (HAL_UART_Init(&husart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/*****************************************************
*function:	д�ַ��ļ�����
*param1:	������ַ�
*param2:	�ļ�ָ��
*return:	����ַ���ASCII��
******************************************************/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&husart1, (uint8_t*)&ch, 1, 10);
	return ch;
}

/*****************************************************
*function:	���ַ��ļ�����
*param1:	�ļ�ָ��
*return:	��ȡ�ַ���ASCII��
******************************************************/
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&husart1, (uint8_t*)&ch, 1, 10);
    return (int)ch;
}
