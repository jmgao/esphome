#include "esphome/core/log.h"
#include "ufire_ph.h"

namespace esphome {
namespace ufire_ph {

static const char *TAG = "ufire_ph.sensor";

void UFirePH::setup() {
  uint8_t version;
  if (!this->read_byte(REGISTER_VERSION, &version) && version != 0xFF) {
    this->mark_failed();
    this->status_set_error();
    return;
  }
}

void UFirePH::update() {
  float temperature = this->measure_temperature_();
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temperature);

}

float UFirePH::measure_temperature_() {
  this->write_byte(REGISTER_TASK, COMMAND_MEASURE_TEMP);
  uint8_t temp[4];
  this->read_bytes(REGISTER_TEMP, temp, 4);
  float f;
  memcpy(&f, &temp, sizeof(f));
  return f;
}

void UFirePH::dump_config() {}

}  // namespace ufire_ph
}  // namespace esphome
