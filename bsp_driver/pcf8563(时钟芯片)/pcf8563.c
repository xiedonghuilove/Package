#include "pcf8563.h"
/*
********************************************************************************
  * @author  xdh
  * @version V1.0
  * @date    2017-xx-xx
  * @apply   3000WControl
********************************************************************************
*/
/******************************************************************************
                            定义相关的变量函数
******************************************************************************/
unsigned char buffer[4];

/*******************************************************************************
  * @Name   : 将BIN转换为BCD
  * @Brief  : none
  * @Input  : BINValue: 输入BIN
  * @Output : none
  * @Return : BCD格式数值
*******************************************************************************/
static unsigned char RTC_BinToBcd2(unsigned char BINValue)
{
		unsigned char bcdhigh = 0;
		while (BINValue >= 10)
		{
			bcdhigh++;
			BINValue -= 10;
		}
		return ((unsigned char)(bcdhigh << 4) | BINValue);
}
/*******************************************************************************
  * @Name   : 将BCD转换为BIN
  * @Brief  : none
  * @Input  : BCDValue: 输入BCD
  * @Output : none
  * @Return : BIN格式数值
*******************************************************************************/
static unsigned char RTC_Bcd2ToBin(unsigned char BCDValue)
{
		unsigned char tmp = 0;
		tmp = ((unsigned char)(BCDValue & (unsigned char)0xF0) >> (unsigned char)0x04) * 10;
		return (tmp + (BCDValue & (unsigned char)0x0F));
}
/*******************************************************************************
  * @Name   : PCF8563某寄存器写入一个字节数据
  * @Brief  : none
  * @Input  : REG_ADD：要操作寄存器地址
  *           dat：    要写入的数据
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_Write_Byte(unsigned char REG_ADD, unsigned char dat)
{
		IIC_Start();
		if(!(IIC_Write_Byte(PCF8563_Write)))  //发送写命令并检查应答位
		{
			IIC_Write_Byte(REG_ADD);
			IIC_Write_Byte(dat);  							//发送数据
		}
		IIC_Stop();
}
/*******************************************************************************
  * @Name   : PCF8563某寄存器读取一个字节数据
  * @Brief  : none
  * @Input  : REG_ADD：要操作寄存器地址
  * @Output : none
  * @Return : 读取得到的寄存器的值
*******************************************************************************/
unsigned char PCF8563_Read_Byte(unsigned char REG_ADD)
{
		unsigned char ReData;
		IIC_Start();
		if(!(IIC_Write_Byte(PCF8563_Write)))  //发送写命令并检查应答位
		{
			IIC_Write_Byte(REG_ADD);  					//确定要操作的寄存器
			IIC_Start();  											//重启总线
			IIC_Write_Byte(PCF8563_Read);  			//发送读取命令
			ReData = IIC_Read_Byte();  					//读取数据
			IIC_Ack(1); 												//发送非应答信号结束数据传送
		}
		IIC_Stop();
		return ReData;
}
/*******************************************************************************
  * @Name   : PCF8563写入多组数据
  * @Brief  : none
  * @Input  : REG_ADD：要操作寄存器起始地址
  *           num：    写入数据数量
  *           *WBuff： 写入数据缓存
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_Write_nByte(unsigned char REG_ADD, unsigned char num, unsigned char *pBuff)
{
		unsigned char i = 0;
		IIC_Start();
		if(!(IIC_Write_Byte(PCF8563_Write)))  //发送写命令并检查应答位
		{
			IIC_Write_Byte(REG_ADD);  					//定位起始寄存器地址
			for(i = 0;i < num;i++)
			{
				IIC_Write_Byte(*pBuff);  					//写入数据
				pBuff++;
			}
		}
		IIC_Stop();
}
/*******************************************************************************
  * @Name   : PCF8563读取多组数据
  * @Brief  : none
  * @Input  : REG_ADD：要操作寄存器起始地址
  *           num：    读取数据数量
  * @Output : *WBuff： 读取数据缓存
  * @Return : none
*******************************************************************************/
void PCF8563_Read_nByte(unsigned char REG_ADD, unsigned char num, unsigned char *pBuff)
{
		unsigned char i = 0;
		IIC_Start();
		if(!(IIC_Write_Byte(PCF8563_Write)))  //发送写命令并检查应答位
		{
			IIC_Write_Byte(REG_ADD);  					//定位起始寄存器地址
			IIC_Start();  											//重启总线
			IIC_Write_Byte(PCF8563_Read);  			//发送读取命令
			for(i = 0;i < num;i++)
			{
				*pBuff = IIC_Read_Byte(); 			 //读取数据
				if(i == (num - 1))	IIC_Ack(1);  //发送非应答信号
				else IIC_Ack(0); 								 //发送应答信号
				pBuff++;
			}
		}
		IIC_Stop();
}
/*******************************************************************************
  * @Name   : PCF8563检测是否存在
  * @Brief  : 向定时器倒计时寄存器写入一个数值再读取出来做对比，相同正确，不同则错误
  * @Input  : none
  * @Output : none
  * @Return : 0: 正常
  *           1: PCF8563错误或者损坏
*******************************************************************************/
unsigned char PCF8563_Check(void)
{
		unsigned char test_value = 0;
		unsigned char Time_Count = 0;  																			//定时器倒计时数据缓存
		if(PCF8563_Read_Byte(PCF8563_Address_Timer) & 0x80)  								//如果打开了定时器，则先关闭
		{
			PCF8563_Write_Byte(PCF8563_Address_Timer, PCF_Timer_Close); 		  //先关闭定时器
			Time_Count = PCF8563_Read_Byte(PCF8563_Address_Timer_VAL);  			//先保存计数值
		}
		PCF8563_Write_Byte(PCF8563_Address_Timer_VAL, PCF8563_Check_Data);  //写入检测值
		for(test_value = 0;test_value < 50;test_value++)  {}  							//延时一定时间再读取
		test_value = PCF8563_Read_Byte(PCF8563_Address_Timer_VAL);  				//再读取回来
		if(Time_Count != 0)  																								//启动了定时器功能，则恢复
		{
			PCF8563_Write_Byte(PCF8563_Address_Timer_VAL, Time_Count);  			//恢复现场
			PCF8563_Write_Byte(PCF8563_Address_Timer, PCF_Timer_Open);  			//启动定时器
		}
		if(test_value != PCF8563_Check_Data)  return 1; 										//器件错误或者损坏
		return 0;  																													//正常
}
/*******************************************************************************
  * @Name   : PCF8563启动
  * @Brief  : none
  * @Input  : none
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_Start(void)
{
		unsigned char temp = 0;
		temp = PCF8563_Read_Byte(PCF8563_Address_Control_Status_1);  //读取控制/状态寄存器1
		if (temp & PCF_Control_ChipStop)
		{
			temp &= PCF_Control_ChipRuns;  													 	 //运行芯片
		}
		if ((temp & (1<<7)) == 0)  																	 //普通模式
		{
			temp &= PCF_Control_TestcClose; 													 //电源复位模式失效
		}
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_1, temp);  //再写入数值
}
/*******************************************************************************
  * @Name   : PCF8563停止
  * @Brief  : 时钟频率输出CLKOUT 在 32.768kHz 时可用
  * @Input  : none
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_Stop(void)
{
		unsigned char temp = 0;
		temp = PCF8563_Read_Byte(PCF8563_Address_Control_Status_1);  	//读取控制/状态寄存器1
		temp |= PCF_Control_ChipStop;  																//停止运行
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_1, temp);  	//再写入数值
}
/*******************************************************************************
  * @Name   : PCF8563设置运行模式
  * @Brief  : none
  * @Input  : Mode: 运行模式
  *                 = PCF_Mode_Normal
  *                 = PCF_Mode_EXT_CLK
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetMode(unsigned char Mode)
{
		unsigned char temp = 0;
		temp = PCF8563_Read_Byte(PCF8563_Address_Control_Status_1);   //读取寄存器值
		if (Mode == PCF_Mode_EXT_CLK)  																//EXT_CLK测试模式
		{
			temp |= PCF_Control_Status_EXT_CLKMode;
		}
		else if (Mode == PCF_Mode_Normal)
		{
			temp &= PCF_Control_Status_NormalMode;
			temp &= ~(1<<3);  																					//电源复位功能失效
		}
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_1, temp);
}
/*******************************************************************************
  * @Name   : PCF8563设置电源复位功能开启与关闭
  * @Brief  : none
  * @Input  : NewState: 状态，PCF8563_PowerResetEnablePCF8563_PowerResetDisable
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetPowerReset(unsigned char NewState)
{
		unsigned char TestC = 0;
		TestC = PCF8563_Read_Byte(PCF8563_Address_Control_Status_1);  	//获取寄存器值
		TestC &= ~(1<<3); 																						 	//清除之前设置
		if (NewState == PCF8563_PowerResetEnable)  											//复位功能有效
		{
			TestC |= PCF8563_PowerResetEnable;
		}
		else if (NewState == PCF8563_PowerResetDisable)
		{
			TestC &= ~PCF8563_PowerResetEnable;  													//失效，普通模式是值逻辑0，即失效
		}
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_1, TestC);  	//写入数值
}
/*******************************************************************************
  * @Name   : PCF8563设置输出频率
  * @Brief  : none
  * @Input  :*PCF_CLKOUTStruct: 频率结构指针
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetCLKOUT(_PCF8563_CLKOUT_Typedef* PCF_CLKOUTStruct)
{
		unsigned char tmp = 0;
		tmp = PCF8563_Read_Byte(PCF8563_Address_CLKOUT);  //读取寄存器值
		tmp &= 0x7c;  //清除之前设置
		if (PCF_CLKOUTStruct->CLKOUT_NewState == PCF_CLKOUT_Open)
		{
			tmp |= PCF_CLKOUT_Open;
		}
		else
		{
			tmp &= PCF_CLKOUT_Close;
		}
		tmp |= PCF_CLKOUTStruct->CLKOUT_Frequency;

		PCF8563_Write_Byte(PCF8563_Address_CLKOUT, tmp);
}
/*******************************************************************************
  * @Name   : PCF8563设置定时器
  * @Brief  : none
  * @Input  :*PCF_TimerStruct: 定时器结构指针
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetTimer(_PCF8563_Timer_Typedef* PCF_TimerStruct)
{
		unsigned char Timer_Ctrl = 0;
		unsigned char Timer_Value = 0;
		Timer_Ctrl = PCF8563_Read_Byte(PCF8563_Address_Timer);  							//获的控制寄存器值
		Timer_Value = PCF8563_Read_Byte(PCF8563_Address_Timer_VAL);  					//获取倒计时数值

		///////先停止定时器
		Timer_Ctrl &= PCF_Timer_Close;
		PCF8563_Write_Byte(PCF8563_Address_Timer, Timer_Ctrl);

		Timer_Ctrl &= 0x7c;  																									//清除定时器之前设置
		if (PCF_TimerStruct->RTC_Timer_NewState == PCF_Timer_Open)  					//开启
		{
			Timer_Ctrl |= PCF_Timer_Open;
			Timer_Ctrl |= PCF_TimerStruct->RTC_Timer_Frequency; 							  //填上新的工作频率
			if (PCF_TimerStruct->RTC_Timer_Value)  															//需要填上新的计数值
			{
				Timer_Value = PCF_TimerStruct->RTC_Timer_Value; 									//填上新的计数值
			}
		}
		else
		{
			Timer_Ctrl &= PCF_Timer_Close;
		}
		PCF8563_Write_Byte(PCF8563_Address_Timer_VAL, Timer_Value);  					//写入倒计时数值

		if (PCF_TimerStruct->RTC_Timer_Interrupt == PCF_Time_INT_Open)  			//开启了中断输出
		{
			Timer_Value = PCF8563_Read_Byte(PCF8563_Address_Control_Status_2);  //获取控制/状态寄存器2数值
			Timer_Value &= PCF_Time_INT_Close;  																//清除定时器中断使能
			Timer_Value &= ~(1<<2); 																					  //清除定时器中断标志
			Timer_Value &= ~(1<<4);  																						//当 TF 有效时 INT 有效 (取决于 TIE 的状态)
			Timer_Value |= PCF_Time_INT_Open;  																	//开启定时器中断输出
			PCF8563_Write_Byte(PCF8563_Address_Control_Status_2, Timer_Value);
		}
		else
		{
			Timer_Value = PCF8563_Read_Byte(PCF8563_Address_Control_Status_2);  //获取控制/状态寄存器2数值
			Timer_Value &= PCF_Time_INT_Close;  																//清除定时器中断使能
			Timer_Value |= PCF_Time_INT_Open;  																	//开启定时器中断输出
			PCF8563_Write_Byte(PCF8563_Address_Control_Status_2, Timer_Value);
		}

		PCF8563_Write_Byte(PCF8563_Address_Timer, Timer_Ctrl);  							//设置定时器控制寄存器
}
/*******************************************************************************
  * @Name   : 设置时间，主要用于后台调用，或者初始化时间用
  * @Brief  : 秒默认就设置成0x00了，形参里面不体现，星期值范围：0 ~ 6
  * @Input  : PCF_Format:  数据格式
  *                        = PCF_Format_BIN
  *                        = PCF_Format_BCD
  *           PCF_Century: 世纪位设定
  *                        = PCF_Century_19xx
  *                        = PCF_Century_20xx
  *           Year:        年
  *           Month:       月
  *           Date:        日
  *           Week:        星期
  *           Hour:        时
  *           Minute:      分
  *
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_Set_Times(unsigned char PCF_Format,\
                       unsigned char PCF_Century,\
											 unsigned char Year, unsigned char Month, unsigned char Date, unsigned char Week,\
                       unsigned char Hour, unsigned char Minute)
{
		_PCF8563_Time_Typedef Time_InitStructure;
		_PCF8563_Date_Typedef Date_InitStructure;
		if (PCF_Format == PCF_Format_BIN)
		{
			//////判断数据是否符合范围
			if (Year > 99)   Year  = 0;  //恢复00年
			if (Month > 12)  Month = 1;  //恢复1月
			if (Date > 31)   Date  = 1;  //恢复1日
			if (Week > 6)    Week  = 1;  //恢复星期一
			if (Hour > 23)    Hour   = 0;  //恢复0小时
			if (Minute > 59)  Minute = 0;  //恢复0分钟

			//////转换一下
			Date_InitStructure.RTC_Years    = RTC_BinToBcd2(Year);
			Date_InitStructure.RTC_Months   = RTC_BinToBcd2(Month);
			Date_InitStructure.RTC_Days     = RTC_BinToBcd2(Date);
			Date_InitStructure.RTC_WeekDays = RTC_BinToBcd2(Week);

			Time_InitStructure.RTC_Hours    = RTC_BinToBcd2(Hour);
			Time_InitStructure.RTC_Minutes  = RTC_BinToBcd2(Minute);
		}
		Time_InitStructure.RTC_Seconds = 0x00;  //恢复0秒
		Time_InitStructure.RTC_Seconds &= PCF_Accuracy_ClockYes;  //保证准确的时间

		///////判断世纪位
		if (PCF_Century == PCF_Century_19xx)
		{
			Date_InitStructure.RTC_Months |= PCF_Century_SetBitC;
		}
		else
		{
			Date_InitStructure.RTC_Months &= ~PCF_Century_SetBitC;
		}

		///////写入信息到寄存器
		buffer[0] = Time_InitStructure.RTC_Seconds;
		buffer[1] = Time_InitStructure.RTC_Minutes;
		buffer[2] = Time_InitStructure.RTC_Hours;
		PCF8563_Write_nByte(PCF8563_Address_Seconds, 3, buffer);  //写入时间信息

		buffer[0] = Date_InitStructure.RTC_Days;
		buffer[1] = Date_InitStructure.RTC_WeekDays;
		buffer[2] = Date_InitStructure.RTC_Months;
		buffer[3] = Date_InitStructure.RTC_Years;
		PCF8563_Write_nByte(PCF8563_Address_Days,    4, buffer);  //写入日期信息
}

/**************************************************************************
									所有寄存器全部操作功能函数
**************************************************************************/
/*******************************************************************************
  * @Name   : 判断时间信息是否符合范围，超出将恢复初值
  * @Brief  : 星期值范围：0 ~ 6
  * @Input  : PCF_DataStruct: 寄存器结构指针
  * @Output : none
  * @Return : none
*******************************************************************************/
static void IS_PCF8563_Data(_PCF8563_Register_Typedef* PCF_DataStruct)
{
		if (PCF_DataStruct->Years > 99)           PCF_DataStruct->Years          = 0;  //恢复00年
		if (PCF_DataStruct->Months_Century > 12)  PCF_DataStruct->Months_Century = 1;  //恢复1月
		if (PCF_DataStruct->Days > 31)            PCF_DataStruct->Days           = 1;  //恢复1日
		if (PCF_DataStruct->WeekDays > 6)         PCF_DataStruct->WeekDays       = 1;  //恢复星期一
		if (PCF_DataStruct->Hours > 23)           PCF_DataStruct->Hours          = 0;  //恢复0小时
		if (PCF_DataStruct->Minutes > 59)         PCF_DataStruct->Minutes        = 0;  //恢复0分钟
		if (PCF_DataStruct->Seconds > 59)         PCF_DataStruct->Seconds        = 0;  //恢复0秒
}
/*******************************************************************************
  * @Name   : PCF8563写入寄存器
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  *           PCF_Century:    世纪位设定
  *                           = PCF_Century_19xx
  *                           = PCF_Century_20xx
  *           PCF_DataStruct: 寄存器结构指针
  *
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetRegister(unsigned char PCF_Format, unsigned char PCF_Century, _PCF8563_Register_Typedef* PCF_DataStruct)
{
		if (PCF_Format == PCF_Format_BIN)  //十进制格式，需要转换一下
		{
			//////////判断数值是否在范围之内
			IS_PCF8563_Data(PCF_DataStruct);

			///////////需要转换一下
			PCF_DataStruct->Years          = RTC_BinToBcd2(PCF_DataStruct->Years);
			PCF_DataStruct->Months_Century = RTC_BinToBcd2(PCF_DataStruct->Months_Century);
			PCF_DataStruct->Days           = RTC_BinToBcd2(PCF_DataStruct->Days);
			PCF_DataStruct->WeekDays       = RTC_BinToBcd2(PCF_DataStruct->WeekDays);

			PCF_DataStruct->Hours          = RTC_BinToBcd2(PCF_DataStruct->Hours);
			PCF_DataStruct->Minutes        = RTC_BinToBcd2(PCF_DataStruct->Minutes);
			PCF_DataStruct->Seconds        = RTC_BinToBcd2(PCF_DataStruct->Seconds);

			PCF_DataStruct->Day_Alarm      = RTC_BinToBcd2(PCF_DataStruct->Day_Alarm);
			PCF_DataStruct->WeekDays_Alarm = RTC_BinToBcd2(PCF_DataStruct->WeekDays_Alarm);

			PCF_DataStruct->Hour_Alarm     = RTC_BinToBcd2(PCF_DataStruct->Hour_Alarm);
			PCF_DataStruct->Minute_Alarm   = RTC_BinToBcd2(PCF_DataStruct->Minute_Alarm);
		}

		/////////判断世纪位
		if (PCF_Century == PCF_Century_19xx)
		{
			PCF_DataStruct->Months_Century |= PCF_Century_SetBitC;
		}
		else
		{
			PCF_DataStruct->Months_Century &= ~PCF_Century_SetBitC;
		}

		//////////关闭所有闹铃，中断输出
		PCF_DataStruct->Timer_Control    &= ~(1<<7);
		PCF_DataStruct->CLKOUT_Frequency &= ~(1<<7);
		PCF_DataStruct->WeekDays_Alarm   &= ~(1<<7);
		PCF_DataStruct->Day_Alarm        &= ~(1<<7);
		PCF_DataStruct->Hour_Alarm       &= ~(1<<7);
		PCF_DataStruct->Minute_Alarm     &= ~(1<<7);
		PCF_DataStruct->Control_Status_2 &= ~(3<<0);

		//////////写入数据到寄存器
		PCF8563_Write_nByte(PCF8563_Address_Control_Status_1, 16, (unsigned char*)PCF_DataStruct);
}
/*******************************************************************************
  * @Name   : PCF8563读取寄存器
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  * @Output : *PCF_Century:   世纪位，0：21世纪；1:20世纪
  *           PCF_DataStruct: 寄存器结构指针
  * @Return : none
*******************************************************************************/
void PCF8563_GetRegister(unsigned char PCF_Format, unsigned char *PCF_Century, _PCF8563_Register_Typedef* PCF_DataStruct)
{
		//////////读取全部寄存器数值
		PCF8563_Read_nByte(PCF8563_Address_Control_Status_1, 16, (unsigned char*)PCF_DataStruct);

		///////////判断世纪位数值
		if (PCF_DataStruct->Months_Century & PCF_Century_SetBitC)
		{
			*PCF_Century = 1;
		}
		else
		{
			*PCF_Century = 0;
		}

		//////////屏蔽无效位
		PCF_DataStruct->Years          &= PCF8563_Shield_Years;
		PCF_DataStruct->Months_Century &= PCF8563_Shield_Months_Century;
		PCF_DataStruct->Days           &= PCF8563_Shield_Days;
		PCF_DataStruct->WeekDays       &= PCF8563_Shield_WeekDays;
		PCF_DataStruct->Hours          &= PCF8563_Shield_Hours;
		PCF_DataStruct->Minutes        &= PCF8563_Shield_Minutes;
		PCF_DataStruct->Seconds        &= PCF8563_Shield_Seconds;
		PCF_DataStruct->Minute_Alarm   &= PCF8563_Shield_Minute_Alarm;
		PCF_DataStruct->Hour_Alarm     &= PCF8563_Shield_Hour_Alarm;
		PCF_DataStruct->Day_Alarm      &= PCF8563_Shield_Day_Alarm;
		PCF_DataStruct->WeekDays_Alarm &= PCF8563_Shield_WeekDays_Alarm;

		//////////判断需要的数据格式
		if (PCF_Format == PCF_Format_BIN)
		{
			PCF_DataStruct->Years           = RTC_Bcd2ToBin(PCF_DataStruct->Years);
			PCF_DataStruct->Months_Century  = RTC_Bcd2ToBin(PCF_DataStruct->Months_Century);
			PCF_DataStruct->Days            = RTC_Bcd2ToBin(PCF_DataStruct->Days);
			PCF_DataStruct->WeekDays        = RTC_Bcd2ToBin(PCF_DataStruct->WeekDays);
			PCF_DataStruct->Hours           = RTC_Bcd2ToBin(PCF_DataStruct->Hours);
			PCF_DataStruct->Minutes         = RTC_Bcd2ToBin(PCF_DataStruct->Minutes);
			PCF_DataStruct->Seconds         = RTC_Bcd2ToBin(PCF_DataStruct->Seconds);
			PCF_DataStruct->Day_Alarm       = RTC_Bcd2ToBin(PCF_DataStruct->Day_Alarm);
			PCF_DataStruct->WeekDays_Alarm  = RTC_Bcd2ToBin(PCF_DataStruct->WeekDays_Alarm);
			PCF_DataStruct->Hour_Alarm      = RTC_Bcd2ToBin(PCF_DataStruct->Hour_Alarm);
			PCF_DataStruct->Minute_Alarm    = RTC_Bcd2ToBin(PCF_DataStruct->Minute_Alarm);
		}
}

