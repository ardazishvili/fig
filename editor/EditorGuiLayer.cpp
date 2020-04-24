#include "../imgui/imgui.h"

#include "../ImGuiBackend.h"
#include "EditorGuiLayer.h"

EditorGuiLayer::EditorGuiLayer(const Window::Param& param,
                               Window* window,
                               glm::mat4& view,
                               glm::mat4& projection) :
  GuiLayer(window, std::make_unique<ImGuiBackend>()),
  _wParam(param), _view(view), _projection(projection)
{
}

EditorGuiLayer::~EditorGuiLayer()
{
  _guiBack->shutdown();
}

void EditorGuiLayer::init()
{
  _guiBack->init(_window);
}

void EditorGuiLayer::update()
{
  _guiBack->newFrame();
  ImGui::Begin("light");
  static float x = 1.2;
  static float y = 0.0;
  static float z = 90.0;
  ImGui::SetWindowPos(ImVec2(0, 110));
  ImGui::SetWindowSize(ImVec2(500, 100));
  ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
  ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
  ImGui::SliderFloat("light z", &z, -100.0f, 100.0f);
  ImGui::End();
}

void EditorGuiLayer::render()
{
  _guiBack->render();
}
