#include "adc_plexer.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ADCPLEX {

static const char *TAG = "ADCPLEX";

void ADCPLEXComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Setting up ADCPLEX...");

  for (auto *sensor : this->sensors_) {
    LOG_SENSOR("  ", "Sensor", sensor);
  }
}

void ADCPLEXSensor::setup() {
  GPIOPin(this->power_pin, OUTPUT).setup();
  // ADCSensor::set_pin(analog_pin); //(Pins::analog_pin('A0'))
  ADCSensor::setup();
};

void ADCPLEXSensor::update() {
    digitalWrite(power_pin, HIGH);
    delay(this->delay);
    ADCSensor::update();
    digitalWrite(power_pin, LOW);
};

}  // namespace ADCPLEX
}  // namespace esphome