/**************************************************************************
时间信息操作功能函数
**************************************************************************/
/******************************************************************************
  * @Name   : PCF8563写入时间信息
  * @Brief  : none
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  *           PCF_DataStruct: 时间结构指针
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetTime(unsigned char PCF_Format, _PCF8563_Time_Typedef* PCF_DataStruct)
{
		if (PCF_Format == PCF_Format_BIN)  //十进制格式，需要转换一下
		{
			//////////判断数值是否在范围之内
			if (PCF_DataStruct->RTC_Hours > 23)    PCF_DataStruct->RTC_Hours   = 0;  //恢复0小时
			if (PCF_DataStruct->RTC_Minutes > 59)  PCF_DataStruct->RTC_Minutes = 0;  //恢复0分钟
			if (PCF_DataStruct->RTC_Seconds > 59)  PCF_DataStruct->RTC_Seconds = 0;  //恢复0秒

			///////////需要转换一下
			PCF_DataStruct->RTC_Hours   = RTC_BinToBcd2(PCF_DataStruct->RTC_Hours);
			PCF_DataStruct->RTC_Minutes = RTC_BinToBcd2(PCF_DataStruct->RTC_Minutes);
			PCF_DataStruct->RTC_Seconds = RTC_BinToBcd2(PCF_DataStruct->RTC_Seconds);
		}

		//////////拷贝数据
		buffer[0] = PCF_DataStruct->RTC_Seconds;
		buffer[1] = PCF_DataStruct->RTC_Minutes;
		buffer[2] = PCF_DataStruct->RTC_Hours;

		/////////写入数据到寄存器
		PCF8563_Write_nByte(PCF8563_Address_Seconds, 3, buffer);
}

/*******************************************************************************
  * @Name   : PCF8563读取时间信息
  * @Brief  : none
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  * @Output : PCF_DataStruct: 时间结构指针
  * @Return : none
*******************************************************************************/
void PCF8563_GetTime(unsigned char PCF_Format, _PCF8563_Time_Typedef* PCF_DataStruct)
{
		////////读取寄存器数值
		PCF8563_Read_nByte(PCF8563_Address_Seconds, 3, buffer);

		///////////屏蔽无效位
		buffer[0] &= PCF8563_Shield_Seconds;
		buffer[1] &= PCF8563_Shield_Minutes;
		buffer[2] &= PCF8563_Shield_Hours;

		///////////判断需要的数据格式
		if (PCF_Format == PCF_Format_BIN)
		{
			PCF_DataStruct->RTC_Hours   = RTC_Bcd2ToBin(buffer[2]);
			PCF_DataStruct->RTC_Minutes = RTC_Bcd2ToBin(buffer[1]);
			PCF_DataStruct->RTC_Seconds = RTC_Bcd2ToBin(buffer[0]);
		}
		else if (PCF_Format == PCF_Format_BCD)
		{
			///////////拷贝数据
			PCF_DataStruct->RTC_Hours   = buffer[2];
			PCF_DataStruct->RTC_Minutes = buffer[1];
			PCF_DataStruct->RTC_Seconds = buffer[0];
		}
}

