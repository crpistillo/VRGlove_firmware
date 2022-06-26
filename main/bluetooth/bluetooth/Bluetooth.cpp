#include "Bluetooth.hpp"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

const std::string Bluetooth::kFlexSensorServiceUUID("f020f474-36c6-4f9f-9fa5-9736ee68a8f9");
const std::string Bluetooth::kMpuServiceUUID("87c26127-73d1-4eb2-9531-f202d75bc7ba");

const std::map<FlexSensorId, std::string> Bluetooth::kFlexSensorCharacteristicsUUIDs = {
    {FlexSensorId::THUMB, "ffd6cbd5-28fc-4fc7-8760-b74e93f1a73d"}, 
    {FlexSensorId::INDEX, "eb359b0e-fd69-4cfb-ad0d-9b4d4c3f83db"}, 
    {FlexSensorId::MIDDLE, "fe3dae39-d576-4cd7-86e2-05b374258f20"}, 
    {FlexSensorId::RING, "c18ca83e-8cba-4a57-811e-a5de911ffd41"},
    {FlexSensorId::PINKY, "b713cb87-4234-4ac8-af57-86cf72fdbc1a"}
};

const std::map<MPUValueType, std::string> Bluetooth::kMPUCharacteristicsUUIDs = {
    {MPUValueType::ACCEL_X, "fd27e73f-e235-472a-9c4d-6cf85665a9af"}, 
    {MPUValueType::ACCEL_Y, "f81cb7d1-26bd-4954-b3ef-685ca4cc8f03"}, 
    {MPUValueType::ACCEL_Z, "9ac1c4cc-67a2-487d-ad04-ba7aeabf89b3"}, 
    {MPUValueType::GYRO_X, "b67f8d22-3085-4455-83cf-124c5054dd02"},
    {MPUValueType::GYRO_Y, "b6f85fdc-d3a9-4e85-bdac-d88cd6ce3c7d"},
    {MPUValueType::GYRO_Z, "796dc4e0-d89c-4bae-b4d9-475505a5d72d"}
};

Bluetooth::Bluetooth(std::string deviceName) {
    deviceName_ = deviceName;
    start();
}

void Bluetooth::start() {
    BLEDevice::init(deviceName_);
    
    BLEServer* server = BLEDevice::createServer();

    BLEService* flexSensorService = server->createService(BLEUUID(Bluetooth::kFlexSensorServiceUUID));
    initializeFlexSensorCharacteristics(flexSensorService);
    flexSensorService->start();

    BLEService* mpuService = server->createService(BLEUUID(Bluetooth::kMpuServiceUUID));
    initializeMpuCharacteristics(mpuService);
    mpuService->start();

    BLEAdvertising* advertising = server->getAdvertising();
	advertising->start();
}

void Bluetooth::initializeFlexSensorCharacteristics(BLEService* service) {
    for (auto i : kFlexSensorCharacteristicsUUIDs) {
        FlexSensorBLECharacteristics_.insert({i.first, 
                                   service-> createCharacteristic(
                                                BLEUUID(i.second),
                                                BLECharacteristic::PROPERTY_READ)});
    }
}

void Bluetooth::initializeMpuCharacteristics(BLEService* service) {
    for (auto i : kMPUCharacteristicsUUIDs) {
        MpuBLECharacteristics_.insert({i.first, 
                                   service-> createCharacteristic(
                                                BLEUUID(i.second),
                                                BLECharacteristic::PROPERTY_READ)});
    }
}

void Bluetooth::send(std::string value, FlexSensorId flexSensorId) {
    FlexSensorBLECharacteristics_[flexSensorId]->setValue(value);
}

void Bluetooth::send(std::string value, MPUValueType mpuValueType) {
    MpuBLECharacteristics_[mpuValueType]->setValue(value);
}