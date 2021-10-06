#include "project.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "ADC_Task.h"
#include "I2C_Task.h"
#include "BLE_Task.h"

#include <stdio.h>
#include <limits.h>
#include <math.h>

//Semaphore for the BLE FreeRTOS Task
SemaphoreHandle_t bleSemaphore;

//Buffers for BLE read service
static uint8_t ADC_bytes[4]; 
static uint8_t I2C_bytes[5];

//Buffers for data conversion operations
static uint16_t ADC_Data[1]; //ADC data
static uint8_t I2C_Data[3]; //I2C data

//Heart Rate buffers and variables
int num_steps = 0;
int beat = 0;
int valley = 0;
int possible_beat = 0;
int possible_val = 0;

//Heart rate sample
float sample[SAMPLE_LENGTH] = {0};


/*********************************************************/
/*********FUNCTION FOR SAMPLING HEART RATE DATA***********/
/*********************************************************/
void fillSampleData(){
    printf(">>Collecting Heart Rate Data\r\n");
    for(int i = 0; i <= SAMPLE_LENGTH; i++){
        sample[i] = 0;
        sample[i] = ADC_GetResult16(0);
        vTaskDelay(10);
    }
}

/*********************************************************/
/***********FUNCTION FOR CALCULATING THE MEAN*************/
/*********************************************************/
float mean(float data[], int len) {
    float sum = 0.0, mean = 0.0;
    int i;
    for(i=0; i<len; ++i) {
        sum += data[i];
    }
    mean = sum/len;
    return mean;
}

/*********************************************************/
/******FUNCTION FOR CALCULATING STANDARD DEVIATION********/
/*********************************************************/
float stddev(float data[], int len) {
    float the_mean = mean(data, len);
    float standardDeviation = 0.0;
    int i;
    for(i=0; i<len; ++i) {
        standardDeviation += pow(data[i] - the_mean, 2);
    }
    return sqrt(standardDeviation/len);
}

/*********************************************************/
/***********FUNCTION FOR MEASURING HEART RATE*************/
/*********************************************************/
void detectPeaks(){
    fillSampleData();
    printf(">>Calculating Heart Rate\r\n");
    float threshold = 6;
    int lag = 3;
    bool possible_peak = false;
    bool possible_valley = false;

    float value_possible_peak = 0;
    float value_possible_valley = 0;

    float value_peak = 0;
    float value_valley = 0;
    float avgFilter[SAMPLE_LENGTH];
    float stdFilter[SAMPLE_LENGTH];

    avgFilter[lag-1] = mean(sample, lag);
    stdFilter[lag-1] = stddev(sample, lag);
    float filteredY[SAMPLE_LENGTH];
    memcpy(filteredY, sample, sizeof(float) * SAMPLE_LENGTH);
    for(int i = lag; i<=SAMPLE_LENGTH; i++)
    {
        avgFilter[i] = mean(filteredY + i-lag+1, lag);
        stdFilter[i] = stddev(filteredY + i-lag+1, lag);
	    if(sample[i] > sample[i-1]){
	       num_steps++;
		        //Looking for the valley
		    if(possible_valley == false){
		 	    //Potential valley has been found
		        possible_valley = true; 
		 	    value_possible_valley = sample[i-1];
                possible_val++;
		        }
	    else {
		    //Looking for the peak
		    if(num_steps >= threshold && fabsf(sample[i] - avgFilter[i-1]) > threshold * stdFilter[i-1]){	
			    //Potential peak has been found
			    possible_peak = true;
			    value_possible_peak = sample[i-1];
                possible_beat++;
		    } 

		    else {
			    //Updating potential valley
			    if(possible_valley == true){
				    if(sample[i] <= value_possible_valley){
				    value_possible_valley = sample[i];
                    possible_val++;
				    }
			    }
			    //Peak has been found
		        if(possible_peak == true){
				    //Updating peak information
		  	        if(sample[i-1] > value_possible_peak || sample[i] > avgFilter[i-1]){
			        value_peak = sample[i-1];
                    beat++;
			    } 
			
			    else {
                    beat++;
			        value_peak = value_possible_peak;
			        }
		        }
			    //Valley has been found
		        if(possible_valley == true){
				    //Updating valley information
		            value_valley = value_possible_valley;
		            possible_valley = false;
                    valley++;
		        }
			    //Updating threshold
		        threshold = 0.6 * num_steps;
		        possible_peak = false;
                filteredY[i] = 0.1 * sample[i] + (1 - 0.1) * filteredY[i-1];
                avgFilter[i] = mean(filteredY + i-lag+1, lag);
		    }
	    }
	    //Resetting number of steps
	    num_steps = 0;
        }
        }
    
printf("Peaks:                  %d \r\n", beat);
printf("Possible Peaks:         %d \r\n", possible_beat);
printf("Estimated Heart Rate:   %d \r\n", 6*beat);
}

