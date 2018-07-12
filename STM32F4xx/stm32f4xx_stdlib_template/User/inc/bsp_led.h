/****************************************************************************
* Copyright (C), 201X-201X,杰普特光电股份有限公司
* 文件名: led.h
* 内容简述：
*
* 文件历史：
* 版本号 日期 作者 说明
* 01a 2018-07-10 XXX创建该文件
*/
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"
/*
    RUNLED   DS1 -->PF1
    ERRLED   DS2-->PF0
    STATE1   DS3--> PI11
    STATE2   DS4-->PI10
*/
//引脚定义
/*******************************************************/
//LED1
#define LED1_PIN                  GPIO_Pin_1
#define LED1_GPIO_PORT            GPIOF
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOF

//LED2
#define LED2_PIN                  GPIO_Pin_0
#define LED2_GPIO_PORT            GPIOF
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOF

//LED3
#define LED3_PIN                  GPIO_Pin_11
#define LED3_GPIO_PORT            GPIOI
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOI

//LED4
#define LED4_PIN                  GPIO_Pin_10
#define LED4_GPIO_PORT            GPIOI
#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOI

/************************************************************/
/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  1
#define OFF 0

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)

#define LED4(a)	if (a)	\
					GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);\
					else		\
					GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN)

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF			digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON				digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF			digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON				digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF			digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON				digitalLo(LED3_GPIO_PORT,LED3_PIN)

#define LED4_TOGGLE		digitalToggle(LED4_GPIO_PORT,LED4_PIN)
#define LED4_OFF			digitalHi(LED4_GPIO_PORT,LED4_PIN)
#define LED4_ON				digitalLo(LED4_GPIO_PORT,LED4_PIN)

void ledGPIO_Init(void);




#endif
