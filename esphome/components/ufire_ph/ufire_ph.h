#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ufire_ph {

static const uint8_t REGISTER_VERSION = 0;
static const uint8_t REGISTER_MV = 1;
static const uint8_t REGISTER_TEMP = 5;
static const uint8_t REGISTER_TASK = 39;

static const uint8_t COMMAND_MEASURE_TEMP = 40;
static const uint8_t COMMAND_MEASURE_MV = 80;

class UFirePH : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }
  void set_ph_sensor(sensor::Sensor *ph_sensor) { this->ph_sensor_ = ph_sensor; }

 protected:
  float measure_temperature_();

  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *ph_sensor_{nullptr};
};

}  // namespace ufire_ph
}  // namespace esphome
