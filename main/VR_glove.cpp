#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C"
{ 
    void app_main(); 
}

void app_main()
{
    std::cout << "VR Glove" << std::endl;
    AdcReader adcReader((adc1_channel_t)ADC_CHANNEL_6);
    while(1) {
        adcReader.readVoltage();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }   
}
