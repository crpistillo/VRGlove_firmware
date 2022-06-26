#pragma once

#include "driver/gpio.h"
#include "flex_sensors.hpp"
#include "mpu_values.hpp"
#include <iostream>
#include "BLEDevice.hpp"
#include "BLEServer.hpp"
#include "BLEUtils.hpp"
#include <map>

class Bluetooth {
public:
    static const std::string kFlexSensorServiceUUID;
    static const std::string kMpuServiceUUID;
    
    static const std::map<FlexSensorId, std::string> kFlexSensorCharacteristicsUUIDs;
    static const std::map<MPUValueType, std::string> kMPUCharacteristicsUUIDs;

    Bluetooth(std::string deviceName);
    void send(std::string value, FlexSensorId flexSensorId);
    void send(std::string value, MPUValueType mpuValueType);

private:
    std::string deviceName_;
    std::map<FlexSensorId, BLECharacteristic*> FlexSensorBLECharacteristics_;
    std::map<MPUValueType, BLECharacteristic*> MpuBLECharacteristics_;

    void initializeFlexSensorCharacteristics(BLEService* service);
    void initializeMpuCharacteristics(BLEService* service);
    void start();
};