#include  "fdcan_motor.h"
#define get_LK8016_measure(ptr, data)                                   \
    {                                                                   \
        (ptr)->last_ecd = (ptr)->ecd;                                   \
        (ptr)->ecd = (uint16_t)(((uint16_t)(data)[7] << 8) | (data)[6]);\
        (ptr)->speed_rad_s = (int16_t)(((uint16_t)(data)[5] << 8) | (data)[4]); \
        (ptr)->given_current = (int16_t)(((uint16_t)(data)[3] << 8) | (data)[2]); \
        (ptr)->temperate = (int8_t)(data)[1];                            \
    }

void FDCAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4, int16_t motor5, int16_t motor6)
{
    FDCAN_TxHeaderTypeDef tx_header;
    uint8_t tx_data[8];
    tx_header.IdType = FDCAN_STANDARD_ID;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;
    tx_header.DataLength = FDCAN_DLC_BYTES_8;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker = 0;

    tx_data[0] = 0xA1;
    tx_data[1] = 0;
    tx_data[2] = 0;
    tx_data[3] = 0;
    tx_data[6] = 0;
    tx_data[7] = 0;

    tx_header.Identifier = 0x141;
    tx_data[4] = (uint8_t)motor1;
    tx_data[5] = (uint8_t)(motor1 >> 8);
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &tx_header, tx_data);

    tx_header.Identifier = 0x142;
    tx_data[4] = (uint8_t)motor2;
    tx_data[5] = (uint8_t)(motor2 >> 8);
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &tx_header, tx_data);

    tx_header.Identifier = 0x141;
    tx_data[4] = (uint8_t)motor3;
    tx_data[5] = (uint8_t)(motor3 >> 8);
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &tx_header, tx_data);

    tx_header.Identifier = 0x142;
    tx_data[4] = (uint8_t)motor4;
    tx_data[5] = (uint8_t)(motor4 >> 8);
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &tx_header, tx_data);

    tx_header.Identifier = 0x200;
    tx_data[0] = (uint8_t)(motor5 >> 8);
    tx_data[1] = (uint8_t)motor5;
    tx_data[2] = (uint8_t)(motor6 >> 8);
    tx_data[3] = (uint8_t)motor6;
    tx_data[4] = 0;
    tx_data[5] = 0;
    tx_data[6] = 0;
    tx_data[7] = 0;
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &tx_header, tx_data);
}


motor_measure_t motor_chassis[6];

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0) > 0)
    {
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data);

        if (hfdcan == &hfdcan1)
        {
            switch (rx_header.Identifier)
            {
                case 0x141:
                    get_LK8016_measure(&motor_chassis[0], rx_data);
                    break;

                case 0x142:
                    get_LK8016_measure(&motor_chassis[2], rx_data);
                    break;

                default:
                    break;
            }
        }
        else if (hfdcan == &hfdcan2)
        {
            switch (rx_header.Identifier)
            {
                case 0x141:
                    get_LK8016_measure(&motor_chassis[1], rx_data);
                    break;

                case 0x142:
                    get_LK8016_measure(&motor_chassis[3], rx_data);
                    break;

                default:
                    break;
            }
        }
    }
}




















