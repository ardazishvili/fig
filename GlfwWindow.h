#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <functional>
#include <memory>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Window.h"
#include "events/Event.h"

class EventFabric;
class GlfwWindow : public Window
{
public:
  GlfwWindow(glm::mat4& view,
             glm::mat4& projection,
             EventFabric* eventFabric,
             const Window::Param& param);
  ~GlfwWindow() override;
  void setOnEvent(std::function<void(std::unique_ptr<Event> event)> onEvent);

  void update();
  void show();
  float width() const override;
  float height() const override;
  void getCursorPos(double* xpos, double* ypos) const;

private:
  glm::mat4& _view;
  glm::mat4& _projection;

  static EventFabric* _eventFabric;
  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
};

#endif