/*********************************************************/
/*******FUNCTION FOR INITIALIZING PSOC COMPONENTS*********/
/*********************************************************/
void Init_Components(){
    ADC_Start();
    UART_Start();
    ADC_StartConvert();
    I2C_Start();
    printf(">>Components Initialized!\r\n");
}

/*********************************************************/
/*****FUNCTION FOR FETCHING TEMPERATURE THROUGH I2C*******/
/*********************************************************/
float getTemperature(){
    float raw = 0;
    float raw2 = 0;
    
    Cy_SCB_I2C_MasterSendStart(I2C_HW, sensorAddress, CY_SCB_I2C_WRITE_XFER, 0, &I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW, MAX30205_TEMPERATURE, 0, &I2C_context);
    Cy_SCB_I2C_MasterSendReStart(I2C_HW, sensorAddress, CY_SCB_I2C_READ_XFER, 0, &I2C_context);
    
    for(uint i = 0; i<sizeof(I2C_Data)-1; i++ ){
        Cy_SCB_I2C_MasterReadByte(I2C_HW, CY_SCB_I2C_ACK, &I2C_Data[i], 0, &I2C_context);
        raw = I2C_Data[0]; //MSB
        raw2 = I2C_Data[1] * 0.00390625; //LSB
        temperature = raw + raw2;
    }
    
    Cy_SCB_I2C_MasterReadByte(I2C_HW, CY_SCB_I2C_NAK, &I2C_Data[sizeof(I2C_Data)], 0, &I2C_context);
    Cy_SCB_I2C_MasterSendStop(I2C_HW, 0, &I2C_context);
    
    return temperature;
}

/*********************************************************/
/*******FUNCTION FOR TX TEMPERATURE DATA OVER BLE*********/
/*********************************************************/
void sendTempData()
{
    cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
    serviceHandle.attrHandle = CY_BLE_TEMPERATURE_TEMPERATURE_CHAR_HANDLE;
    
    char tempChar[5];
    
    sprintf(tempChar, "%f", getTemperature());
    
    for(uint i = 0; i<sizeof(I2C_bytes); i++)
    {
    I2C_bytes[i] = tempChar[i];
    }
    
    serviceHandle.value.len = sizeof(I2C_bytes);
    serviceHandle.value.val = (uint8_t*) &I2C_bytes;
    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
}

/*********************************************************/
/*********FUNCTION FOR ADC DATA TRANSFER OVER BLE*********/
/*********************************************************/
void writeRefValue(){
    //Value pair for the BLE service
    cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
    
    //Attribute to read
    serviceHandle.attrHandle = CY_BLE_ADCVAL_ADC_CHAR_HANDLE;
    //ADC Value
    ADC_Data[0] = ADC_GetResult16(0);
    //String for conversion
    char charVal[5];
    //Conversion of 16 bits decimal number (Decimal to ASCII)
    sprintf(charVal, "%d", ADC_Data[0]);
    //Passing each ASCII character to 8-bit unsigned integer 
    for (int i = 0; i<(int)sizeof(ADC_bytes);i++)
    {
    ADC_bytes[i] = charVal[i];
    }
    //Assigning buffer to packet sent over BLE
    serviceHandle.value.len = sizeof(ADC_bytes);
    serviceHandle.value.val = (uint8_t*) &ADC_bytes;
    //Updating local GATT database
    Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
}

