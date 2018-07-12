/****************************************************************************
* Copyright (C), 201X-201X,杰普特光电股份有限公司
* 文件名: led.h
* 内容简述：
*
* 文件历史：
* 版本号 日期 作者 说明
* 01a 2018-07-10 XXX创建该文件
*/
#ifndef __APP_H
#define __APP_H

#include "includes.h"

/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
void vTaskTaskUserIF(void *pvParameters);
void vTaskLED(void *pvParameters);
void vTaskMsgPro(void *pvParameters);
void vTaskStart(void *pvParameters);
void AppTaskCreate (void);

#endif
