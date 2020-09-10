#include "adcplex.h"
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

void ADCPLEXSensor::update() {
  digitalWrite(this->get_power_pin(), HIGH);
  delay(this->get_delay());
  publish_state(this->parent_->adc_->get_state());
  digitalWrite(this->get_power_pin(), LOW);
}

}  // namespace ADCPLEX
}  // namespace esphome
