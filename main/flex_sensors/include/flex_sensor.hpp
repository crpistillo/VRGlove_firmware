#pragma once

#include "driver/gpio.h"

class FlexSensor {
public:
    // Value of the resistor in series with the flex sensor, in Ohms
    static const uint32_t kSeriesResistance;

    // Value of the Vcc supply voltage, in mV
    static const uint32_t kSupplyVoltage;

    FlexSensor();

    void updateVoltage(uint32_t voltage);
    uint32_t resistance() const;
    uint32_t angle() const;

private:
    uint32_t voltage_;
};