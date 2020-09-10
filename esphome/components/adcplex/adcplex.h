#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
// #include "esphome.h"

namespace esphome {
namespace adcplex {
    
/// Internal holder class that is in instance of Sensor so that the hub can create individual sensors.
class ADCPLEXSensor : public sensor::ADCSensor {
    public:
        ADCPLEXSensor(ADCPLEXComponent *paren) : parent_(parent) {}
        void setup() override;
        void update() override;
        void set_power_pin(uint8_t power_pin) { this->power_pin = power_pin; }
        uint8_t get_power_pin() const { return power_pin; }
        void set_delay(int delay) { this->delay = delay; }
        uint8_t get_delay() const { return delay; }

    protected:
        ADCPLEXComponent *parent_;
        uint8_t power_pin;
        int delay;
};

class ADCPLEXComponent : public Component {
    public:
        void register_sensor(ADCPLEXSensor *obj) { this->sensors_.push_back(obj); }
        void dump_config() override;
        /// HARDWARE_LATE setup priority
        float get_setup_priority() const override { return setup_priority::DATA; }

    protected:
        std::vector<ADCPLEXSensor *> sensors_;
};

}  // namespace ADCPLEX
}  // namespace esphome