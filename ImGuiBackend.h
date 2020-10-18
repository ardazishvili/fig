#ifndef IMGUI_BACKEND_H
#define IMGUI_BACKEND_H

#include "GuiBackend.h"

#include "third/gui/imgui/imgui.h"
#include "third/gui/imgui/imgui_impl_glfw.h"
#include "third/gui/imgui/imgui_impl_opengl3.h"

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
