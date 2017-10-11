#include "spi.h"
/*
********************************************************************************
  * @author  xdh
  * @version V1.0
  * @date    2017-xx-xx
  * @apply   3000WControl
********************************************************************************
*/
SPI_HandleTypeDef SPI2_Handler;  //SPI句柄

//以下是SPI模块的初始化代码，配置成主机模式
//SPI口初始化
//这里针是对SPI5的初始化
void SPI2_Init(void)
{
	__HAL_SPI_DISABLE(&SPI2_Handler);

    SPI2_Handler.Instance=SPI2;                         //SPI2
    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //设置SPI工作模式，设置为主模式
    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //设置SPI单向或者双向的数据模式:SPI设置为双线模式
    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //串行同步时钟的空闲状态为高电平
    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//定义波特率预分频的值:波特率预分频值为256
    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //关闭TI模式
    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//关闭硬件CRC校验
    SPI2_Handler.Init.CRCPolynomial=7;                  //CRC值计算的多项式
    HAL_SPI_Init(&SPI2_Handler);//初始化

    __HAL_SPI_ENABLE(&SPI2_Handler);                    //使能SPI2

    SPI2_ReadWriteByte(0Xff);                           //启动传输
}

//SPI2底层驱动，时钟使能，引脚配置
//此函数会被HAL_SPI_Init()调用
//hspi:SPI句柄
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOB_CLK_ENABLE();//使能IO时钟
    __HAL_RCC_SPI2_CLK_ENABLE();//使能SPI时钟
    //通用推挽输出
    GPIO_InitStruct.Pin=GPIO_SD_CS_B
    GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;    //推挽输出
    GPIO_InitStruct.Pull=GPIO_PULLUP;            //上拉
    GPIO_InitStruct.Speed=GPIO_SPEED_HIGH;       //高速
    HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    //复用推挽输出
    GPIO_InitStruct.Pin=GPIO_SD_CLK_B|GPIO_SD_MISO_B|GPIO_SD_MOSI_B;
    GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
    GPIO_InitStruct.Pull=GPIO_PULLUP;                  //上拉
    GPIO_InitStruct.Speed=GPIO_SPEED_FAST;             //快速
    GPIO_InitStruct.Alternate=GPIO_AF5_SPI2;           //复用为SPI2
    HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//SPI速度设置函数
//SPI速度=fAPB1/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1时钟一般为45Mhz：
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&SPI2_Handler);            //关闭SPI
    SPI2_Handler.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
    __HAL_SPI_ENABLE(&SPI2_Handler);             //使能SPI

}

//SPI5 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 1000);
		return Rxdata;          		    //返回收到的数据
}
