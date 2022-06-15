#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "flex_sensors/include/flex_sensor.hpp"
#include "flex_sensors/include/flex_sensors.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bluetooth/bluetooth/include/Bluetooth.hpp"
#include <sstream>

extern "C"
{ 
    void app_main(); 
}

void app_main()
{
    AdcReader adcReader((adc1_channel_t)ADC_CHANNEL_6);
    FlexSensor flexSensor(20500, 60000);
    Bluetooth bluetooth("ESP_32");

    while(1) {
        flexSensor.updateVoltage(adcReader.readVoltage());
        std::cout << "Resistance: " << flexSensor.resistance();
        std::cout << ", Angle: " << flexSensor.angle() << std::endl;
        std::ostringstream ss;
        ss << flexSensor.angle();
        bluetooth.send(ss.str(), FlexSensorId::MIDDLE);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }   
    
    /*bluetooth.send("thumb", FlexSensorId::THUMB);
    bluetooth.send("index", FlexSensorId::INDEX);
    bluetooth.send("middle", FlexSensorId::MIDDLE);
    bluetooth.send("ring", FlexSensorId::RING);
    bluetooth.send("pinky", FlexSensorId::PINKY);*/
}
