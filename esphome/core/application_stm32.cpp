#include "esphome/core/application.h"

#ifdef ARDUINO_ARCH_STM32

namespace esphome {

static const char *const TAG = "app_stm32";

void ICACHE_RAM_ATTR HOT Application::feed_wdt_arch_() {
    // STM32 has no watchdog
}

}  // namespace esphome
#endif
