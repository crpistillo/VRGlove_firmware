#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "flex_sensors/include/flex_sensor.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bluetooth/bluetooth/include/Bluetooth.hpp"
#include <string>
#include "esp_log.h"
#include "esp_err.h"
#include <math.h>

#include "mpu/include/mpu.hpp"

extern "C"
{ 
    void app_main(); 
}

void app_main()
{
    MPU mpu;
   
    AdcReader adcReader_thumb((adc1_channel_t)ADC_CHANNEL_0);
    FlexSensor flexSensor_thumb(27000, 67000);

    AdcReader adcReader_index((adc1_channel_t)ADC_CHANNEL_6);
    FlexSensor flexSensor_index(18600, 62000);
    
    AdcReader adcReader_middle((adc1_channel_t)ADC_CHANNEL_7);
    FlexSensor flexSensor_middle(22400, 61000);

    AdcReader adcReader_ring((adc1_channel_t)ADC_CHANNEL_4);
    FlexSensor flexSensor_ring(26000, 66000);

    AdcReader adcReader_pinky((adc1_channel_t)ADC_CHANNEL_5);
    FlexSensor flexSensor_pinky(115000, 180000);

    Bluetooth bluetooth("ESP_32");

    while(1) {        
        flexSensor_thumb.updateVoltage(adcReader_thumb.readVoltage());
        flexSensor_index.updateVoltage(adcReader_index.readVoltage());
        flexSensor_middle.updateVoltage(adcReader_middle.readVoltage());
        flexSensor_ring.updateVoltage(adcReader_ring.readVoltage());
        flexSensor_pinky.updateVoltage(adcReader_pinky.readVoltage());

        std::cout << "Thumb: " << flexSensor_thumb.angle() << std::endl;
        std::cout << "Index: " << flexSensor_index.angle() << std::endl;
        std::cout << "Middle: " << flexSensor_middle.angle() << std::endl;
        std::cout << "Ring: " << flexSensor_ring.angle() << std::endl;
        std::cout << "Pinky: " << flexSensor_pinky.angle() << std::endl;

        mpu.read();
        mpu.printOrientation();

        bluetooth.send(std::to_string((int)flexSensor_thumb.angle()) + " " +
                       std::to_string((int)flexSensor_index.angle()) + " " + 
                       std::to_string((int)flexSensor_middle.angle()) + " " +
                       std::to_string((int)flexSensor_ring.angle()) + " " +
                       std::to_string((int)flexSensor_pinky.angle()) + " " +
                       std::to_string((int)mpu.getOrientation().x) + " " +
                       std::to_string((int)mpu.getOrientation().y) + " " + 
                       std::to_string((int)mpu.getOrientation().z));        
        
        vTaskDelay(pdMS_TO_TICKS(150));
    }   
}
