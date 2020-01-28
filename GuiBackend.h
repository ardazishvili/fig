#ifndef GUI_BACKEND_H
#define GUI_BACKEND_H

#include "Window.h"

class GuiBackend
{
public:
  virtual void init(Window* rawWindow) = 0;
  virtual void newFrame() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
};

#endif
