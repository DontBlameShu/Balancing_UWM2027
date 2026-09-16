/*
 * @Name: lolt.c
 * @Description: volt+上位机底层程序,留出Volt_Sendware函数DATA结构体+VOLT共用体供调用
 * @Author: source
 * @Copyright: SixuanRobomasterLab
 */
#include "volt.h"
#include "stdio.h"
volt_un volt;
/**
 * @Name: Volt_Sendware
 * @Description:发送 协议     在scheduler_task文件中中调用Volt_Sendware());即可
 * @Param: void
 * @Return: void
 * @Author: source
 * @Warning: void
 */
void Volt_Sendware()
{
    static uint8_t vofa_cnt = 0;

    if(++vofa_cnt < 10)
        return;

    vofa_cnt = 0;

    volt.Volt_Data.End = 0x7f800000;
    HAL_UART_Transmit(&huart1, volt.Sent, sizeof(volt.Sent), 1);
}
