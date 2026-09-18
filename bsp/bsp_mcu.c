/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bsp_mcu.c
  * @brief          : MCU peripheral initialization functions
  * @author         : GrassFan Wang
  * @date           : 2025/01/22
  * @version        : v1.0
  ******************************************************************************
  * @attention      : none
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "bsp_mcu.h"
#include "bsp_gpio.h"
#include "bsp_can.h"
#include "bsp_pwm.h"
//#include "bsp_uart.h"
#include "bmi088.h"

/**
  * @brief Initializes the MCU.
  */
void MCU_Init(void)
{
  /* ----------------------- BSP Init ----------------------- */
  BSP_PWM_Init();
	BSP_GPIO_Init();
  fdcan_filter_init();
 // BSP_USART_Init();
  /* ----------------------- Device Init ----------------------- */
  BMI088_Init();
}
//------------------------------------------------------------------------------
