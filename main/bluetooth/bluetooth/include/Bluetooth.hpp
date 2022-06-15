#pragma once

#include "driver/gpio.h"
#include "flex_sensors.hpp"
#include <iostream>
#include "BLEDevice.hpp"
#include "BLEServer.hpp"
#include "BLEUtils.hpp"
#include <map>

class Bluetooth {
public:
    static const std::string kServiceUUID;
    static const std::map<FlexSensorId, std::string> kCharacteristicsUUIDs;

    Bluetooth(std::string deviceName);
    void send(std::string value, FlexSensorId flexSensorId);

private:
    std::string deviceName_;
    std::map<FlexSensorId, BLECharacteristic*> BLECharacteristics_;

    void initializeCharacteristics(BLEService* service);
    void start();
};