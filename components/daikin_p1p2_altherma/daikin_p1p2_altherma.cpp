#include <esphome/core/log.h>

#include "daikin_p1p2_serial.h"
#include "daikin_p1p2_altherma.h"

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

  ESP_LOGI(TAG, "P1P2 pins RX=%d TX=%d RST=%d", rx_pin_->get_pin(), tx_pin_->get_pin(), rst_pin_->get_pin());

  if (p1p2_serial_init(rx_pin_->get_pin(), tx_pin_->get_pin(), rst_pin_->get_pin()) != P1P2_OK) {
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

  ESP_LOGI(TAG, "P1P2 pins RX=%d TX=%d RST=%d", rx_pin_->get_pin(), tx_pin_->get_pin(), rst_pin_->get_pin());

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
