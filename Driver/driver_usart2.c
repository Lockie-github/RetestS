/**
 * @file driver_usart2.c
 * @author Lockie (k303278@126.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "main.h"
#include "driver_usart2.h"

///< Instantiate 485
UART_HandleTypeDef husart2;
volatile uint8_t usart2_tx_finish = 0;
volatile uint8_t usart2_rx_finish = 0;
RS485_TxRxMsg RS485_CPTU1;
RS485_TxRxMsg RS485_CPTU2;
RS485_TxRxMsg RS485_CPTU3;
RS485_TxRxMsg RS485_Pre1;
RS485_TxRxMsg RS485_Pre2;
RS485_TxRxMsg RS485_Pre3;
RS485_TxRxMsg RS485_Pre4;
RS485_TxRxMsg RS485_Pre5;
RS485_TxRxMsg RS485_Pre6; 
RS485_TxRxMsg RS485_Pre7; 


void datainit()
{
    uint8_t CPTU_command[3][8]=
                              {
                                  0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A,
                                  0x02,0x03,0x00,0x00,0x00,0x01,0x84,0x39,
                                  0x03,0x03,0x00,0x00,0x00,0x01,0x84,0xE8                            
                              };
      
    //CPTU1
    RS485_CPTU1.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_CPTU1.tx_command[i] =CPTU_command[0][i] ;
    }
    //CPTU2
    RS485_CPTU2.length = 8;
     for(int i=0; i<8; i++)
    {
        RS485_CPTU2.tx_command[i] =CPTU_command[1][i] ;
    }
    //CPTU3
    RS485_CPTU3.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_CPTU3.tx_command[i] =CPTU_command[2][i] ;
    }

    uint8_t Pre_command[7][8]=
                             {
                                0x01, 0x03,0x00,0x07,0x00,0x02,0x75,0xCA,
                                0X02, 0x03,0x00,0x07,0x00,0x02,0X75,0XF9,
                                0X03, 0x03,0x00,0x07,0x00,0x02,0X74,0X28,
                                0X04, 0x03,0x00,0x07,0x00,0x02,0X74,0X28,/////////////////
                                0X05, 0x03,0x00,0x07,0x00,0x02,0X74,0X4E,
                                0X06, 0x03,0x00,0x07,0x00,0x02,0X74,0X7D,
                                0X07, 0x03,0x00,0x07,0x00,0x02,0X75,0XAC
                             };
    //pressure 1
    RS485_Pre1.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre1.tx_command[i] =Pre_command[0][i] ;
    }
    //pressure 2
    RS485_Pre2.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre2.tx_command[i] =Pre_command[1][i] ;
    }
    //pressure 3
    RS485_Pre3.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre3.tx_command[i] =Pre_command[2][i] ;
    }
    //pressure 4
    RS485_Pre4.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre4.tx_command[i] =Pre_command[3][i] ;
    }
    //pressure 5
    RS485_Pre5.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre5.tx_command[i] =Pre_command[4][i] ;
    }
    //pressure 6
    RS485_Pre6.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre6.tx_command[i] =Pre_command[5][i] ;
    }
    //pressure 7
    RS485_Pre7.length = 8;
    for(int i=0; i<8; i++)
    {
        RS485_Pre7.tx_command[i] =Pre_command[6][i] ;
    }
}
	



/**
 * @brief configure USART2
 * 
 * @param baudrate just baudrate
 */
void RS485_Init(uint32_t baudrate)
{
    husart2.Instance         = RS485;                   //Select USART2
    husart2.Init.BaudRate    = baudrate;                
    husart2.Init.WordLength  = USART_WORDLENGTH_8B;     
    husart2.Init.StopBits    = USART_STOPBITS_1;        
    husart2.Init.Parity      = USART_PARITY_NONE;       // None check
    husart2.Init.Mode        = USART_MODE_TX_RX;        
    husart2.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
    
    if (HAL_UART_Init(&husart2) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
 * @brief USART2 interrupt serve function
 * 
 */
void RS485_IRQHandler(void)
{
    HAL_UART_IRQHandler(&husart2);
}

/**
 * @brief RX485 Send function
 * 
 * @param pdata The pointer of data should be send
 * @param sz Amount of data
 */
void RS485_Tx(uint8_t *pdata, uint16_t sz)
{
    usart2_tx_finish = 0;
	
    //RE_DE_TX();
    HAL_UART_Transmit(&husart2, pdata, sz,8);
}

/**
 * @brief RX485 Recieve function
 * 
 * @param pdata The pointer of data will recieve
 * @param sz Amount of data
 */
void RS485_Rx(uint8_t *pdata, uint16_t sz)
{
	usart2_rx_finish = 0;
	
     HAL_UART_Receive(&husart2, pdata, sz,10);

}
