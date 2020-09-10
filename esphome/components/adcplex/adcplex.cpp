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

float ADCPLEXComponent::request_measurement(ADCPLEXSensor *sensor) {
  digitalWrite(sensor->get_power_pin(), HIGH);
  delay(sensor->get_delay());
  sensor->publish_state(this->adc_.get_state());
  digitalWrite(sensor->get_power_pin(), LOW);
}

}  // namespace ADCPLEX
}  // namespace esphome
