#include "Window.h"

Window::Window(const Param& param) : _param(param)
{
}

void Window::setBackgroundColor(const Color& color)
{
  _color = color;
}
