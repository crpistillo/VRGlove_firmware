#include "mpu.hpp"
#include <iostream>

const gpio_num_t MPU::SDA(GPIO_NUM_21);
const gpio_num_t MPU::SCL(GPIO_NUM_22);
const uint32_t MPU::CLOCK_SPEED(400000);
const uint8_t MPU::kDMPOutputRate(100);
const mpud::dmp_feature_t MPU::kDMPFeatures(
        mpud::DMP_FEATURE_LP_6X_QUAT | mpud::DMP_FEATURE_GYRO_CAL | mpud::DMP_FEATURE_TAP |
        mpud::DMP_FEATURE_SEND_CAL_GYRO | mpud::DMP_FEATURE_SEND_RAW_ACCEL);

MPU::MPU() {
    initializeMPU();
}

void MPU::initializeMPU() {
    i2c0.begin(SDA, SCL, CLOCK_SPEED);

    mpu_.setBus(i2c0);  
    mpu_.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);

    testConnection();

    ESP_ERROR_CHECK(mpu_.initialize());
    ESP_ERROR_CHECK(mpu_.loadDMPFirmware());
    ESP_ERROR_CHECK(mpu_.setDMPFeatures(MPU::kDMPFeatures));
    ESP_ERROR_CHECK(mpu_.setDMPOutputRate(MPU::kDMPOutputRate));
    ESP_ERROR_CHECK(mpu_.enableDMP());
}

void MPU::testConnection() {
    while (esp_err_t err = mpu_.testConnection()) {
        std::cout << "Failed to connect to the MPU, error=" << err << std::endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    std::cout << "MPU connection successful!" << std::endl;
}

void MPU::read() {
    mpu_.readDMPPacket(&quatRaw_, &gyroRaw_, &accelRaw_);
    mpud::axes_q16_t eulerRaw = mpud::quaternionToEuler(quatRaw_);
    quat_ = mpud::q30_to_float(quatRaw_);
    euler_ = mpud::q16_to_float(eulerRaw);
    accelG_ = mpud::accelGravity(accelRaw_, mpud::ACCEL_FS_2G);
    gyroDPS_ = mpud::gyroDegPerSec(gyroRaw_, mpud::GYRO_FS_2000DPS);
}

mpud::float_axes_t MPU::getOrientation() {
    return euler_;
};

void MPU::printOrientation() {
    printf("orientation: [%+6.2f %+6.2f %+6.2f ] (º) \n", euler_.x, euler_.y, euler_.z);
}
