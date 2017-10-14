#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"
/*
********************************************************************************
  * @author  xdh
  * @version V1.0
  * @date    2017-xx-xx
  * @apply   3000WControl
********************************************************************************
*/
/*
    PC通信  232  MCU
        USART2_RX  ---> PD6
        USART2_TX  ---> PD5
    主控板   485   子控制板通信
        UART4_RX   --> PC11
        UART4_TX   --> PC10
        EN         --> PA15
*/
#define USART_REC_LEN         15 //定义最大的接受字节数200

extern UART_HandleTypeDef UART2_Handler;  //UART句柄
extern DMA_HandleTypeDef UART2TxDMA_Handler;//DMA句柄

extern UART_HandleTypeDef UART4_Handler;  //UART句柄
extern DMA_HandleTypeDef UART4TxDMA_Handler;//DMA句柄

#define RXBUFFERSIZE 1      //缓存大小

extern uint8_t aRx2Buffer[RXBUFFERSIZE];//HAL库USART2接受Buff
extern uint8_t aRx4Buffer[RXBUFFERSIZE];//HAL库USART4接受Buff

extern uint8_t  USART2_TX_BUF[USART_REC_LEN];//定义发送缓冲区，
extern uint8_t  USART4_TX_BUF[USART_REC_LEN];//定义发送缓冲区，

extern uint8_t  USART2_RX_BUF[USART_REC_LEN];//定义接受缓冲区，
extern uint8_t  USART4_RX_BUF[USART_REC_LEN];//定义接受缓冲区，


extern uint16_t USART2_RX_STA;            //接受状态标志
extern uint16_t USART4_RX_STA;            //接受状态标志

extern uint16_t USART2_TX_STA;		//发送状态标志

extern u8 SEND_OVER_FLAG;

#define GPIO_PCTXD_D					GPIO_PIN_6		//复用推挽输出
#define GPIO_PCRXD_D					GPIO_PIN_5		//复用推挽输出


#define GPIO_485TX_C					GPIO_PIN_11		//复用推挽输出
#define GPIO_485RX_C					GPIO_PIN_10		//复用推挽输出
#define GPIO_485EN_A         	        GPIO_PIN_15      //通用推挽输出

#define RS485EN_RX()       PAout(15)=0
#define RS485EN_TX()       PAout(15)=1


void usart_init(uint32_t bound);
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);


#endif
