#include "usart.h"
#include "delay.h"
#include "led.h"
#include "cmd.h"

UART_HandleTypeDef UART2_Handler;//UART2句柄
DMA_HandleTypeDef UART2TxDMA_Handler;//DMA句柄

UART_HandleTypeDef UART4_Handler;//UART3句柄
DMA_HandleTypeDef UART4TxDMA_Handler;//UART4_DMA句柄

uint8_t USART2_TX_BUF[USART_REC_LEN]={0xef,0xfe,0xff,0x01,0,0,0,0,0,0,0,0,0,0,0};
uint8_t USART4_TX_BUF[USART_REC_LEN]={0xef,0xfe,0xff,0x01,0,0,0,0,0,0,0,0,0,0,0};

uint8_t USART2_RX_BUF[USART_REC_LEN];
uint8_t USART4_RX_BUF[USART_REC_LEN];

uint8_t aRx2Buffer[RXBUFFERSIZE];
uint8_t aRx4Buffer[RXBUFFERSIZE];


uint16_t USART2_RX_STA = 0;     //接受状态标记
uint16_t USART4_RX_STA = 0;     //接受状态标记

uint16_t USART2_TX_STA = 0;


u8 SEND_OVER_FLAG = 0;

#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕
	USART2->DR = (u8) ch;
	return ch;
}
#endif

void usart_init(uint32_t bound)
{
		//使能时钟
		__HAL_RCC_DMA1_CLK_ENABLE();
		//UART2 初始化设置
		UART2_Handler.Instance = USART2;       				    // USART2
		UART2_Handler.Init.BaudRate = bound;   					//波特率
		UART2_Handler.Init.WordLength = UART_WORDLENGTH_8B; 	//字长为8位
		UART2_Handler.Init.StopBits = UART_STOPBITS_1;   		 //一个停止位
		UART2_Handler.Init.Parity = UART_PARITY_NONE;    		 //无奇偶校验
		UART2_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;	     //无硬件留控制
		UART2_Handler.Init.Mode = UART_MODE_TX_RX;  			//收发模式
		HAL_UART_Init(&UART2_Handler);    					  //初始化串口的时候会自动使能UART2。并且调用回调函数
		//并且  huart->State= HAL_UART_STATE_READY
		//连接DMA和外设句柄，
		__HAL_LINKDMA(&UART2_Handler, hdmatx, UART2TxDMA_Handler);//将DMA和USART2联系起来，
		//Tx_DMA配置
		UART2TxDMA_Handler.Instance = DMA1_Stream6;							//数据流
		UART2TxDMA_Handler.Init.Channel = DMA_CHANNEL_4;					//通道选择
		UART2TxDMA_Handler.Init.Direction = DMA_MEMORY_TO_PERIPH;			//内存到外设
		UART2TxDMA_Handler.Init.PeriphInc = DMA_PINC_DISABLE;				//外设地址不增
		UART2TxDMA_Handler.Init.MemInc = DMA_MINC_ENABLE;					//内存地址自增
		UART2TxDMA_Handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//外设数据宽度8BIT
		UART2TxDMA_Handler.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//内存数据宽度8BIT
		UART2TxDMA_Handler.Init.Mode = DMA_NORMAL;							//外设普通模式
		UART2TxDMA_Handler.Init.Priority = DMA_PRIORITY_MEDIUM;			   //中等优先级
		UART2TxDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;			//不使能FIFO模式
		UART2TxDMA_Handler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		UART2TxDMA_Handler.Init.MemBurst = DMA_MBURST_SINGLE;				//内存突发单次传输
		UART2TxDMA_Handler.Init.PeriphBurst = DMA_PBURST_SINGLE;			//外设突发单次传输

		HAL_DMA_DeInit(&UART2TxDMA_Handler);//先把DMA寄存器设置为缺省值（默认值）
		HAL_DMA_Init(&UART2TxDMA_Handler);//初始化DMA

		//该函数会开启接受中断，标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
		HAL_UART_Transmit_DMA(&UART2_Handler,(u8*)USART2_TX_BUF,USART_REC_LEN); //启动传输
		HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)aRx2Buffer, RXBUFFERSIZE);
		//每次接收RXBUFFERSIZE个字符后，表示接受结束。从而进入回调函数HAL_UART_RxCpltCallback进行相应的处理

		//UART4初始化设置
		UART4_Handler.Instance = UART4;       				    // USART4
		UART4_Handler.Init.BaudRate = 115200;   					//波特率
		UART4_Handler.Init.WordLength = UART_WORDLENGTH_8B; 	//字长为8位
		UART4_Handler.Init.StopBits = UART_STOPBITS_1;   		 //一个停止位
		UART4_Handler.Init.Parity = UART_PARITY_NONE;    		 //无奇偶校验
		UART4_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;	     //无硬件留控制
		UART4_Handler.Init.Mode = UART_MODE_TX_RX;  			//收发模式
		HAL_UART_Init(&UART4_Handler);    					  //初始化串口的时候会自动使能UART2。并且调用回调函数

    //连接DMA和串口外设
    __HAL_LINKDMA(&UART4_Handler,hdmatx,UART4TxDMA_Handler); //将DMA与UART4联系起来(发送DMA)
    //Tx DMA配置
    UART4TxDMA_Handler.Instance=DMA1_Stream4;                           //数据流选择
    UART4TxDMA_Handler.Init.Channel=DMA_CHANNEL_4;                      //通道选择
    UART4TxDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //存储器到外设
    UART4TxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //外设非增量模式
    UART4TxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //存储器增量模式
    UART4TxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //外设数据长度:8位
    UART4TxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //存储器数据长度:8位
    UART4TxDMA_Handler.Init.Mode=DMA_NORMAL;                            //外设普通模式
    UART4TxDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //中等优先级
    UART4TxDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;
    UART4TxDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;
    UART4TxDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //存储器突发单次传输
    UART4TxDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //外设突发单次传输

    HAL_DMA_DeInit(&UART4TxDMA_Handler);//配置为缺省值
    HAL_DMA_Init(&UART4TxDMA_Handler);//初始化

    RS485EN_RX();//开始设置485为接收模式
	__HAL_UART_ENABLE_IT(&UART4_Handler,USART_IT_RXNE);  //使能接收中断
	__HAL_UART_DISABLE_IT(&UART4_Handler,USART_IT_TC);   //禁止发送完成中断

		HAL_UART_Transmit_DMA(&UART4_Handler,(u8*)USART4_TX_BUF,USART_REC_LEN); //启动传输
		HAL_UART_Receive_IT(&UART4_Handler, (u8 *)aRx4Buffer, RXBUFFERSIZE);	//该函数会开启接受中断，标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

