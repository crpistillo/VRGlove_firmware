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

#include "MPU.hpp"
#include "MPUdmp.hpp"
#include "dmp/types.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"
#include "bluetooth/bluetooth/include/measurements.hpp"


extern "C"
{ 
    void app_main(); 
}

static const uint32_t MIN_ANGLE_R = 20500;
static const uint32_t MAX_ANGLE_R = 60000;

static constexpr gpio_num_t SDA = GPIO_NUM_21;
static constexpr gpio_num_t SCL = GPIO_NUM_22;
static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

static constexpr uint8_t kDMPOutputRate = 100; 

static const char* TAG = "APP";

static mpud::quat_q30_t quatRaw;
static mpud::raw_axes_t accelRaw, gyroRaw;

static MPUdmp_t mpu;
static mpud::quat_t quat;
static mpud::float_axes_t euler;
static mpud::float_axes_t accelG, gyroDPS;

static const mpud::dmp_feature_t kDMPFeatures =
        (mpud::DMP_FEATURE_LP_6X_QUAT | mpud::DMP_FEATURE_GYRO_CAL | mpud::DMP_FEATURE_TAP |
         mpud::DMP_FEATURE_SEND_CAL_GYRO | mpud::DMP_FEATURE_SEND_RAW_ACCEL);

void app_main()
{

    i2c0.begin(SDA, SCL, CLOCK_SPEED);
    mpu.setBus(i2c0);
    mpu.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);

    ESP_LOGI(TAG, "MPU connection successful!");
   
    ESP_ERROR_CHECK(mpu.initialize());
    ESP_ERROR_CHECK(mpu.loadDMPFirmware());
    ESP_ERROR_CHECK(mpu.setDMPFeatures(kDMPFeatures));
    ESP_ERROR_CHECK(mpu.setDMPOutputRate(kDMPOutputRate));

    ESP_ERROR_CHECK(mpu.enableDMP());

/*    MPU mpu;*/
   
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

        mpu.readDMPPacket(&quatRaw, &gyroRaw, &accelRaw);

        mpud::axes_q16_t eulerRaw = mpud::quaternionToEuler(quatRaw);
        quat                      = mpud::q30_to_float(quatRaw);
        euler                     = mpud::q16_to_float(eulerRaw);
        accelG                    = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_2G);
        gyroDPS                   = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_2000DPS);

        bluetooth.send(std::to_string((int)flexSensor_thumb.angle()) + " " +
                       std::to_string((int)flexSensor_index.angle()) + " " + 
                       std::to_string((int)flexSensor_middle.angle()) + " " +
                       std::to_string((int)flexSensor_ring.angle()) + " " +
                       std::to_string((int)flexSensor_pinky.angle()) + " " +
                       std::to_string((int)euler.x) + " " +
                       std::to_string((int)euler.y) + " " + 
                       std::to_string((int)euler.z));

        vTaskDelay(pdMS_TO_TICKS(150));
    }   
}
