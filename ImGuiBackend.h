#ifndef IMGUI_BACKEND_H
#define IMGUI_BACKEND_H

#include "GuiBackend.h"

namespace fig
{
class ImGuiBackend : public GuiBackend
{
public:
  void init(Window* rawWindow) override;
  void newFrame() override;
  void render() override;
  void shutdown() override;
};
}

#endif
