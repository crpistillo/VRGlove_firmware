#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "flex_sensors/include/flex_sensor.hpp"
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
    FlexSensor flexSensor;
    while(1) {
        flexSensor.updateVoltage(adcReader.readVoltage());
        std::cout << "Resistance: " << flexSensor.resistance();
        std::cout << ", Angle: " << flexSensor.angle() << std::endl;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }   
}
