#pragma once

#include "Camera.h"
#include "Light.h"

namespace fig {
struct Color {
  float r;
  float g;
  float b;
  float alfa;
};

class Window;
class WindowBackground {
 public:
  WindowBackground() = default;
  WindowBackground(const WindowBackground&) = delete;
  WindowBackground(WindowBackground&&) = delete;
  WindowBackground& operator=(const WindowBackground&) = delete;
  WindowBackground& operator=(WindowBackground&&) = delete;
  ~WindowBackground() = default;

  virtual void render() = 0;
  virtual void bind(Window* window) = 0;
};
}  // namespace fig
