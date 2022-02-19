#include "ImGuiBackend.h"

#include "GlfwWindow.h"

namespace fig {
void ImGuiBackend::init(Window* rawWindow) {
  const char* glsl_version = "#version 450";
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  // TODO downcast
  ImGui_ImplGlfw_InitForOpenGL(dynamic_cast<GlfwWindow*>(rawWindow)->_window,
                               true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::GetStyle().WindowRounding = 0.0f;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void ImGuiBackend::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiBackend::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiBackend::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
}  // namespace fig
