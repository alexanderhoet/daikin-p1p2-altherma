#include "daikin_p1p2_altherma.h"
#include "esphome/core/log.h"

#include <p1p2_serial.h>

namespace esphome {
namespace daikin_p1p2_altherma {

static const char *const TAG = "daikin_p1p2_altherma";

static void message_print(P1P2_Message_t *message);

void DaikinP1P2Altherma::setup() {
  ESP_LOGI(TAG, "Setting up Daikin P1P2");

  if (!rx_pin_ || !tx_pin_ || !rst_pin_) {
    ESP_LOGE(TAG, "Pins not configured");
    return;
  }

  //const int rx = rx_pin_->get_pin();
  //const int tx = tx_pin_->get_pin();
  //const int rst = rst_pin_->get_pin();

  const int rx = 34;
  const int tx = 33;
  const int rst = 32;

  ESP_LOGI(TAG, "P1P2 pins RX=%d TX=%d RST=%d", rx, tx, rst);

  if (p1p2_serial_init(rx, tx, rst) != P1P2_OK) {
    ESP_LOGE(TAG, "P1P2 serial init failed");
    return;
  }

  ESP_LOGI(TAG, "P1P2 RX initialized");
}

void DaikinP1P2Altherma::loop() {
  P1P2_Message_t rxmessage = {0};

  if (p1p2_message_read(&rxmessage, 1) == P1P2_OK) {
    message_print(&rxmessage);
  }
  ESP_LOGI(TAG, "Loop is running");
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
