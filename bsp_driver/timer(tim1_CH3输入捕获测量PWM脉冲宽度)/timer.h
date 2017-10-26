#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"



extern u8  TIM1CH3_CAPTURE_STA;		    				
extern u32	TIM1CH3_CAPTURE_VAL;

void TIM1_CH3_Cap_Init(u32 arr,u16 psc);
	
#endif

