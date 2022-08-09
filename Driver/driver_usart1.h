/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_usart.h
 * 摘要：
 *  
 * 修改历史     版本号       Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_USART1_H
#define __DRIVER_USART1_H

#include "stm32f1xx_hal.h"

/*********************
 * 引脚宏定义
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
 * 函数宏定义
**********************/

/*********************
 * 全局变量声明
**********************/
extern UART_HandleTypeDef husart1;

/*********************
 * 对外函数API
**********************/

/*
 *  函数名：void DEBUG_USART_Init(uint32_t baudrate)
 *  输入参数：baudrate-串口波特率
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化USART的波特率，收发选择，有效数据位等
*/
extern void DEBUG_USART_Init(uint32_t baudrate);
#endif
