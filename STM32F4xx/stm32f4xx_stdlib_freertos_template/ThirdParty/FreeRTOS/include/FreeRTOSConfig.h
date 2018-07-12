/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* 确保stdint仅由编译器使用，而不是由汇编器使用. */
//#ifdef __ICCARM__
#if defined(__ICCARM__)||defined(__CC_ARM)||defined(__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION			1							//使用抢占式调度器
#define configUSE_IDLE_HOOK				0							//
#define configUSE_TICK_HOOK				0							//设置时间片钩子函数
#define configCPU_CLOCK_HZ				( SystemCoreClock )			//设置CPU频率
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )		//设置FreeRTOS的系统时钟频率，单位Hz
#define configMAX_PRIORITIES			( 5 )						//设置任务优先级数量 （ 0 最低 --  MAX-1 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 130 )	//设置空闲任务的最小任务堆栈大小(单位为字)
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 75 * 1024 ) )	//设置堆大小  动态内存分配时申请的内存大小
#define configMAX_TASK_NAME_LEN			( 10 )											//设置任务名的最大长度
#define configUSE_TRACE_FACILITY		1							//启动可视化跟踪调试
#define configUSE_16_BIT_TICKS			0						//设置系统节拍定时器变量数据类型（TickType_t） 1 --> 16bit  /  	0 --> 32bit                               	
#define configIDLE_SHOULD_YIELD			0		//定义了与空闲任务处于同等优先级的其他用户任务的行为。 1 --> 同优先级让出CPU权利。建议关闭

#define configUSE_MUTEXES				1		//使用互斥信号量，相关的API会编译
#define configQUEUE_REGISTRY_SIZE		8		//设置可以注册的队列和信号量的最大数量（使用内核调试器查看信号量和队列时需要此宏）             
#define configCHECK_FOR_STACK_OVERFLOW	0		//设置堆栈溢出检测
#define configUSE_RECURSIVE_MUTEXES		1		//使用递归互斥信号量
#define configUSE_MALLOC_FAILED_HOOK	0		//内存分配失败钩子函数，需要用户实现vApplicationMallocFailedHook()
#define configUSE_APPLICATION_TASK_TAG	0		//设置是否编译函数configUSE_APPLICATION_TASK_TAGF()。
#define configUSE_COUNTING_SEMAPHORES	1		//启动计数型信号量，相应的API会被编译
#define configGENERATE_RUN_TIME_STATS	0		//设置为1 开始时钟统计功能，相应的API会被编译

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0			//设置是否启用协程，建议关闭协程
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )	//设置可以分配给协程的最大优先级数，（0 -- X-1）


/* Software timer definitions.
	软件定时器定义
*/
#define configUSE_TIMERS				1			
#define configTIMER_TASK_PRIORITY		( 2 )			//设置软件定时器的任务优先级
#define configTIMER_QUEUE_LENGTH		10				//软件定时器的命令队列长度
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )	//软件定时器的任务堆栈大小

/* 
		INCLUDE_开头的宏 表示使能或者失能FreeRTOS相应的API函数。
*/
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 4位  0-15的优先级 */
#endif

/* 用来设置最低优先级 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* 设置FreeRTOS系统可管理的最大优先级 设置为5表示高于5的优先级（0-4）不归FreeRTOS管 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* 设置内核中断优先级    0xf << 4 = 0xF0  --> 15 */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* configMAX_SYSCALL_INTERRUPT_PRIORITY不能设置为零 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* 正常的assert（）语义，而不依赖于提供assert.h头文件。
	断言函数，检测传入的参数是否合理
*/
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* 
		重定义别名
*/
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

