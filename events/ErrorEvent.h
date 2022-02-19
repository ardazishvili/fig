#pragma once

#include <iostream>

#include "events/Event.h"

namespace fig {
class ErrorEvent : public Event {
 public:
  void process(Camera* camera, EventManager* eventManager) override {
    std::cout << "ErrorEvent test output" << std::endl;
  }
};
}  // namespace fig
