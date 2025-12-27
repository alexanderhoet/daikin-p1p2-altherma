#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace daikin_p1p2_altherma {

class DaikinP1P2Altherma : public Component {
 public:
  void setup() override;
  void loop() override;
};

}
}
