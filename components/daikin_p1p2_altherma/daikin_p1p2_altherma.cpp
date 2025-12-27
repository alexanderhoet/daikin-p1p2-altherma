#include "daikin_p1p2_altherma.h"
#include "esphome/core/log.h"

#include <p1p2_serial.h>

namespace esphome {
namespace daikin_p1p2_altherma {

static const char *const TAG = "daikin_p1p2_altherma";

// Forward declaration
static void message_print(P1P2_Message_t *message);

void DaikinP1P2Altherma::setup() {
  ESP_LOGI(TAG, "Initializing P1P2 RX engine");

  // Replace with your GPIO pins
  const int rx_pin = 21;
  const int tx_pin = 22;
  const int rst_pin = 23;

  if (p1p2_serial_init(rx_pin, tx_pin, rst_pin) != P1P2_OK) {
    ESP_LOGE(TAG, "Failed to initialize P1P2 serial, deinitializing");
    p1p2_serial_deinit();
    return;
  }

  ESP_LOGI(TAG, "P1P2 RX engine initialized");
}

void DaikinP1P2Altherma::loop() {
  P1P2_Message_t rxmessage = {0};

  if (p1p2_message_read(&rxmessage, 1) == P1P2_OK) {
    message_print(&rxmessage);
  }
}

static void message_print(P1P2_Message_t *message) {
  char buffer[128] = {0};
  int offset = 0;

  offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                     "%02x %02x %02x: ", message->direction, message->deviceid, message->messageid);

  for (uint8_t i = 0; i < message->datasize && offset < sizeof(buffer) - 3; i++) {
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%02x ", message->data[i]);
  }

  ESP_LOGD(TAG, "%s", buffer);
}

}
}