//开启一次DMA传输
//huart:串口句柄
//pData：传输的数据指针
//Size:传输的数据量
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (u32)pData, (uint32_t)&huart->Instance->DR, Size);//开启DMA传输
    huart->Instance->CR3 |= USART_CR3_DMAT;//使能串口DMA发送
}

//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//GPIO端口配置
	GPIO_InitTypeDef GPIO_InitStruct;

	if (huart->Instance == USART2)//如果是串口2，则进行串口2 MSP 配置
	{
		__HAL_RCC_USART2_CLK_ENABLE();  //使能USART2时钟
		__HAL_RCC_GPIOD_CLK_ENABLE(); //使能GPIOD

		//复用推挽输出
		GPIO_InitStruct.Pin=GPIO_PCTXD_D|GPIO_PCRXD_D;			//PD5 PD6
		GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;		  				//复用推挽输出
		GPIO_InitStruct.Pull=GPIO_PULLUP;			    				//上拉
		GPIO_InitStruct.Speed=GPIO_SPEED_FAST;		  			//高速
		GPIO_InitStruct.Alternate=GPIO_AF7_USART2;				//复用为USART2
		HAL_GPIO_Init(GPIOD,&GPIO_InitStruct);	   				//初始化PD5,PD6

		//串口2中断配置
		HAL_NVIC_EnableIRQ(USART2_IRQn);//使能USART2中断通道
		HAL_NVIC_SetPriority(USART2_IRQn, 2, 7);

	}
	if (huart->Instance == UART4)//如果是串口4
	{
		__HAL_RCC_UART4_CLK_ENABLE();//使能串口4时钟
		__HAL_RCC_GPIOA_CLK_ENABLE();//使能GPIOA时钟
		__HAL_RCC_GPIOC_CLK_ENABLE();//使能GPIOC时钟

    	//复用推挽输出
		GPIO_InitStruct.Pin=GPIO_485RX_C|GPIO_485TX_C;		//PA0 PA1
		GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;		  			//复用推挽输出
		GPIO_InitStruct.Pull=GPIO_PULLUP;			   			//上拉
		GPIO_InitStruct.Speed=GPIO_SPEED_FAST;		  			//高速
		GPIO_InitStruct.Alternate=GPIO_AF8_UART4;				//复用为USART4
		HAL_GPIO_Init(GPIOC,&GPIO_InitStruct)					//初始化
		//通用推挽输出
		GPIO_InitStruct.Pin=GPIO_485EN_A; 			//PA15
		GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;    //推挽输出
		GPIO_InitStruct.Pull=GPIO_PULLUP;            //上拉
		GPIO_InitStruct.Speed=GPIO_SPEED_HIGH;       //高速
		HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
		/*
			这里将串口2和串口4的优先级设为一致。
		*/
		//串口4中断配置
		HAL_NVIC_EnableIRQ(UART4_IRQn);//使能USART2中断通道
		HAL_NVIC_SetPriority(UART4_IRQn, 2, 7);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}

