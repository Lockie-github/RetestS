#include "driver_usart1.h"
#include "driver_usart2.h"
#include "driver_msp_usart.h"
/**
 * @brief Configure USART1 & 2 configuration 
 * 
 * @param husart handle of USART1 & 2
 */
void HAL_UART_MspInit(UART_HandleTypeDef* husart)
{
    ///< Instantiate GPIO 
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(husart->Instance==DEBUG_USART)
    {
     
        DEBUG_USART_CLK_EN();
        
        DEBUG_USART_GPIO_CLK_EN();
        /*  USART1 GPIO Configuration   
            PA9------> USART1_TX
            PA10------> USART1_RX
        */
        GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;           
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;             
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;       
        HAL_GPIO_Init(DEBUG_USART_PORT, &GPIO_InitStruct);  

        GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;           
        GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;          
        HAL_GPIO_Init(DEBUG_USART_PORT, &GPIO_InitStruct);  
    }
    else if(husart->Instance==RS485)
    {
       
        RS485_CLK_ENABLE();
        
        // Eable USART2 I/O clk
        RS485_GPIO_CLK_EN();
  
        /*  USART2 GPIO Configuration   
            PA2------> USART2_TX
            PA3------> USART2_RX
        */
        GPIO_InitStruct.Pin = RS485_TX_PIN;            
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  
        HAL_GPIO_Init(RS485_PORT, &GPIO_InitStruct);   

        GPIO_InitStruct.Pin = RS485_RX_PIN;            
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;        
        GPIO_InitStruct.Pull = GPIO_NOPULL;            
        HAL_GPIO_Init(RS485_PORT, &GPIO_InitStruct);                                  
        
        HAL_NVIC_SetPriority(RS485_IRQn, 0, 0);        // configure USART2 interrupt grade（0-15）（0-15）
                                                       // regulation：(0,0)Highest,(0,1)...(15,15)Lowest
        HAL_NVIC_EnableIRQ(RS485_IRQn);                // USART2
    }
}

/**
 * @brief 
 * 
 * @param husart 
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* husart)
{
    if(husart->Instance==DEBUG_USART)
    {
        DEBUG_USART_CLK_DIS();
        /**USART1 GPIO Configuration   
        PA9      ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(DEBUG_USART_PORT, DEBUG_USART_TX_PIN | DEBUG_USART_RX_PIN);
        
        HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);
    }
    else if(husart->Instance==RS485)
    {
        RS485_CLK_DISABLE();
        /**USART2 GPIO Configuration   
        PA2      ------> USART2_TX
        PA3      ------> USART2_RX
        */
        HAL_GPIO_DeInit(RS485_PORT, RS485_TX_PIN | RS485_RX_PIN);
        
        HAL_NVIC_DisableIRQ(RS485_IRQn);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == RS485)
    {
        usart2_tx_finish = 1;
		RE_DE_RX();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == RS485)
    {
        usart2_rx_finish = 1;
    }
}
