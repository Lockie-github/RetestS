/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_usart.c
 * 摘要：
 *  
 * 修改历史     版本号       Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/
#include <stdio.h>
#include "main.h"
#include "driver_usart1.h"
/*
 * 定义全局变量
*/
UART_HandleTypeDef husart1;

/*
 *  函数名：void DEBUG_USART_Init(uint32_t baudrate)
 *  输入参数：baudrate-串口波特率
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化USART的波特率，收发选择，有效数据位等
*/
void DEBUG_USART_Init(uint32_t baudrate)
{
    husart1.Instance         = DEBUG_USART;             // 选择USART1
    husart1.Init.BaudRate    = baudrate;                // 配置波特率
    husart1.Init.WordLength  = USART_WORDLENGTH_8B;     // 配置数据有效位为8bit
    husart1.Init.StopBits    = USART_STOPBITS_1;        // 配置一位停止位
    husart1.Init.Parity      = USART_PARITY_NONE;       // 不设校验位
    husart1.Init.Mode        = USART_MODE_TX_RX;        // 可收可发
    husart1.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
    
    // 使用库函数初始化USART3的参数
    if (HAL_UART_Init(&husart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/*****************************************************
*function:	写字符文件函数
*param1:	输出的字符
*param2:	文件指针
*return:	输出字符的ASCII码
******************************************************/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&husart1, (uint8_t*)&ch, 1, 10);
	return ch;
}

/*****************************************************
*function:	读字符文件函数
*param1:	文件指针
*return:	读取字符的ASCII码
******************************************************/
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&husart1, (uint8_t*)&ch, 1, 10);
    return (int)ch;
}
