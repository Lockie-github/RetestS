/**
 * @file driver_usart2.h
 * @author Lockie (k303278@126.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __DRIVER_USART2_H
#define __DRIVER_USART2_H

#include "stm32f1xx_hal.h"

/*********************
 * ���ź궨��
**********************/
#define RS485                  USART2
#define RS485_RX_PIN           GPIO_PIN_3
#define RS485_TX_PIN           GPIO_PIN_2
#define RS485_PORT             GPIOA
#define RS485_GPIO_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()

#define RE_DE_PIN               GPIO_PIN_5
#define RE_DE_PORT              GPIOC
#define RE_DE_GPIO_CLK_EN()     __HAL_RCC_GPIOC_CLK_ENABLE()


#define RE_DE_TX()              HAL_GPIO_WritePin(RE_DE_PORT, RE_DE_PIN, GPIO_PIN_SET)
#define RE_DE_RX()              HAL_GPIO_WritePin(RE_DE_PORT, RE_DE_PIN, GPIO_PIN_RESET)

#define RS485_IRQn             USART2_IRQn
#define RS485_IRQHandler       USART2_IRQHandler
#define RS485_CLK_ENABLE()     __HAL_RCC_USART2_CLK_ENABLE()
#define RS485_CLK_DISABLE()    __HAL_RCC_USART2_CLK_DISABLE()

enum Sensor
{
    Pre1 = 0,
    Pre2,
    Pre3,
    Pre4,
    Pre5,
    Pre6,
    Pre7,
    CPTU1,
    CPTU2,
    CPTU3
};

typedef struct
{

    uint8_t length;
    uint8_t tx_command[8];
    uint8_t rx_data[8];
}RS485_TxRxMsg;

extern UART_HandleTypeDef husart2;
extern volatile uint8_t usart2_tx_finish;
extern volatile uint8_t usart2_rx_finish;
extern RS485_TxRxMsg RS485_CPTU1;
extern RS485_TxRxMsg RS485_CPTU2;
extern RS485_TxRxMsg RS485_CPTU3;
extern RS485_TxRxMsg RS485_Pre1;
extern RS485_TxRxMsg RS485_Pre2;
extern RS485_TxRxMsg RS485_Pre3;
extern RS485_TxRxMsg RS485_Pre4;
extern RS485_TxRxMsg RS485_Pre5;
extern RS485_TxRxMsg RS485_Pre6; 
extern RS485_TxRxMsg RS485_Pre7; 

void datainit(void);
/*********************
 ********API**********
**********************/


extern void RS485_Init(uint32_t baudrate);


extern void RS485_Tx(uint8_t *pdata, uint16_t sz);


extern void RS485_Rx(uint8_t *pdata, uint16_t sz);
#endif
