/****************************************************************************
* Copyright (C), 201X-201X,杰普特光电股份有限公司
* 文件名: main.c
* 内容简述：
*
* 文件历史：
* 版本号 日期 作者 说明
* 01a 2018-07-10 XXX创建该文件
*/

#include "stm32f4xx.h"
#include "includes.h"


/******************************************************************************
* 函数名：ledGPIO_Init
* 功 能：LED GPIO初始化
* 输 入： 无
* 输 出：无
* 返 回：无
*/
int main(void)
{
	/* 程序来到main函数之前，启动文件：statup_stm32f429xx.s已经调用
	* SystemInit()函数把系统时钟初始化成180MHZ
    在启动调度前，为了防止初始化STM32外设时有中断服务程序执行，这里禁止全局中断(除了NMI和HardFault)。
	  这样做的好处是：
	  1. 防止执行的中断服务程序中有FreeRTOS的API函数。
	  2. 保证系统正常启动，不受别的中断影响。
	  3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
	  在移植文件port.c中的函数prvStartFirstTask中会重新开启全局中断。通过指令cpsie i开启，__set_PRIMASK(1)
	  和cpsie i是等效的。
	*/
  __set_PRIMASK(1);

  /* 硬件初始化 */
	bsp_Init();

  /* 创建任务 */
	AppTaskCreate();

  /* 启动调度，开始执行任务 */
  vTaskStartScheduler();

  /*
	  如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
	  heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
  while(1);
}
