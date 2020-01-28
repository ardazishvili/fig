#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Window.h"

class EventFabric;
class GlfwWindow : public Window
{
public:
  GlfwWindow(glm::mat4& view,
             glm::mat4& projection,
             EventFabric* eventFabric,
             const Window::Param& param);
  ~GlfwWindow() override;
  void setOnEvent(
    std::function<void(std::unique_ptr<Event> event)> onEvent) override;
  void update() override;
  void show() override;
  float width() const override;
  float height() const override;
  void getCursorPos(double* xpos, double* ypos) const;
  bool shouldClose() override;
  void close() override;

private:
  glm::mat4& _view;
  glm::mat4& _projection;

  static EventFabric* _eventFabric;
  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
  GLFWwindow* _window;

  // for ImGui instantiation we might need raw GLFWwindow*
  friend class ImGuiBackend;
};

#endif
