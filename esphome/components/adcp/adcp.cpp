#include "adcp.h"
#include "esphome/core/log.h"

namespace esphome {
namespace adcp {

static const char *TAG = "ADCP";

void ADCPComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Setting up ADCP...");
}

void ADCPSensor::update() {
  digitalWrite(this->get_power_pin(), HIGH);
  delay(this->get_delay());
  publish_state(this->parent_->get_adc()->get_state()); // find_adc(this->get_adc_id())
  digitalWrite(this->get_power_pin(), LOW);
}

}  // namespace ADCPLEX
}  // namespace esphome
