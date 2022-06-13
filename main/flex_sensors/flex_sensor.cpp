#include "include/flex_sensor.hpp"

const uint32_t FlexSensor::kSeriesResistance(23100);
const uint32_t FlexSensor::kSupplyVoltage(3300);

FlexSensor::FlexSensor() {

}

void FlexSensor::updateVoltage(uint32_t voltage) {
    voltage_ = voltage;
}

uint32_t FlexSensor::resistance() const {
    return FlexSensor::kSeriesResistance * FlexSensor::kSupplyVoltage / voltage_ - FlexSensor::kSeriesResistance;
}

uint32_t FlexSensor::angle() const {
    return 3.18 * resistance() / 1000 - 64.5;
}