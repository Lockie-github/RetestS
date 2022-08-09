/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_usart.h
 * ժҪ��
 *  
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/

#ifndef __DRIVER_USART1_H
#define __DRIVER_USART1_H

#include "stm32f1xx_hal.h"

/*********************
 * ���ź궨��
**********************/
#define DEBUG_USART                  USART1
#define DEBUG_USART_RX_PIN           GPIO_PIN_10
#define DEBUG_USART_TX_PIN           GPIO_PIN_9
#define DEBUG_USART_PORT             GPIOA
#define DEBUG_USART_GPIO_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define DEBUG_USART_CLK_EN()         __HAL_RCC_USART1_CLK_ENABLE()
#define DEBUG_USART_CLK_DIS()        __HAL_RCC_USART1_CLK_DISABLE()
#define DEBUG_USART_IRQn             USART1_IRQn

/*********************
 * �����궨��
**********************/

/*********************
 * ȫ�ֱ�������
**********************/
extern UART_HandleTypeDef husart1;

/*********************
 * ���⺯��API
**********************/

/*
 *  ��������void DEBUG_USART_Init(uint32_t baudrate)
 *  ���������baudrate-���ڲ�����
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��USART�Ĳ����ʣ��շ�ѡ����Ч����λ��
*/
extern void DEBUG_USART_Init(uint32_t baudrate);
#endif
