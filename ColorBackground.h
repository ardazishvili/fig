#pragma once

#include "WindowBackground.h"

namespace fig {
class ColorBackground : public WindowBackground {
 public:
  ColorBackground(const Color& color);

  void render() override;
  void bind(Window* window) override;

 private:
  Color _color;
};
}  // namespace fig
