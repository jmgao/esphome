#include "template_binary_sensor.h"

namespace esphome {
namespace template_ {

void TemplateBinarySensor::loop() {
  if (!this->f_.has_value())
    return;

  auto s = (*this->f_)();
  if (s.has_value()) {
    this->publish_state(*s);
  }
}
void TemplateBinarySensor::dump_config() { LOG_BINARY_SENSOR("", "Template Binary Sensor", this); }

}  // namespace template_
}  // namespace esphome