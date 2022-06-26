#include "mpu.hpp"
#include <iostream>

const gpio_num_t MPU::SDA(GPIO_NUM_21);
const gpio_num_t MPU::SCL(GPIO_NUM_22);
const uint32_t MPU::CLOCK_SPEED(400000);

MPU::MPU() {
    initializeMPU();
}

void MPU::initializeMPU() {
    i2c0.begin(SDA, SCL, CLOCK_SPEED);

    mpu_.setBus(i2c0);  
    mpu_.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);

    testConnection();

    ESP_ERROR_CHECK(mpu_.initialize());  

}

void MPU::testConnection() {
    while (esp_err_t err = mpu_.testConnection()) {
        std::cout << "Failed to connect to the MPU, error=" << err << std::endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    std::cout << "MPU connection successful!" << std::endl;
}

void MPU::setupConfigurations() {
    //ESP_ERROR_CHECK(MPU.setSampleRate(50));  // set sample rate to 50 Hz
    ESP_ERROR_CHECK(mpu_.setGyroFullScale(mpud::GYRO_FS_500DPS));
    // ESP_ERROR_CHECK(MPU.setAccelFullScale(mpud::ACCEL_FS_4G));
}

void MPU::read() {
    mpu_.motion(&accelRaw_, &gyroRaw_);
    accelG_ = mpud::accelGravity(accelRaw_, mpud::ACCEL_FS_4G);
    gyroDPS_ = mpud::gyroDegPerSec(gyroRaw_, mpud::GYRO_FS_500DPS);
}

mpud::float_axes_t MPU::getAccelG() {
    return accelG_;
};

mpud::float_axes_t MPU::getGyroDPS() {
    return gyroDPS_;
};