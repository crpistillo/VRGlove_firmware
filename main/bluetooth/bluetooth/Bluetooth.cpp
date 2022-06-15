#include "Bluetooth.hpp"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
const std::string Bluetooth::kServiceUUID("f020f474-36c6-4f9f-9fa5-9736ee68a8f9");

const std::map<FlexSensorId, std::string> Bluetooth::kCharacteristicsUUIDs = {
    {FlexSensorId::THUMB, "ffd6cbd5-28fc-4fc7-8760-b74e93f1a73d"}, 
    {FlexSensorId::INDEX, "eb359b0e-fd69-4cfb-ad0d-9b4d4c3f83db"}, 
    {FlexSensorId::MIDDLE, "fe3dae39-d576-4cd7-86e2-05b374258f20"}, 
    {FlexSensorId::RING, "c18ca83e-8cba-4a57-811e-a5de911ffd41"},
    {FlexSensorId::PINKY, "b713cb87-4234-4ac8-af57-86cf72fdbc1a"}
};

Bluetooth::Bluetooth(std::string deviceName) {
    deviceName_ = deviceName;
    start();
}

void Bluetooth::start() {
    BLEDevice::init(deviceName_);
    
    BLEServer* server = BLEDevice::createServer();

    BLEService* service = server->createService(BLEUUID(Bluetooth::kServiceUUID));

    initializeCharacteristics(service);

    service->start();

    BLEAdvertising* advertising = server->getAdvertising();
	advertising->start();
}

void Bluetooth::initializeCharacteristics(BLEService* service) {
    for (auto i : kCharacteristicsUUIDs) {
        BLECharacteristics_.insert({i.first, 
                                   service-> createCharacteristic(
                                                BLEUUID(i.second),
                                                BLECharacteristic::PROPERTY_READ)});
    }
}

void Bluetooth::send(std::string value, FlexSensorId flexSensorId) {
    BLECharacteristics_[flexSensorId]->setValue(value);
}