/**************************************************************************
日期信息操作功能函数
**************************************************************************/
/*******************************************************************************
  * @Name   : PCF8563写入日期信息
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  *           PCF_Century:    世纪位设定
	* 0-4位为月 7位为世纪    世纪位:0 = 20xx         //20161102
  *                        世纪位:1 = 19xx
  *           PCF_DataStruct: 日期结构指针
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetDate(unsigned char PCF_Format, unsigned char PCF_Century, _PCF8563_Date_Typedef* PCF_DataStruct)
{
		if (PCF_Format == PCF_Format_BIN)  //十进制格式，需要转换一下
		{
			//////////判断数值是否在范围之内
			if (PCF_DataStruct->RTC_Years > 99)    PCF_DataStruct->RTC_Years    = 0;  //恢复00年
			if (PCF_DataStruct->RTC_Months > 12)   PCF_DataStruct->RTC_Months   = 1;  //恢复1月
			if (PCF_DataStruct->RTC_Days > 31)     PCF_DataStruct->RTC_Days     = 1;  //恢复1日
			if (PCF_DataStruct->RTC_WeekDays > 6)  PCF_DataStruct->RTC_WeekDays = 1;  //恢复星期一

			///////////需要转换一下
			PCF_DataStruct->RTC_Years    = RTC_BinToBcd2(PCF_DataStruct->RTC_Years);
			PCF_DataStruct->RTC_Months   = RTC_BinToBcd2(PCF_DataStruct->RTC_Months);
			PCF_DataStruct->RTC_Days     = RTC_BinToBcd2(PCF_DataStruct->RTC_Days);
			PCF_DataStruct->RTC_WeekDays = RTC_BinToBcd2(PCF_DataStruct->RTC_WeekDays);
		}

		////////判断世纪位
		if (PCF_Century == PCF_Century_19xx)
		{
			PCF_DataStruct->RTC_Months |= PCF_Century_SetBitC;
		}
		else
		{
			PCF_DataStruct->RTC_Months &= ~PCF_Century_SetBitC;
		}

		////////////数据拷贝
		buffer[0] = PCF_DataStruct->RTC_Days;
		buffer[1] = PCF_DataStruct->RTC_WeekDays;
		buffer[2] = PCF_DataStruct->RTC_Months;
		buffer[3] = PCF_DataStruct->RTC_Years;
		//////////写入数据到寄存器
		PCF8563_Write_nByte(PCF8563_Address_Days, 4, buffer);
}
/*******************************************************************************
  * @Name   : PCF8563读取日期信息
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  * @Output : *PCF_Century:   世纪位，0：21世纪；1:20世纪
  *           PCF_DataStruct: 日期结构指针
  * @Return : none
*******************************************************************************/
void PCF8563_GetDate(unsigned char PCF_Format, unsigned char *PCF_Century, _PCF8563_Date_Typedef* PCF_DataStruct)
{
		/////////////读取全部寄存器数值
		PCF8563_Read_nByte(PCF8563_Address_Days, 4, buffer);

		////////////判断世纪位数值
		if (buffer[2] & PCF_Century_SetBitC)
		{
			*PCF_Century = 1;
		}
		else
		{
			*PCF_Century = 0;
		}

		//////////屏蔽无效位
		buffer[0] &= PCF8563_Shield_Days;
		buffer[1] &= PCF8563_Shield_WeekDays;
		buffer[2] &= PCF8563_Shield_Months_Century;
		buffer[3] &= PCF8563_Shield_Years;

		///////////判断需要的数据格式
		if (PCF_Format == PCF_Format_BIN)
		{
			PCF_DataStruct->RTC_Years    = RTC_Bcd2ToBin(buffer[3]);
			PCF_DataStruct->RTC_Months   = RTC_Bcd2ToBin(buffer[2]);
			PCF_DataStruct->RTC_Days     = RTC_Bcd2ToBin(buffer[0]);
			PCF_DataStruct->RTC_WeekDays = RTC_Bcd2ToBin(buffer[1]);
		}
		else if (PCF_Format == PCF_Format_BCD)
		{
			////////拷贝数据
			PCF_DataStruct->RTC_Years    = buffer[3];
			PCF_DataStruct->RTC_Months   = buffer[2];
			PCF_DataStruct->RTC_Days     = buffer[0];
			PCF_DataStruct->RTC_WeekDays = buffer[1];
		}
}
/**************************************************************************
闹铃信息操作功能函数
**************************************************************************/
/*******************************************************************************
  * @Name   : PCF8563写入闹铃信息
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  *           PCF_DataStruct: 闹铃结构指针
  *
  * @Output : none
  * @Return : none
*******************************************************************************/
void PCF8563_SetAlarm(unsigned char PCF_Format, _PCF8563_Alarm_Typedef* PCF_DataStruct)
{
		unsigned char Alarm_State = 0;
		unsigned char Alarm_Interrupt = 0;  //控制/状态寄存器闹铃中断缓存
		if (PCF_Format == PCF_Format_BIN)  //十进制格式，需要转换一下
		{
			////////////判断数值是否在范围之内
			if (PCF_DataStruct->RTC_AlarmMinutes > 59)  PCF_DataStruct->RTC_AlarmMinutes  = 0;  //恢复0分钟
			if (PCF_DataStruct->RTC_AlarmHours > 23)    PCF_DataStruct->RTC_AlarmHours    = 0;  //恢复0小时
			if (PCF_DataStruct->RTC_AlarmDays > 31)     PCF_DataStruct->RTC_AlarmDays     = 1;  //恢复1日
			if (PCF_DataStruct->RTC_AlarmWeekDays > 6)  PCF_DataStruct->RTC_AlarmWeekDays = 1;  //恢复星期一

			/////////////需要转换一下
			PCF_DataStruct->RTC_AlarmMinutes  = RTC_BinToBcd2(PCF_DataStruct->RTC_AlarmMinutes);
			PCF_DataStruct->RTC_AlarmHours    = RTC_BinToBcd2(PCF_DataStruct->RTC_AlarmHours);
			PCF_DataStruct->RTC_AlarmDays     = RTC_BinToBcd2(PCF_DataStruct->RTC_AlarmDays);
			PCF_DataStruct->RTC_AlarmWeekDays = RTC_BinToBcd2(PCF_DataStruct->RTC_AlarmWeekDays);
		}

		////////////判断是否开启闹铃选择
		if (PCF_DataStruct->RTC_AlarmNewState == RTC_AlarmNewState_Open)  //只打开闹铃
		{
			Alarm_State = 1;
		}
		else if (PCF_DataStruct->RTC_AlarmNewState == RTC_AlarmNewState_Open_INT_Enable)  //打开闹铃并打开中断输出
		{
			Alarm_State = 2;
		}
		else if (PCF_DataStruct->RTC_AlarmNewState == RTC_AlarmNewState_Close)  //关闭闹铃，并且关闭中断输出
		{
			Alarm_State = 3;
		}

		////////读取控制/状态寄存器2值
		Alarm_Interrupt = PCF8563_Read_Byte(PCF8563_Address_Control_Status_2);
		Alarm_Interrupt &= PCF_Alarm_INT_Close;  //先关闭中断输出
		Alarm_Interrupt &= PCF_Control_ClearAF;;  //清除标志
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_2, Alarm_Interrupt);

		/////////根据开启类型进行相应操作
		if (Alarm_State == 1 || Alarm_State == 2)  //打开闹铃
		{
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Days)      PCF_DataStruct->RTC_AlarmDays     &= PCF_Alarm_DaysOpen;  //日期闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Hours)     PCF_DataStruct->RTC_AlarmHours    &= PCF_Alarm_HoursOpen;  //小时闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Minutes)   PCF_DataStruct->RTC_AlarmMinutes  &= PCF_Alarm_MinutesOpen;  //分钟闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_WeekDays)  PCF_DataStruct->RTC_AlarmWeekDays &= PCF_Alarm_WeekDaysOpen;  //分钟闹铃
		}
		if (Alarm_State == 3)  //关闭
		{
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Days)      PCF_DataStruct->RTC_AlarmDays     |= PCF_Alarm_DaysClose;  //日期闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Hours)     PCF_DataStruct->RTC_AlarmHours    |= PCF_Alarm_HoursClose;  //小时闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_Minutes)   PCF_DataStruct->RTC_AlarmMinutes  |= PCF_Alarm_MinutesClose;  //分钟闹铃
			if (PCF_DataStruct->RTC_AlarmType & RTC_AlarmType_WeekDays)  PCF_DataStruct->RTC_AlarmWeekDays |= PCF_Alarm_WeekDaysClose;  //分钟闹铃
		}

		///////////判断是否开启中断输出
		if (Alarm_State == 2)
		{
			Alarm_Interrupt |= PCF_Alarm_INT_Open;
			Alarm_Interrupt &= PCF_Control_ClearAF;;  //清除标志
		}

		////////////拷贝数据
		buffer[0] = PCF_DataStruct->RTC_AlarmMinutes;
		buffer[1] = PCF_DataStruct->RTC_AlarmHours;
		buffer[2] = PCF_DataStruct->RTC_AlarmDays;
		buffer[3] = PCF_DataStruct->RTC_AlarmWeekDays;

		////////////写入数据到寄存器
		PCF8563_Write_nByte(PCF8563_Alarm_Minutes, 4, buffer);

		////////////写入控制/状态寄存器2数值
		PCF8563_Write_Byte(PCF8563_Address_Control_Status_2, Alarm_Interrupt);
}

