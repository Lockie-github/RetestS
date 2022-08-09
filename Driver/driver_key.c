/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_key.c
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/

#include <stdbool.h>

#include "main.h"
#include "driver_key.h"
/*
 *  函数名：void KeyInit(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化按键的引脚，配置为下降沿触发外部中断
*/
void KeyInit(void)
{
    // 定义GPIO的结构体变量
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // 使能按键的GPIO对应的时钟
    KEY_UP_GPIO_CLK_EN();
    KEY_DOWN_GPIO_CLK_EN();
    KEY_LEFT_GPIO_CLK_EN();
    KEY_RIGHT_GPIO_CLK_EN();

    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;         // 设置为下降沿触发外部中断
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;               // 默认下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;       // 引脚反转速度设置为快
    
    // 初始化'Up'键引脚配置 
    GPIO_InitStruct.Pin = KEY_UP_GPIO_PIN;              // 选择按键的引脚
    HAL_GPIO_Init(KEY_UP_GPIO_PORT, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/*  说明：如下的四个外部中断函数均可放在stm32f1xx_it.c中，
 *  如果放在其中需要注意包含本文件的.h头文件，此处将中断函数放在本文件只是为了方便理清逻辑
*/
/*
 *  函数名：void EXTI0_IRQHandler(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 *  函数作用：外部中断0的中断处理函数
*/
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_GPIO_PIN);
}

/*
 *  函数名：void HAL_GPIO_EXTI_Callback(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 *  函数作用：外部中断处理函数的回调函数，用以处理不同引脚触发的中断服务最终函数
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY_UP_GPIO_PIN)
    {
        step = 0;
    } 
}
