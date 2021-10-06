
#pragma once

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include <limits.h>


#define LE_Port  P0_5_PORT
#define LE_Num   P0_5_NUM

#define AMP_Port P5_5_PORT
#define AMP_Num  P5_5_NUM

#define OE_Port  P7_2_PORT
#define OE_Num   P7_2_NUM

#define SDI_Port P12_6_PORT
#define SDI_Num  P12_6_NUM

#define CLK_Port P12_7_PORT
#define CLK_Num  P12_7_NUM

#define SDA_Port P6_5_PORT
#define SDA_Num  P6_5_NUM

#define SAMPLE_LENGTH           200

//COLORS EXPRESSED IN HEX VALUES FOR LED DRIVER REGISTER
static uint16_t RED = 0x0001;
static uint16_t GREEN = 0x0002;
static uint16_t IR = 0x000C;


float mean(float data[], int len);
float stddev(float data[], int len);
void detectPeaks();
void fillSampleData();






/* [] END OF FILE */
