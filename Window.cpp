#include "Window.h"

namespace fig {
Window::Window(const Param& param) : _param(param) {}

void Window::setBackgroundColor(const Color& color) { _color = color; }

}  // namespace fig
