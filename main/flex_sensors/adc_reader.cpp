#include "include/adc_reader.hpp"

const uint32_t AdcReader::kDefaultVRef(1100);
const int AdcReader::kNoOfSamples(64);
const adc_bits_width_t AdcReader::kCaptureWidth(ADC_WIDTH_BIT_12);
const adc_unit_t AdcReader::kAdcUnit(ADC_UNIT_1);
adc1_channel_t AdcReader::channel_((adc1_channel_t)ADC_CHANNEL_6);
esp_adc_cal_characteristics_t* AdcReader::adcCharacteristics_ = NULL;

// With ADC_ATTEN_DB_11, the measurable input voltage range is: 150 mV ~ 2450 mV
const adc_atten_t AdcReader::kAttenuation(ADC_ATTEN_DB_11);

AdcReader::AdcReader(adc1_channel_t channel) {
    channel_ = channel;
    configureAdc();
    characterizeAdc();
}

void AdcReader::configureAdc() const {
    adc1_config_width(AdcReader::kCaptureWidth);
    adc1_config_channel_atten(channel_, AdcReader::kAttenuation);
}

void AdcReader::characterizeAdc() const {
    adcCharacteristics_ = (esp_adc_cal_characteristics_t*) 
                           calloc(1, sizeof(esp_adc_cal_characteristics_t));
                           
    esp_adc_cal_characterize(AdcReader::kAdcUnit, 
                             AdcReader::kAttenuation, 
                             AdcReader::kCaptureWidth, 
                             AdcReader::kDefaultVRef, 
                             adcCharacteristics_);
}

uint32_t AdcReader::readVoltage() const {
    uint32_t adc_reading = 0;
    //Multisampling
    for (int i = 0; i < AdcReader::kNoOfSamples; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t)channel_);
    }
    adc_reading /= AdcReader::kNoOfSamples;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adcCharacteristics_);
    printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
    return voltage;
}