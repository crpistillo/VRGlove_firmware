#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "flex_sensors/include/flex_sensor.hpp"
#include "flex_sensors/include/flex_sensors.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bluetooth/bluetooth/include/Bluetooth.hpp"
#include "mpu/include/mpu.hpp"
#include "mpu/include/mpu_values.hpp"
#include <string>

extern "C"
{ 
    void app_main(); 
}

const uint32_t MIN_ANGLE_R = 20500;
const uint32_t MAX_ANGLE_R = 60000;

static constexpr gpio_num_t SDA = GPIO_NUM_21;
static constexpr gpio_num_t SCL = GPIO_NUM_22;
static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

void app_main()
{
    MPU mpu;
   
    AdcReader adcReader_thumb((adc1_channel_t)ADC_CHANNEL_0);
    FlexSensor flexSensor_thumb(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_index((adc1_channel_t)ADC_CHANNEL_6);
    FlexSensor flexSensor_index(MIN_ANGLE_R, MAX_ANGLE_R);
    
    AdcReader adcReader_middle((adc1_channel_t)ADC_CHANNEL_7);
    FlexSensor flexSensor_middle(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_ring((adc1_channel_t)ADC_CHANNEL_4);
    FlexSensor flexSensor_ring(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_pinky((adc1_channel_t)ADC_CHANNEL_5);
    FlexSensor flexSensor_pinky(MIN_ANGLE_R, MAX_ANGLE_R);

    Bluetooth bluetooth("ESP_32");

    while(1) {
        mpu.read();

        /*printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", mpu.getAccelG().x, mpu.getAccelG().y, mpu.getAccelG().z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", mpu.getGyroDPS()[0], mpu.getGyroDPS()[1], mpu.getGyroDPS()[2]);*/
        
        flexSensor_thumb.updateVoltage(adcReader_thumb.readVoltage());
        flexSensor_index.updateVoltage(adcReader_index.readVoltage());
        flexSensor_middle.updateVoltage(adcReader_middle.readVoltage());
        flexSensor_ring.updateVoltage(adcReader_ring.readVoltage());
        flexSensor_pinky.updateVoltage(adcReader_pinky.readVoltage());

        /*std::cout << "THUMB: " << flexSensor_thumb.angle() << std::endl;
        std::cout << "INDEX: " << flexSensor_index.angle() << std::endl;
        std::cout << "MIDDLE: " << flexSensor_middle.angle() << std::endl;
        std::cout << "RING: " << flexSensor_ring.angle() << std::endl;
        std::cout << "PINKY: " << flexSensor_pinky.angle() << std::endl;*/

        bluetooth.send(std::to_string(flexSensor_thumb.angle()), FlexSensorId::THUMB);
        bluetooth.send(std::to_string(flexSensor_index.angle()), FlexSensorId::INDEX);
        bluetooth.send(std::to_string(flexSensor_middle.angle()), FlexSensorId::MIDDLE);
        bluetooth.send(std::to_string(flexSensor_ring.angle()), FlexSensorId::RING);
        bluetooth.send(std::to_string(flexSensor_pinky.angle()), FlexSensorId::PINKY);

        bluetooth.send(std::to_string(mpu.getAccelG().x), MPUValueType::ACCEL_X);
        bluetooth.send(std::to_string(mpu.getAccelG().y), MPUValueType::ACCEL_Y);
        bluetooth.send(std::to_string(mpu.getAccelG().z), MPUValueType::ACCEL_Z);

        bluetooth.send(std::to_string(mpu.getGyroDPS()[0]), MPUValueType::GYRO_X);
        bluetooth.send(std::to_string(mpu.getGyroDPS()[1]), MPUValueType::GYRO_Y);
        bluetooth.send(std::to_string(mpu.getGyroDPS()[2]), MPUValueType::GYRO_Z);

        vTaskDelay(pdMS_TO_TICKS(10));
    }   
}
