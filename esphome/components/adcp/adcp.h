#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace adcp {

class ADCPSensor;  
class ADCPComponent : public Component {
  public:
    void register_sensor(ADCPSensor *obj) { this->sensors_.push_back(obj); }
    void dump_config() override;
    void update();

    void set_adc(sensor::Sensor *adc) { this->adc_ = adc; }
    sensor::Sensor *get_adc() const { return this->adc_; }
    float get_setup_priority() const override { return setup_priority::DATA; }

  protected:
    std::vector<ADCPSensor *> sensors_;
    sensor::Sensor *adc_;
};

class ADCPSensor : public sensor::Sensor {
  public:
    ADCPSensor(ADCPComponent *parent) : parent_(parent) {}
    void set_power_pin(int *power_pin) { this->power_pin = power_pin; }
    void set_delay(int *delay) { this->delay = delay; }

    int *get_power_pin() const { return this->power_pin; }
    int *get_delay() const { return this->delay; }

  protected:
    ADCPComponent *parent_;
    int *power_pin_;
    int *delay_;
};
}  // namespace adcp
}  // namespace esphome
