#include "BLEUtils.h"
#include "BLEServer.h"
#include <esp_log.h>
#include <string>
#include <stdio.h>
#include "BLEDevice.h"
#include "sdkconfig.h"
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

/*#define SERVICE_UUID "f020f474-36c6-4f9f-9fa5-9736ee68a8f9"
#define FLEX_1_CHARACTERISTIC_UUID "ffd6cbd5-28fc-4fc7-8760-b74e93f1a73d"
#define FLEX_2_CHARACTERISTIC_UUID "eb359b0e-fd69-4cfb-ad0d-9b4d4c3f83db"
#define FLEX_3_CHARACTERISTIC_UUID "fe3dae39-d576-4cd7-86e2-05b374258f20"
#define FLEX_4_CHARACTERISTIC_UUID "c18ca83e-8cba-4a57-811e-a5de911ffd41"
#define FLEX_5_CHARACTERISTIC_UUID "b713cb87-4234-4ac8-af57-86cf72fdbc1a"

static void run() {
	BLEDevice::init("MYDEVICE");

	BLEServer* server = BLEDevice::createServer();

	BLEService* service = server->createService(BLEUUID(SERVICE_UUID));

	BLECharacteristic* flex1Characteristic = service->createCharacteristic(
		BLEUUID(FLEX_1_CHARACTERISTIC_UUID),
		BLECharacteristic::PROPERTY_READ
	);

	BLECharacteristic* flex2Characteristic = service->createCharacteristic(
		BLEUUID(FLEX_2_CHARACTERISTIC_UUID),
		BLECharacteristic::PROPERTY_READ
	);

	BLECharacteristic* flex3Characteristic = service->createCharacteristic(
		BLEUUID(FLEX_3_CHARACTERISTIC_UUID),
		BLECharacteristic::PROPERTY_READ
	);

	BLECharacteristic* flex4Characteristic = service->createCharacteristic(
		BLEUUID(FLEX_4_CHARACTERISTIC_UUID),
		BLECharacteristic::PROPERTY_READ
	);

	BLECharacteristic* flex5Characteristic = service->createCharacteristic(
		BLEUUID(FLEX_5_CHARACTERISTIC_UUID),
		BLECharacteristic::PROPERTY_READ
	);


	flex1Characteristic->setValue("Flexs 1");
	flex2Characteristic->setValue("Flexsss 2");
	flex3Characteristic->setValue("Flex 3");
	flex4Characteristic->setValue("Flex 4");
	flex5Characteristic->setValue("Flex 5");

	service->start();

	BLEAdvertising* advertising = server->getAdvertising();
	advertising->start();
}

extern "C"
{ 
    void app_main(); 
}

void app_main()
{
    run();
}*/