/*********************************************************/
/************FUNCTION FOR LED SDI SIGNAL SHIFT************/
/*********************************************************/
void shiftOut(uint16_t ulBitOrder, uint16_t ulVal)
    {
        uint8_t i;
        uint16_t mask_MSB = 0x8000; // 1...(15)0
        uint16_t mask_LSB = 0x0001; // 0(15)... 1
        
        //To keep LEDs off while shifting into register
        Cy_GPIO_Set(OE_PORT, OE_NUM);
        bool output = false;
        for (i = 0; i < 16; i++)
        {         
            if (ulBitOrder == 1){               
                output = ulVal & mask_MSB;
                ulVal = ulVal << 1;
            }
            else{               
                output = ulVal & mask_LSB; 
                ulVal = ulVal >> 1;
            }
            Cy_GPIO_Set(CLK_PORT, CLK_NUM);
            Cy_GPIO_Write(SDI_Port, SDI_Num, output);
            Cy_SysLib_Delay(1);
            Cy_GPIO_Clr(CLK_PORT, CLK_NUM);
          }
    }

/*********************************************************/
/*****FUNCTION FOR ENABLING LEDS OF DIFFERENT COLORS******/
/*********************************************************/
void enableLED(uint8_t LedNo){
        printf(">>Starting LED register shifting! \n\r");
        Cy_GPIO_Clr(LE_PORT, LE_NUM);
        Cy_GPIO_Clr(CLK_PORT, CLK_NUM);
        //To keep LEDs off while shifting into register
        Cy_GPIO_Set(OE_PORT, OE_NUM); 
        
        if(LedNo == 1){
            shiftOut(0, RED);
        }
        else if (LedNo == 2){           
            shiftOut(0, GREEN);
        }
        else if (LedNo == 3){
            shiftOut(0, IR);           
        }     
        Cy_GPIO_Set(LE_PORT, LE_NUM);
        Cy_GPIO_Clr(LE_Port, LE_Num);
        Cy_GPIO_Clr(OE_PORT, OE_NUM);
        
        printf(">>LED Enabled Successfully! \n\r");
    }

/*********************************************************/
/*********CALLBACK FUNCTION BLE SERVICE HANDLING**********/
/*********************************************************/
void callback(uint32_t event, void *eventParam)
{
    cy_stc_ble_gatts_write_cmd_req_param_t  *writeReqParameter;
    switch (event)
    {
        case CY_BLE_EVT_STACK_ON:
        printf(">>Start advertising\r\n");
        Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
        break;
        
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            printf(">>Device disconnected!\r\n");
            Cy_GPIO_Set(OE_PORT, OE_NUM); //turn off the led when disconnected
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            printf(">>Start advertising!\r\n");
            break;
            
        case CY_BLE_EVT_GATT_CONNECT_IND:
            printf(">>Device connected!\r\n");
        break;
            
        case CY_BLE_EVT_GATTS_WRITE_REQ:
            
            writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *)eventParam;
            
            if(CY_BLE_LED_CHANGE_LED_CHAR_HANDLE == writeReqParameter->handleValPair.attrHandle)
            {
                uint8_t val = writeReqParameter->handleValPair.value.val[0];

                if(val==49) 
                {
                    val=1;
                    enableLED(val);
                    vTaskDelay(100);                
                    detectPeaks();
                }
                else if(val==50) 
                {
                    val=2;
                    enableLED(val); 
                    vTaskDelay(100);
                    detectPeaks();
                }
                else if (val == 51) {
                    val = 3;
                    enableLED(val); 
                    vTaskDelay(100);
                    detectPeaks();
                }
                else writeRefValue();
            }
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        default:
            sendTempData();
            writeRefValue();
            break;
    }

}
    
/*********************************************************/
/******FUNCTION FOR HANDLING BLE FreeRTOS INTERRUPTS******/
/*********************************************************/
void bleInterruptNotify(){
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(bleSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*********************************************************/
/******FUNCTION FOR BLE FreeRTOS TASK INSTRUCTIONS********/
/*********************************************************/
void bleTask(void *arg){

    (void) arg;
    Init_Components();
    printf(">>>BLE Task Successfully Started!\r\n");
    
    bleSemaphore = xSemaphoreCreateCounting(UINT_MAX, 0);
    Cy_BLE_Start(callback);
    
    while(Cy_BLE_GetState() != CY_BLE_STATE_ON)
    {
        Cy_BLE_ProcessEvents();
    }
    
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);
    

    for(;;)
    {
        xSemaphoreTake(bleSemaphore, portMAX_DELAY);
        Cy_BLE_ProcessEvents();
    }
}

/* [] END OF FILE */
