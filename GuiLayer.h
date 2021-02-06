#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include "GuiBackend.h"
#include "Layer.h"
#include "Window.h"

namespace fig
{
class GuiLayer : public Layer
{
public:
  GuiLayer(Window* window, std::unique_ptr<GuiBackend> guiBack) : _window(window), _guiBack(std::move(guiBack))
  {
  }

protected:
  Window* _window;
  std::unique_ptr<GuiBackend> _guiBack;
};
}

#endif
