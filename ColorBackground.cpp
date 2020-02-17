#include "ColorBackground.h"
#include "Window.h"

ColorBackground::ColorBackground(const Color& color) : _color(color)
{
}

void ColorBackground::render()
{
}

void ColorBackground::bind(Window* window)
{
  window->setBackgroundColor(_color);
}
