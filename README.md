# PSoC-6-BLE_HeartRate
Project for Embedded Systems, using a PSoC 6 and also a PPG EduKit (created by VUB) attached to it. Uses Red, Green and IR LED lights and a photodetector to measure light absorption and generate a current.    

Date: 22/06/2021

# Software Engineering for Embedded Systems

# Heart Rate and Blood Saturation Measurement using PPG EduKit

Done By:

Tatazi Xhuliano – 0574551


# Table of Contents

[Abstract 3](#_Toc84410537)

**[ProjectSteps](#_Toc84410538)**

[ProjectPlanning](#_Toc84410539)

[Project Implementation](#_Toc84410540)

[Project Delivery](#_Toc84410541)

**[Theoretical Observations](#_Toc84410542)**

[PPG Signal](#_Toc84410543)

[Heart Rate](#_Toc84410544)

[Robust Peak Detection Algorithm (RPD)](#_Toc84410545)

[Mountaineer&#39;s Method for Peak Detection (MMPD)](#_Toc84410546)

[Finite State Machine (FSM)](#_Toc84410547)

**[Hardware](#_Toc84410548)**

[PSoC 6](#_Toc84410549)

[PPG EduKit](#_Toc84410550)

[LED Driver](#_Toc84410551)

[ADC (Analog-to-Digital Converter)](#_Toc84410552)

[UART (Universal Asynchronous Receiver-Transmitter)](#_Toc84410553)

[I2C (Inter-Integrated Circuit)](#_Toc84410554)

**[Software](#_Toc84410555)**

[PSoC Creator](#_Toc84410556)

[LED Driver](#_Toc84410557)

[Temperature Sensor](#_Toc84410558)

[Heart Rate](#_Toc84410559)

**[Conclusion](#_Toc84410560)**

**[Output](#_Toc84410561)**

**[Problems and Difficulties Encountered](#_Toc84410562)**

**[References](#_Toc84410563)**

## Abstract

Our project is about measuring the heart rate and blood oxygen saturation by using PPG signal. We were provided with two devices, one PSoC 6 which would help us with the embedded device part and the PPG EduKit which was connected through a PCB Arduino board.Thegoalofourprojectistodefineanalgorithmformeasuringtheheartrateandthen another for the blood saturation. After defining the algorithms, we had to implement BLE communication and display results through I2C to an Arduino Display and retrieve temperature data. The PPG EduKit has three different LEDs interfaced by a LED Driver and a photodetector to measure the light absorbed which will be useful for later on calculations including a temperature sensor. We managed to convert the analog signal to digital and tried the output values on MATLAB to check what kind of heart rate output we get. On our second trial of the project, we succeeded to devise an algorithm in C language for the peak detection of the signal by adapting two different algorithms, from which we got acceptable results. And also implemented Bluetooth (BLE) services for different datatransmission.

# ProjectSteps

### ProjectPlanning

In our project the first milestone to achieve was understanding all the medical terminology in the provideddocumentsforreference.Thenwehadtomakeastep-by-stepplantofollowinorderforour device to work properly asfollows:

1. Understand terminology and referenced documents of theproject.
2. Identify and understand the signal flow in thedevice.
3. Clearly understand the circuit and each componentfunctionalities.
4. Gathering information regarding signalprocessing.
5. Understanding the requirements of the device to startup.
6. Understanding the algorithms provided by references and gathering otherresources.
7. Apply the algorithms and observe theresult.

### Project Implementation

The implementation of the project had the most difficult part, it started on the phase of understanding the device requirements to start up. We had to follow some steps:

1. Understand the start and end points of the device in order to begin with the signal acquisition.
2. Understand the LED Driverdatasheet.
3. Trying to change the LEDs duringruntime.
4. Connecting the last amplifier on the PPG EduKit with anADC.
5. Understanding different configurations of theADC.
6. Implementing the ADC in runtime, so we could start gettingvalues.
7. Implementing the temperature sensor communication throughI2C
8. Adding BLEfunctionalities

### Project Delivery

The delivery of the project was supposed to be a complete product which would show the results on the LCD display mounted to the PPG EduKit. We had difficulties in adapting C++ language to PSoC Creator so we couldn&#39;t use the display, but we implemented an algorithm for the peak detection of the signal and retrieved information from the temperature sensor and transmitted the data via BLE. The LEDs are also controllable remotely with BLE but with some minimal restrictions due to lack of information about the LEDDriver.

# Theoretical Observations

### PPG Signal

As mentioned before, in our project we have to use the PPG signal to calculate the HR (Heart Rate) and SpO2 (Blood Oxygen Saturation). These two measurements are done independently from each other but both from the PPG signal. This signal is acquired by the current that the photodetector generates by absorbing lights from the LED. The current generated it&#39;s composed by two different components, AC that stands for Alternating Current and DC which stands for Direct Current. These two currents compose the graph of the PPG Signal with the help of a bar graph. The AC component is related to variations of blood volume in synchronization with the heart beat, as for the DC component we understood that it shows minor changes related to respiration that is caused by optical signals reflected or transmitted by the tissue. This kind of signal is widely used in today technology and mostly in wearable embedded devices which we use in our everyday life [4],[5].

![](RackMultipart20211006-4-w5iuf7_html_d5c831c361172621.png)

_Figure __1:__ Mathematical __model__ of __a__ pure __PPG__ signal__[9]_

### Heart Rate

The heart rate is a very important in medical observations and mostly to know when a patient cardiovascular system is performing as it should. The heart rate can be measured in the peripheral circulation of the body (ear lobe, finger, chest, etc.) and it should be a really precise measurement that updates over time. For measuring there are various techniques in today&#39;s technology. The PPG and ECG signals are mostly used, with the PPG EduKit we have different filters for the signal that will beexplainedlateron.From the PPG Wave form we have to analyze the AC component as we said that it is in synchronization with the heartbeat.[10] So, we have to follow some steps to calculate it, generally said we should:

1. Start the device and get the PPG Filtered Signalvalues
2. Make an algorithm that identifies and counts the peaks of thesignal
3. Define the algorithm in such way that it takes a measurement of 10 seconds repeatedly by counting peaks and multiplies the result by 6 in order to have the output in BPM (beats per minute)[11]

SpO2

As for the Blood Oxygen Saturation, it has a different way of measurement. To calculate it we need to configure the application for taking two different measurements in different wavelengths:

1. In the IR (Infra-Red) spectrum or 940nm wavelength for Oxyhemoglobin
2. In the Red-light spectrum or 660nm wavelength for the Deoxyhemoglobin

To perform these calculations, we had to implement a runtime switching for the LED Driver in order to enable the two different outputs and a switch to indicate the start of the measurements. Then by making the ratio of the two outputs, we can get the absorption of light.

![](RackMultipart20211006-4-w5iuf7_html_a0f75526f10d8fbe.jpg)

_Figure 2: Light absorption of hemoglobin in blood [1]_

As we can see in the graph shown above, the Deoxyhemoglobin has highest absorption rate on the IR wavelength and the Oxyhemoglobin in the Red wavelength so that&#39;s the only reason why we need switching.

### Robust Peak Detection Algorithm (RPD)

This algorithm works by using the principle of dispersion of data by using z-scores. This method uses 3 inputs for the process like Lag which is described as the size of the moving window, Influence which refers to the influence of the new signal on the mean and standard deviation of the sample window and Threshold which refers to the z-score at which the algorithm signals, it is a robust algorithm because it constructs a moving mean across the sample data such that signals are not corrupted by threshold.[12]

### Mountaineer&#39;s Method for Peak Detection (MMPD)

Unlike the RPD algorithm that is more related to a statistical approach, this method has been developed for low-amplitude peak detection of PPG signals. It goes like a filter through the data by filtering them and checking if they meet the conditions to be considered peaks or valleys. This method looks more at a logical side of the problem rather than a statistical side.[13]

### Finite State Machine (FSM)

The Bluetooth connectivity requires a real-time operating system to work on top in order to keep alive the connection so we decided to use FreeRTOS in our case. The operating system (OS) is set on 100 Hz tick rate and with a heap size of (48\*1024). The system has only one task in runtime which handles the Bluetooth. After the Bluetooth stack is initialized, the other components like ADC, I2C and UART are initialized while the BLE service is set up in the main process.

![](RackMultipart20211006-4-w5iuf7_html_25e93222d997ba25.png)

The Bluetooth stack needs a callback method to be set in order to handle different BLE packets, the method first waits for the stack to turn on and then starts advertising packets requesting for connection, after a packet is received it is translated by the BLE module and an event is created which is still handled by the callback method. In our case we had three two main event types which were read and write, the BLE stack has three different kind of services, each of 16-bits, the ADC value which is set to read together with the temperature service and the write service which is used to turn on the LEDs and start measuring the heart rate. Each time a service is executed, the BLE stack goes back to waiting for packets that can be processed by the callbackfunction.

The heart rate measurement starts after a LED is turned on, after the device receives the write request for changing the LED color, we used the task delay function in FreeRTOS in order to achieve a 1 second delay for the ADC values to be stabilized. After the LED is turned on, next we had to fill up a sample for the data to be stored, we found more suitable a sample size of 200 entries since a loop of 200 iterations could give unnormal behavior. Each entry has a delay on 0.1s from each other which is done inside the loop that fills the sample buffer. After the data is retrieved, a peak detection algorithm iterates again throughout all the data and analyzes it by some conditionals which classify the data into peaks or possible peaks and valleys or possible valleys, we are more interested in the peaks since we&#39;re dealing with low-amplitude signal. After the data is processed an estimation and filter of the data is done, through UART we printed an estimated heart rate and also the possible peaks along with the truepeaks.

As for the temperature and ADC value which are read from the BLE GATT database is pretty simple, when the controller receives a read request, a method for the specific function does the serial communication (temperature case) and the ADC information retrieval. Both of them are structured the same way and work the same way, after the value is retrieved from the sensor, a conversion from digit to ASCII to HEX is done in order to fill up the buffer for the service and send it as a packet via BLE.

# Hardware

### PSoC 6

It is a low-cost device that supports BLE communications for IoT. The device is made up by different parts such as the microcontroller unit (MCU), Analog &amp; Digital blocks, a block that supports the communication interface, Bluetooth low energy and also an input/output subsystem.

![](RackMultipart20211006-4-w5iuf7_html_a2bfb4d5d215b213.jpg)

_Figure 3: PSoC 6 Prototyping Board_

The MCU is built with a dual-core architecture (150Mhz ARM Cortex M4 &amp; 100MHz Arm Cortex M0+ CPUs). It supports ultra-low-power (0.9V) and low-power (1.1V) modes and below that we have 1MB Flash memory and a 288Kb SRAM with DMAcontroller.The analog block is made up by 2 opamps and 2 low power comparators, 12-bit SAR ADC and 12-bit DAC and the last component in the analog block is CapSense (Capacity sensing block). The digital block is made up of 12 UDB (universal digital blocks) and 32 TCPWM blocks (timer/counter/pulse-widthmodulator).

Regarding the communication interface of the PsoC6, it is made up of 8 serial communication blocks and 2 deep sleep serial communication blocks, I2S and PDM-PCM (Pulse-Density Modulation and Pulse-Code Modulation) converter + USB 2.0.

The BLE block or Bluetooth low energy supports a 5.0 Radio with a 2mbps data throughput, and the input/output subsystem is made up of 36 GPIOs (General Purpose Input/Output pins).

![](RackMultipart20211006-4-w5iuf7_html_b10d7b021c7f0505.jpg)

_Figure 4: PSOC 6 block diagram [3]_

### PPG EduKit

The PPG EduKit is a device designed at VUB by the ETRO Department of the Faculty of Engineering and is used to obtain the PPG signal using two different sensor setups, but in our case we used the one that obtains the signal through some analog modules with user-tunable analog conditioning stages, which use one photodetector and three different wavelengths (green, red and infrared) [8]. This setup will be explained in detail how does it work later in this chapter. On the PPG EduKit there is also a LCD display for real-time plotting of the PPG signal or the calculated heart rate and blood oxygen saturation and a LED Driver that is used to power up the three different wavelengths on the LEDs analog module. Finally, it has a temperature sensor (MAX30205) to measure the temperature of the user and a generic push-button (SW1) and a RGB LED (neopixel), which can be programmed by the user asdesired.

The shape and pinout of the PPG EduKit is an Arduino lookalike, but it operates with a logic level voltage of 3V3 instead of 5V that usually Arduino microcontrollers use. A PSOC 6 prototyping board is connected underneath the PPG EduKit with an Arduino-to-PSOC6 bridge board.

The current generated by the photodetector in the LEDs analog module is converted to voltage and amplified by the Transimpedance Amplifier (TIA) module, highlighted with green colorat Figure 5. In the TIA module there is a 20KOhm potentiometer (blue box) and a 22 KOhm resistor R1, which are used to yield the best signal quality for RED and IR light. After the TIA module, the amplified voltage is filtered first by a first order high band-passfilter(HPF module shown with yellow outline at Figure 1) and then by a low band-pass filter(LPF module shown with purple outline at Figure 5).Thisfiltering removes the noise and the DC (direct current) component. After the two filters, an inverting amplifier, highlighted with blue color at Figure 5, amplifies and inverts the denoised PPG signal [8].

![](RackMultipart20211006-4-w5iuf7_html_6bf11ad34d3bfb64.jpg)

_Figure 5: PPG EduKit device (own processing)._

On Figure 6 are shown the analog conditioning stages of the 4 analog modules of the PPG EduKit.

![](RackMultipart20211006-4-w5iuf7_html_99a28d1de5ddeda3.jpg)

_Figure 6: Analog conditioning stages of the analog module [8]_

### LED Driver

The TLC5925 is our LED Driver incorporated with the PPGEduKit. The driver consists of 16 outputs for LEDs, SDI (Serial-data Input to the Shift register), Clock, Latch Enable and Output Enable. This driver&#39;s outputs were connected to the inputs of the LED block containing three different LEDs, Green, Red and Infrared. The driver contains a 16-bit shift register that is loaded by the SDI. An external resistor was applied to the driver on the board of the PPG EduKit to modify the drivingcurrent [2].

### ADC (Analog-to-Digital Converter)

We are dealing with analog signal and we need to convert it to digital signal in order to make it easier to process, store and as well minimize errors of the signal. We have tried different configurations of the ADC, but we got the most similar values with the samples on the below defined settings:

  1. Vref to Vdda so we can bring down the voltage of the ADC from 5.5V to3.3V
  2. Sampling rate of256
  3. Number of channels to1
  4. Enabledaveraging
  5. Compare mode to &quot;(Result\&lt;Low) or (High \&lt;=Result)&quot;

![](RackMultipart20211006-4-w5iuf7_html_c6c32e1b252143ec.png)

_Figure 7: ADC component on PSOC Creator&#39;s TopDesign (own processing)._

![](RackMultipart20211006-4-w5iuf7_html_ca76571ffc1ca585.png)

_Figure 8: ADC component configuration on PSOC Creator (own processing)_

### UART (Universal Asynchronous Receiver-Transmitter)

Usually, it is found as in IC (Integrated Circuit) and it is used for serial communication over peripheral (USB) connection. Usually it is used for debugging, so when we used to get stuck on the code usually used print statements to identify which part of the code was getting stuck. It&#39;s asynchronous that means that there is no clock signal to synchronize the output bits from the transmitting device to receiving one, it has configurable speed (Baud) in our case we used 115200 baud for communication. It&#39;s the best tool that a developer can have [7].

### I2C (Inter-Integrated Circuit)

Is a serial communication protocol which transfers the data bit by bit along a single wire which is the SDA line, it is synchronous, so the output of bits is synchronized to the sampling of bits by a clock signal controlled by the master and it&#39;s shared between the master and a slave/s. The term master refers to the controller of the clock line and slave refers to the responding circuit which cannot control or initiate the clock line. In our case we used it for the temperature sensor. Each sensor that works with I2C has an address of a register defined in the datasheet from which we get the bits for the sensor value. The register is made by a 16-bits value where the MSB represent the actual temperature digits and the LSB represent the decimal value of the temperaturesensor.

# Software

### PSoC Creator

For our project we had to use PSoC Creator since it&#39;s the most suitable IDE for PSoC 6. In the IDE we have different files and schemas to deal with like main files, top design, pins, etc. in the following sections each component used will be explained more in details. As for the device we used the CM4 processorandmainfileforourmainoperations.WewilltalkabouthowwemanagedtostartupLEDs, ADC, UART and how we used MATLAB for ourcase.

### LED Driver

The LED Driver was about the three different LEDs (Green,Red,IR). In order for the driver to work we need a clock because it uses the rising edge for the SDI input. The SDI input is the one that defines by using HIGH/LOW values on the rising edge of the clock, which of the outputs will be enabled but thisisnotall.After we have passed the signal through SDI, we have to confirm it with the latch enable pin by changing its value from LOW to HIGH and then again to LOW, after confirming the register shift we have to enable the defined outputs by pulling LOW the output enable pin[2].

![](RackMultipart20211006-4-w5iuf7_html_21babf2d02cf6b00.png)

_Figure 9: Timing diagram [2]_

voidshiftOut(uint16\_tulBitOrder,uint16\_tulVal)

{

uint8\_ti;

uint16\_tmask\_MSB=0x8000;//1...(15)0 uint16\_tmask\_LSB=0x0001;//0(15)...1

//TokeepLEDsoffwhileshiftingintoregister Cy\_GPIO\_Set(OE\_PORT,OE\_NUM);

booloutput=false; for(i=0;i\&lt;16;i++)

{

if(ulBitOrder==1){ output=ulVal&amp;mask\_MSB; ulVal=ulVal\&lt;\&lt;1;

}

else{

output=ulVal&amp;mask\_LSB; ulVal=ulVal\&gt;\&gt;1;

}

Cy\_GPIO\_Set(CLK\_PORT,CLK\_NUM);

Cy\_GPIO\_Write(SDI\_Port,SDI\_Num,output); Cy\_SysLib\_Delay(1); Cy\_GPIO\_Clr(CLK\_PORT,CLK\_NUM);

}

}

### Temperature Sensor

As mentioned above in I2C the temperature sensor which has registers provided in the datasheet for different use cases [14] . In our case we used only the temperature register address which by using I2C it first sends a start signal to the sensor address and then it changes state from write to read [15]. It reads a 16-bit register value that is divided in two octets defined as Most Significant Byte and Least Significant Byte (MSB and LSB). MSB part contains the temperature in integer and the second one is converted to decimals by multiplying the LSB with 2-8 (0.00390625). After the information is retrieved, it is sent over BLE with the respectiveservice.

### Heart Rate

Since we implemented the algorithm for the peak detection, we decided to use UART to print the results of the algorithm and debug in case there would be an undefined behavior of the system. It is used to indicate the different BLE events like the task starting, start advertising, device connected and messages to indicate the LED changing and sampling of the data along with the processing.

![](RackMultipart20211006-4-w5iuf7_html_30a5d9e5a72a26ad.png)

_Figure 10: UART component on PSOC Creator&#39;s TopDesign (own processing)._

![Shape1](RackMultipart20211006-4-w5iuf7_html_2ea072fe121bb05a.gif)//Potential valley has been found possible\_valley = true; value\_possible\_valley=sample[i-1]; possible\_val++;

}

else {

//Looking for the peak

if(num\_steps\&gt;=threshold&amp;&amp;fabsf(sample[i]-avgFilter[i-1])\&gt;threshold\*stdFilter[i-1]){

//Potential peak has been found possible\_peak = true; value\_possible\_peak = sample[i-1]; possible\_beat++;

}

else {

//Updating potential valley if(possible\_valley == true){ if(sample[i] \&lt;= value\_possible\_valley){ value\_possible\_valley = sample[i]; possible\_val++;

}

}

//Peak has been found if(possible\_peak == true){

//Updating peak information

if(sample[i-1] \&gt; value\_possible\_peak || sample[i] \&gt; avgFilter[i-1]){ value\_peak=sample[i-1];

beat++;

}

else { beat++;

value\_peak = value\_possible\_peak;

}

}

//Valley has been found if(possible\_valley == true){

//Updating valley information value\_valley = value\_possible\_valley; possible\_valley = false;

valley++;

}

//Updating threshold threshold = 0.6 \* num\_steps; possible\_peak =false;

filteredY[i] = 0.1 \* sample[i] + (1 - 0.1) \* filteredY[i-1]; avgFilter[i]=mean(filteredY+i-lag+1,lag);

}

}

//Resettingnumberofsteps num\_steps = 0;

}

}

printf(&quot;Peaks: %d \r\n&quot;, beat); printf(&quot;PossiblePeaks: %d \r\n&quot;, possible\_beat); printf(&quot;EstimatedHeartRate:%d\r\n&quot;,7\*beat);

_}_

The algorithm for the heart rate iterates over all the sample and it compares different consecutive values by measuring the standard deviation and mean of the moving window of the algorithm as mentioned in the RPD algorithm, it has qualities of the MMPD algorithm like the threshold which empirically increases with 6 times the number of steps going upward the slope. Each time the value increases, the algorithm waits for the decreasing part of the slope in order to define the peak value and set the flag of the expected upcoming valley. After the sample data is finished analyzing, the peaks found are printed along with the possible peaks and an estimated heart rate value.

# Conclusion

After taking the measurements from the device of the 2 different LEDs (RED &amp; IR) we passed the values with UART to the MATLAB algorithm that we found. But from the tests we concludedandtheresultsweobtainedfromtheMATLABalgorithmoutput;weevaluatedthe heart rate to be 64.9 beats per minute. According to health experts it is said that a normal heart rate should have between 60-100 beats per minute, but this rate can also vary from minute to minute. As per the results that we got for the blood oxygen saturation (SpO2), we can see that the output is 78.1 which is out of the boundaries for a healthy individual. If your blood oxygen saturation falls below 95%, please consult with a medicalexpert.

#####

After implementing the algorithm for the heart rate in C language, we had almost finished and achieved our end goal of the project. We had some difficulties with the algorithms at first to understand the way they worked, while we implemented each of them, we noticed that both algorithms were finding possible peaks but no actual ones. We thought of combining both of them into a single algorithm, so we choose the MMPD general structure of the algorithm and added the statistical conditions of RPD to be met by the signal in order for it to detect the right peaks. After a lot of use cases that we tried with different configurations of the algorithm, we concluded for using the current parameters which gave a good result the more wemeasured.

# Output

Below screenshots show different outputs of the implemented services like BLE, Heart Rate, Temperature and ADC.

![Shape2](RackMultipart20211006-4-w5iuf7_html_f02f1efbbc811585.gif)

_1 - Temperature Screenshots of CySmart App_

![](RackMultipart20211006-4-w5iuf7_html_f67a511f2c10ee0.png)

_2 -ADC Value Printed in CySmart App_

![](RackMultipart20211006-4-w5iuf7_html_805bd0785fc5754c.jpg)

_3_ _- BLE Services User Characteristics in LightBlue App_

![](RackMultipart20211006-4-w5iuf7_html_66d889f5844d06fd.png) ![](RackMultipart20211006-4-w5iuf7_html_4462c6df514cadca.png)

_4 - Terminal Output of the Heart Rate_

# Problems and Difficulties Encountered

Along the way of developing the application for the device we encountered a lot of obstacles which looked like impossible tasks at first but the more we were trying to fix and debug the more we realized that the solution most of the times was just in front of us, but we couldn&#39;t notice it. Mainly the problems we encountered were in the software part of the project but nevertheless on the other parts we had problems too, as for example:

-
#### Project Planning

1. Difficulties sharing the workload in an equal way in order for all the members to work and not be leftout.
2. Dividing the tasks in such way that each of them is suitable to the team memberbackground.
3. Defining the steps of the application developmentlifecycle.
4. Gathering the right resources from trustworthysources.
5. Build up a stable project goal by adding the features in a structuredway.

-
#### ProjectImplementation

1. Understanding how to start our project, meaning what were the first steps we had totake
2. Intensive learning of the Clanguage.
3. Problems with the device components like the LED Driver which we couldn&#39;t figure out how it works,this limited the device functionality since it does not allow to turn on the LEDs in a different order other than RED \&gt;\&gt; Green \&gt;\&gt; IR.
4. Problems with the BLE protocols and services, in order to understand how the stack worked and how the BLE task behaved it required an intensive debugging of thecode.
5. Understanding the conversion of different formats like from a 16-bit integer to an 8-bit integer and the conversion of different values to HEX format in order to pass the values to the BLE stack.
6. Finding the right parameters for specific services and specific functions which required a lot of tests andtrials.
7. BLE stack problems like device disconnection because of FreeRTOS delaytimeout

-
#### Projectdelivery

1. Time limits for the projectdelivery
2. Device functionalities that remained unused like the switch, NeoPixel, LCDDisplay

# References

1. &quot;Pulse Oximetry – Carboxyhemoglobin&quot;. Available at:[https://stormanesthesia.com/anesthesia-](https://stormanesthesia.com/anesthesia-material/miscellaneous-articles/58-pulse-oximetry-carboxyhemoglobin)[material/miscellaneous-articles/58-pulse-oximetry-carboxyhemoglobin](https://stormanesthesia.com/anesthesia-material/miscellaneous-articles/58-pulse-oximetry-carboxyhemoglobin)
2. &quot;TLC5925 – Low-Power 16-Channel Constant-Current LED Sink Driver&quot;. Available at:[https://www.ti.com/lit/ds/symlink/tlc5925.pdf?ts=1624300191782&amp;ref\_url=https%253A%252F%25](https://www.ti.com/lit/ds/symlink/tlc5925.pdf?ts=1624300191782&amp;ref_url=https%253A%252F%252Fwww.google.com%252F)2Fwww.google.com%252F

1. &quot;PSoC® 63 Microcontrollers: Arm® Cortex®-M4/M0+&quot;. Available at:[https://www.cypress.com/products/psoc-63-microcontrollers-arm-cortex-m4m0](https://www.cypress.com/products/psoc-63-microcontrollers-arm-cortex-m4m0)

1. &quot;Photoplethysmography (PPG)&quot;. Available at:[https://www.news-](https://www.news-medical.net/health/Photoplethysmography-(PPG).aspx)[medical.net/health/Photoplethysmography-(PPG).aspx](https://www.news-medical.net/health/Photoplethysmography-(PPG).aspx)

1. &quot;Photoplethysmography – (IR Heart Rate Monitor)&quot;. Available at:[https://www.instructables.com/Photoplethysmography-IR-Heart-Rate-Monitor/](https://www.instructables.com/Photoplethysmography-IR-Heart-Rate-Monitor/)
2. &quot;Heart rate/ SpO2 using PPG – MATLAB code&quot;. Available at:[https://nl.mathworks.com/matlabcentral/fileexchange/53364-heart-rate-spo2-using-ppg](https://nl.mathworks.com/matlabcentral/fileexchange/53364-heart-rate-spo2-using-ppg)
3. &quot;UART: A Hardware Communication Protocol Understanding UniversalAsynchronous

Receiver/Transmitter&quot;. Available at: [https://www.analog.com/en/analog-dialogue/articles/uart-a-](https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html)[hardware-communication-protocol.html](https://www.analog.com/en/analog-dialogue/articles/uart-a-hardware-communication-protocol.html)

1. &quot;PPGEDUKITSENSOR–ApplicationNote–ETRODepartment,FacultyofEngineering,VUB&quot;.
2. &quot;Malekian Reza, 2015, Body Sensor Network for Mobile Health Monitoring, a Diagnosisand

Anticipating System&quot;. Available at: [https://www.researchgate.net/figure/Mathematical-model-of-a-](https://www.researchgate.net/figure/Mathematical-model-of-a-pure-PPG-signal_fig11_282404009)[pure-PPG-signal\_fig11\_282404009](https://www.researchgate.net/figure/Mathematical-model-of-a-pure-PPG-signal_fig11_282404009)

1. &quot;Relations between ac-dc components and optical path length in photoplethysmography&quot; Available at:[https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-](https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-16/issue-07/077012/Relations-between-ac-dc-components-and-optical-path-length-in/10.1117/1.3600769.full?SSO=1%23%3A~%3Atext%3DPhotoplethysmography%20(PPG)%20is%2Cthe%20ac%20waveform)[16/issue-07/077012/Relations-between-ac-dc-components-and-optical-path-length-](https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-16/issue-07/077012/Relations-between-ac-dc-components-and-optical-path-length-in/10.1117/1.3600769.full?SSO=1%23%3A~%3Atext%3DPhotoplethysmography%20(PPG)%20is%2Cthe%20ac%20waveform)[in/10.1117/1.3600769.full?SSO=1#:~:text=Photoplethysmography%20(PPG)%20is,the%20ac%20wav](https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-16/issue-07/077012/Relations-between-ac-dc-components-and-optical-path-length-in/10.1117/1.3600769.full?SSO=1%23%3A~%3Atext%3DPhotoplethysmography%20(PPG)%20is%2Cthe%20ac%20waveform)[eform](https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-16/issue-07/077012/Relations-between-ac-dc-components-and-optical-path-length-in/10.1117/1.3600769.full?SSO=1%23%3A~%3Atext%3DPhotoplethysmography%20(PPG)%20is%2Cthe%20ac%20waveform)

1. &quot;Monitoring of Heart Rate from Photoplethysmographic Signals Using a Samsung Galaxy Note8 in Underwater Environments&quot; Available at:https://[www.ncbi.nlm.nih.gov/pmc/articles/PMC6651860/#:~:text=Heart%20rate%20is%20calculate](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC6651860/#%3A~%3Atext%3DHeart%20rate%20is%20calculate)d,in%20the%20dry%20environment.

1. &quot;Robust peak detection algorithm (using z-scores)&quot; Available at:[https://stackoverflow.com/questions/22583391/peak-signal-detection-in-realtime-timeseries-](https://stackoverflow.com/questions/22583391/peak-signal-detection-in-realtime-timeseries-data/54507140#54507140)data/54507140#54507140

1. &quot;The mountaineer&#39;s method for peak detection in photoplethysmographic signals&quot; Availableat:

[https://revistas.udea.edu.co/index.php/ingenieria/article/view/332019](https://revistas.udea.edu.co/index.php/ingenieria/article/view/332019)

1. &quot;Protocentral\_MAX30205&quot; Available at:[https://github.com/Protocentral/Protocentral\_MAX30205/blob/master/src/Protocentral\_MAX3020](https://github.com/Protocentral/Protocentral_MAX30205/blob/master/src/Protocentral_MAX30205.h)5.h
2. &quot;Basics of I2C Communication&quot; Availableat:

https://[www.circuitbasics.com/basics-of-the-i2c-communication-](http://www.circuitbasics.com/basics-of-the-i2c-communication-) protocol/#:~:text=I2C%20is%20a%20serial%20communication,always%20controlled%20by%20the%2 0master.