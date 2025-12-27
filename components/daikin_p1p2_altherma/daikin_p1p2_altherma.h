#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace daikin_p1p2_altherma {

class DaikinP1P2Altherma : public Component {
 public:
  void setup() override;
  void loop() override;

  float get_setup_priority() const override {
    return setup_priority::LATE;
  }

  void set_rx_pin(InternalGPIOPin *pin) { rx_pin_ = pin; }
  void set_tx_pin(InternalGPIOPin *pin) { tx_pin_ = pin; }
  void set_rst_pin(InternalGPIOPin *pin) { rst_pin_ = pin; }

 protected:
  InternalGPIOPin *rx_pin_{nullptr};
  InternalGPIOPin *tx_pin_{nullptr};
  InternalGPIOPin *rst_pin_{nullptr};
};

}
}
