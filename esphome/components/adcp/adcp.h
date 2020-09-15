#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace adcp {

class ADCPSensor;
  
class ADCPComponent : public Component {
public:
    void register_sensor(ADCPSensor *obj) { this->sensors_.push_back(obj); }
    void update() override;
    void dump_config() override;

    void set_adc(sensor::ADCSensor *adc) { this->adc_ = adc; }
    sensor::ADCSensor get_adc() { return this->adc_; }

    float get_setup_priority() const override { return setup_priority::DATA; }

protected:
    std::vector<ADCPSensor *> sensors_;
    sensor::ADCSensor *adc_;
};

class ADCPSensor : public sensor::Sensor {
public:
    ADCPSensor(ADCPComponent *parent) : parent_(parent) {}
    void set_power_pin(uint8_t power_pin) { this->power_pin = power_pin; }
    void set_adc_id(std::string adc) { this->adc_ = adc; }
    void set_delay(int delay) { this->delay = delay; }

    uint8_t get_power_pin() const { return this->power_pin; }
    std::string get_adc_id() const { return this->adc_; }
    uint8_t get_delay() const { return this->delay; }

protected:
    ADCPComponent *parent_;
    uint8_t power_pin;
    std::string adc_;
    int delay;
};
}  // namespace adcp
}  // namespace esphome
