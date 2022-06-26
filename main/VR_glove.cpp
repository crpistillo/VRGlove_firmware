#include <iostream>
#include "flex_sensors/include/adc_reader.hpp"
#include "flex_sensors/include/flex_sensor.hpp"
#include "flex_sensors/include/flex_sensors.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bluetooth/bluetooth/include/Bluetooth.hpp"
#include "mpu/include/mpu.hpp"
#include "mpu/include/mpu_values.hpp"
#include <sstream>

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
   
    /*AdcReader adcReader_thumb((adc1_channel_t)ADC_CHANNEL_0);
    FlexSensor flexSensor_thumb(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_index((adc1_channel_t)ADC_CHANNEL_6);
    FlexSensor flexSensor_index(MIN_ANGLE_R, MAX_ANGLE_R);
    
    AdcReader adcReader_middle((adc1_channel_t)ADC_CHANNEL_7);
    FlexSensor flexSensor_middle(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_ring((adc1_channel_t)ADC_CHANNEL_4);
    FlexSensor flexSensor_ring(MIN_ANGLE_R, MAX_ANGLE_R);

    AdcReader adcReader_pinky((adc1_channel_t)ADC_CHANNEL_5);
    FlexSensor flexSensor_pinky(MIN_ANGLE_R, MAX_ANGLE_R);*/

    Bluetooth bluetooth("ESP_32");

    while(1) {

        mpu.read();

        printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", mpu.getAccelG().x, mpu.getAccelG().y, mpu.getAccelG().z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", mpu.getGyroDPS()[0], mpu.getGyroDPS()[1], mpu.getGyroDPS()[2]);

        
        /*
        flexSensor_thumb.updateVoltage(adcReader_thumb.readVoltage());
        flexSensor_index.updateVoltage(adcReader_index.readVoltage());
        flexSensor_middle.updateVoltage(adcReader_middle.readVoltage());
        flexSensor_ring.updateVoltage(adcReader_ring.readVoltage());
        flexSensor_pinky.updateVoltage(adcReader_pinky.readVoltage());

        std::cout << "THUMB: " << flexSensor_thumb.angle() << std::endl;
        std::cout << "INDEX: " << flexSensor_index.angle() << std::endl;
        std::cout << "MIDDLE: " << flexSensor_middle.angle() << std::endl;
        std::cout << "RING: " << flexSensor_ring.angle() << std::endl;
        std::cout << "PINKY: " << flexSensor_pinky.angle() << std::endl;


        std::ostringstream thumb_angle;
        thumb_angle << flexSensor_thumb.angle();

        std::ostringstream index_angle;
        index_angle << flexSensor_index.angle();

        std::ostringstream middle_angle;
        middle_angle << flexSensor_middle.angle();

        std::ostringstream ring_angle;
        ring_angle << flexSensor_ring.angle();

        std::ostringstream pinky_angle;
        pinky_angle << flexSensor_pinky.angle();

        bluetooth.send(thumb_angle.str(), FlexSensorId::THUMB);
        bluetooth.send(index_angle.str(), FlexSensorId::INDEX);
        bluetooth.send(middle_angle.str(), FlexSensorId::MIDDLE);
        bluetooth.send(ring_angle.str(), FlexSensorId::RING);
        bluetooth.send(pinky_angle.str(), FlexSensorId::PINKY);*/

        std::ostringstream accel_x;
        accel_x << mpu.getAccelG().x;

        std::ostringstream accel_y;
        accel_y << mpu.getAccelG().y;

        std::ostringstream accel_z;
        accel_z << mpu.getAccelG().z;

        std::ostringstream gyro_x;
        gyro_x << mpu.getGyroDPS()[0];

        std::ostringstream gyro_y;
        gyro_y << mpu.getGyroDPS()[1];

        std::ostringstream gyro_z;
        gyro_z << mpu.getGyroDPS()[2];

        bluetooth.send(accel_x.str(), MPUValueType::ACCEL_X);
        bluetooth.send(accel_y.str(), MPUValueType::ACCEL_Y);
        bluetooth.send(accel_z.str(), MPUValueType::ACCEL_Z);

        bluetooth.send(gyro_x.str(), MPUValueType::GYRO_X);
        bluetooth.send(gyro_y.str(), MPUValueType::GYRO_Y);
        bluetooth.send(gyro_z.str(), MPUValueType::GYRO_Z);

        vTaskDelay(pdMS_TO_TICKS(25));
    }   
}
