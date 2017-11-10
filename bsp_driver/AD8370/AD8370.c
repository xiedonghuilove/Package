#include "stm32f4xx.h"
#include "stdint.h"
#include "AD8370.h"

/*
 * Return:      void
 * Parameters:  void
 * Description: AD8370初始化
 */
void ad8370Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = AD8370_SDIO|AD8370_SCLK|AD8370_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    AD8370_CS_1();
    AD8370_SCLK_1();
    AD8370_SDIO_1();
}

/*
 * Return:      void
 * Parameters:  Gain: 要设置的增益值（0.0 --- 50.118899）
 * Description: 设置AD8370的增益
 */
void ad8370SetGain(float Gain)
{
    uint8_t data;
    
    if(Gain < 7.079488f)
    {
        data = Gain / 0.055744f;
        data &= 0x7F;
    }
    else
    {
        data = Gain / (0.055744f * 7.079458f);
        data |= 0x80;
    }
    
    ad8370WriteByte(data);
}

/*
 * Return:      void
 * Parameters:  Data: 要写入的字节
 * Description: 向AD8370写入一个字节
 */
void ad8370WriteByte(uint8_t Data)
{
    uint8_t mask;
    
    AD8370_CS_0();
    
    for(mask=0x80; mask; mask>>=1)
    {
        AD8370_SCLK_0();
        
        if(Data & mask)
            AD8370_SDIO_1();
        else
            AD8370_SDIO_0();

        AD8370_SCLK_1();
    }
    AD8370_SDIO_1();
    
    AD8370_CS_1();
}
