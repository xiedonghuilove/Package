#ifndef _AD8370_H_
#define _AD8370_H_


#define AD8370_SDIO             GPIO_Pin_0
#define AD8370_SCLK             GPIO_Pin_1
#define AD8370_CS               GPIO_Pin_5


#define AD8370_CS_0()           GPIOB->BSRRH = AD8370_CS
#define AD8370_CS_1()           GPIOB->BSRRL = AD8370_CS
 
#define AD8370_SCLK_0()         GPIOB->BSRRH = AD8370_SCLK
#define AD8370_SCLK_1()         GPIOB->BSRRL = AD8370_SCLK
 
#define AD8370_SDIO_0()         GPIOB->BSRRH = AD8370_SDIO
#define AD8370_SDIO_1()         GPIOB->BSRRL = AD8370_SDIO


#define AD8370_SDIO_VALUE()     GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)


void ad8370Init(void);
void ad8370SetGain(float Gain);
void ad8370WriteByte(uint8_t Data);

#endif
