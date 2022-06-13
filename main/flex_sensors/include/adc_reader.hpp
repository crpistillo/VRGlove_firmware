#pragma once

#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

class AdcReader {
public:
    // Default Vref value of the ADC in [ms]
    static const uint32_t kDefaultVRef; 
    
    // Number of samples to take for the measurement of a voltage value
    static const int kNoOfSamples;

    // ADC resolution in bits
    static const adc_bits_width_t kCaptureWidth;

    // ADC attenuation parameter. Determines the range of the ADC
    static const adc_atten_t kAttenuation;

    // ADC unit in use (SAR ADC 1 or SAR ADC 2)
    static const adc_unit_t kAdcUnit;

    AdcReader(adc1_channel_t channel);

    void readVoltage() const;

private:
    // ADC pin channel
    static adc1_channel_t channel_; 

    // Structure storing characteristics of an ADC
    static esp_adc_cal_characteristics_t* adcCharacteristics_;

    void configureAdc() const;
    void characterizeAdc() const;
};