#ifndef COLOR_BACKGROUND_H
#define COLOR_BACKGROUND_H

#include "WindowBackground.h"

namespace fig
{
class ColorBackground : public WindowBackground
{
public:
  ColorBackground(const Color& color);

  void render() override;
  void bind(Window* window) override;

private:
  Color _color;
};
}

#endif