/*******************************************************************************
  * @Name   : PCF8563读取闹铃信息
  * @Brief  : 星期数值范围是: 0 ~ 6，十进制格式；只是返回了闹铃寄存器数值，开关位、中断输出什么的不返回
  * @Input  : PCF_Format:     数据格式
  *                           = PCF_Format_BIN
  *                           = PCF_Format_BCD
  * @Output : PCF_DataStruct: 闹铃结构指针
  * @Return : none
*******************************************************************************/
void PCF8563_GetAlarm(unsigned char PCF_Format, _PCF8563_Alarm_Typedef* PCF_DataStruct)
{
		///////////读取全部寄存器数值
		PCF8563_Read_nByte(PCF8563_Alarm_Minutes, 4, buffer);

		///////////屏蔽无效位，分钟报警值全部返回
		buffer[0] &= PCF8563_Shield_Minute_Alarm;  //分钟报警值
		buffer[1] &= PCF8563_Shield_Hour_Alarm;  //小时报警值
		buffer[2] &= PCF8563_Shield_Day_Alarm;  //日期报警值
		buffer[3] &= PCF8563_Shield_WeekDays_Alarm;  //星期报警值

		//////////判断需要的数据格式
		if (PCF_Format == PCF_Format_BIN)
		{
			PCF_DataStruct->RTC_AlarmDays     = RTC_Bcd2ToBin(buffer[2]);
			PCF_DataStruct->RTC_AlarmHours    = RTC_Bcd2ToBin(buffer[1]);
			PCF_DataStruct->RTC_AlarmMinutes  = RTC_Bcd2ToBin(buffer[0]);
			PCF_DataStruct->RTC_AlarmWeekDays = RTC_Bcd2ToBin(buffer[3]);
		}
		else if (PCF_Format == PCF_Format_BCD)
		{
			///////////拷贝数据
			PCF_DataStruct->RTC_AlarmDays     = buffer[2];
			PCF_DataStruct->RTC_AlarmHours    = buffer[1];
			PCF_DataStruct->RTC_AlarmMinutes  = buffer[0];
			PCF_DataStruct->RTC_AlarmWeekDays = buffer[3];
		}
}
