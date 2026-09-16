#ifndef _VOLT_C
#define _VOLT_C
#include "stm32f4xx_hal.h"
#include "usart.h"
#define DATA_LEN 4
#pragma pack(1)
typedef __packed struct
{
	float Data[DATA_LEN];
	uint32_t End;
}volt_data_t;
typedef union
{
	volt_data_t Volt_Data;
	uint8_t Sent[DATA_LEN*4+4];
}volt_un;
#pragma pack()
extern volt_un volt;
extern void Volt_Sendware(void);
#endif


