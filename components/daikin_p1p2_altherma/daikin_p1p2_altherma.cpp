#include "daikin_p1p2_altherma.h"
#include "esphome/core/log.h"

namespace esphome {
namespace daikin_p1p2_altherma {

static const char *const TAG = "daikin_p1p2_altherma";

void DaikinP1P2Altherma::setup() {
  ESP_LOGI(TAG, "Daikin P1P2 Altherma component setup()");
}

void DaikinP1P2Altherma::loop() {
  // For now just prove loop() is alive (debug level to avoid spam)
  ESP_LOGD(TAG, "Daikin P1P2 loop()");
}

}
}
