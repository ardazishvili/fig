#pragma once

#include "Window.h"

namespace fig {
class GuiBackend {
 public:
  virtual void init(Window* rawWindow) = 0;
  virtual void newFrame() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
};
}  // namespace fig
