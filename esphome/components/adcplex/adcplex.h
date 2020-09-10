#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace adcplex {

class ADCPlexSensor;
  
class ADCPLEXComponent : public Component {
    public:
        void register_sensor(ADCPLEXSensor *obj) { this->sensors_.push_back(obj); }
        void dump_config() override;

        void set_adc(sensor::ADCSensor *adc) { this->adc_ = adc; }
        sensor::ADCSensor get_adc() { return this->adc_;}
        float get_setup_priority() const override { return setup_priority::DATA; }

    protected:
        std::vector<ADCPLEXSensor *> sensors_;
        sensor::ADCSensor *adc_;
};
  
  class ADCPLEXSensor : public sensor::Sensor {
    public:
        ADCPLEXSensor(ADCPLEXComponent *parent) : parent_(parent) {}
        void set_power_pin(uint8_t power_pin) { this->power_pin = power_pin; }
        void set_delay(int delay) { this->delay = delay; }

        uint8_t get_power_pin() const { return power_pin; }
        uint8_t get_delay() const { return delay; }

    protected:
        ADCPLEXComponent *parent_;
        uint8_t power_pin;
        int delay;
};

}  // namespace ADCPLEX
}  // namespace esphome