//串口中断函数
void USART2_IRQHandler(void)
{
	u8 Res;
	if(USART2->SR & (1<<6))//发送完成中断,置标志位
	{
		USART2->SR &= ~(1<<6);//清发送完成中断
	}
	if(USART2->SR & (1<<3))//上溢错误
	{
		USART2->SR &= ~(1<<3);
	}
	if(USART2->SR & (1<<5))
	{
		Res = USART2->DR;   //读取数据寄存器,清SR中断标志

		USART2->SR &= ~(1<<5);//清发送完成中断
		if((USART2_RX_STA & 0xfff) == 13)  //接收帧尾
		{
			++USART2_RX_STA;
			USART2_RX_BUF[USART2_RX_STA & 0xfff] = Res; //接收校验位
			////收到一帧，进行校验，并执行，然后回复

			//子控制收到正确的一帧数据和命令
			if(pc_to_control_crc())
			{
				if(run_pc_cmd())
				{
					replay_pc();
				}
			}
//			if(run_pc_cmd())
//			{
//				replay_pc();
//			}
			USART2_RX_STA = 0;
		}
		else if(USART2_RX_STA & 0x4000) //接收一帧数据的第3个----第9个数据
		{
			++USART2_RX_STA;
			USART2_RX_BUF[USART2_RX_STA & 0xfff] = Res;
		}
		else if(USART2_RX_STA & 0x8000) //接收一帧数据的第二个数据 ---0xfe
		{
			if(Res != 0xfe)
			USART2_RX_STA = 0;
			else
			{
				USART2_RX_BUF[(++USART2_RX_STA)&0xfff] = Res;
				USART2_RX_STA |= 0x4000;
			}
		}
		else if(Res == 0xef)  //接收一帧数据的第一个数据 ---0xef
		{
			USART2_RX_BUF[USART2_RX_STA & 0xfff] = Res;
			USART2_RX_STA |= 0x8000;
		}
	}
}

//串口4中断服务程序
void UART4_IRQHandler(void)
{
	u8 Res;
	if(UART4->SR & (1<<6))//发送完成中断,置标志位
	{
		UART4->SR &= ~(1<<6);//清发送完成中断
		SEND_OVER_FLAG=1;
	}
	if(UART4->SR & (1<<3))//上溢错误
	{
		UART4->SR &= ~(1<<3);
	}
	if(UART4->SR & (1<<5))
	{
		Res = UART4->DR;   //读取数据寄存器,清SR中断标志
		UART4->SR &= ~(1<<5);//清接受完成中断

		if((USART4_RX_STA & 0xfff) == 13)  //接收帧尾
		{
			++USART4_RX_STA;
			USART4_RX_BUF[USART4_RX_STA & 0xfff] = Res; //接收校验位
			//收到一帧，进行CRC校验，并执行，然后回复
			if(sub_to_master_crc())//收到子控板的一帧数据，CRC校验
			{
				run_sub_cmd();
			}

			USART4_RX_STA = 0;//这句话不能丢
		}
		else if(USART4_RX_STA & 0x4000) //接收一帧数据的第3个----第9个数据
		{
			++USART4_RX_STA;
			USART4_RX_BUF[USART4_RX_STA & 0xfff] = Res;
		}
		else if(USART4_RX_STA & 0x8000) //接收一帧数据的第二个数据 ---0xfe
		{
			if(Res != 0xfe)
			USART4_RX_STA = 0;
			else
			{
				USART4_RX_BUF[(++USART4_RX_STA)&0xfff] = Res;
				USART4_RX_STA |= 0x4000;
			}
		}
		else if(Res == 0xef)  //接收一帧数据的第一个数据 ---0xef
		{
			USART4_RX_BUF[USART4_RX_STA & 0xfff] = Res;
			USART4_RX_STA |= 0x8000;
//			COM_485_CNT=0;                  //485通信3s报警检测
		}
	}
}
