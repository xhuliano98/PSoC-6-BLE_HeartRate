
#include "project.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <stdio.h>
#include <limits.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x0800 ? '1' : '0'), \
  (byte & 0x0400 ? '1' : '0'), \
  (byte & 0x0200 ? '1' : '0'), \
  (byte & 0x0100 ? '1' : '0'), \
  (byte & 0x0080 ? '1' : '0'), \
  (byte & 0x0040 ? '1' : '0'), \
  (byte & 0x0020 ? '1' : '0'), \
  (byte & 0x0010 ? '1' : '0'), \
  (byte & 0x0008 ? '1' : '0'), \
  (byte & 0x0004 ? '1' : '0'), \
  (byte & 0x0002 ? '1' : '0'), \
  (byte & 0x0001 ? '1' : '0') 


cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
cy_stc_ble_gatt_value_t serviceData;

void callback(uint32_t event, void *eventParam);
void shiftOut(uint16_t ulBitOrder, uint16_t ulVal);
void enableLED(uint8_t LedNo);
void writeRefValue();
void sendTempData();
void bleInterruptNotify();
void bleTask(void *arg);

/* [] END OF FILE */
