#include "flex_sensor.hpp"
#include <iostream>

const uint32_t FlexSensor::kSeriesResistance(23100);
const uint32_t FlexSensor::kSupplyVoltage(3300);

FlexSensor::FlexSensor(uint32_t r1, uint32_t r2) {
    r1_ = r1;
    r2_ = r2;
}

void FlexSensor::updateVoltage(uint32_t voltage) {
    voltage_ = voltage;
}

uint32_t FlexSensor::resistance() const {
    return FlexSensor::kSeriesResistance * FlexSensor::kSupplyVoltage / voltage_ - FlexSensor::kSeriesResistance;
}

float FlexSensor::angle() const {
    return 90.0 * ( ((float)resistance() - (float)r2_) / ((float)r2_ - (float)r1_) + 1);
}