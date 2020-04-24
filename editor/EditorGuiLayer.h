#ifndef EDITOR_GUI_LAYER_H
#define EDITOR_GUI_LAYER_H

#include "../GuiLayer.h"

class EditorGuiLayer : public GuiLayer
{
public:
  EditorGuiLayer(const Window::Param& param,
                 Window* window,
                 glm::mat4& view,
                 glm::mat4& projection);
  ~EditorGuiLayer();
  void init() override;
  void update() override;
  void render() override;

private:
  Window::Param _wParam;
  glm::mat4& _view;
  glm::mat4& _projection;
};

#endif
