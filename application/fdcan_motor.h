#ifndef FDCAN_MOTOR_H
#define FDCAN_MOTOR_H
#include "struct_typedef.h"
#include "main.h"
#include "fdcan.h"

extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;

typedef struct
{
    uint16_t ecd;
    int16_t speed_rad_s;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
} motor_measure_t;

extern motor_measure_t motor_chassis[6];
extern void FDCAN_cmd_chassis(int16_t motor1,int16_t motor2,int16_t motor3,int16_t motor4,int16_t motor5,int16_t motor6);


#endif
