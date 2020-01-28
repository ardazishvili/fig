#include <cstdio>

#include "events/ErrorEvent.h"
#include "events/Event.h"
#include "events/EventFabric.h"

#include "GlfwWindow.h"

std::function<void(std::unique_ptr<Event> event)> GlfwWindow::_onEvent =
  [](std::unique_ptr<Event> event) {
  };
EventFabric* GlfwWindow::_eventFabric = nullptr;

GlfwWindow::GlfwWindow(glm::mat4& view,
                       glm::mat4& projection,
                       EventFabric* eventFabric,
                       const Window::Param& param) :
  Window(param),
  _view(view), _projection(projection)
{
  _eventFabric = eventFabric;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  _window =
    glfwCreateWindow(_param.width, _param.height, "LearnOPenGl", NULL, NULL);

  if (_window == NULL) {
    glfwTerminate();
    throw "Application ctor failed: failed to create window";
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  auto err = glewInit();
  if (err) {
    throw "Application ctor failed: Failed to initialize OpenGL loader!";
  }

  glViewport(0, 0, _param.width, _param.height);

  glfwSetErrorCallback([](int, const char*) {
    _onEvent(std::make_unique<ErrorEvent>());
  });

  glfwSetFramebufferSizeCallback(_window,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });

  glfwSetCursorPosCallback(
    _window, [](GLFWwindow* window, double xpos, double ypos) {
      _onEvent(_eventFabric->getMouseMoveEvent(xpos, ypos));
    });

  glfwSetScrollCallback(
    _window, [](GLFWwindow* window, double xoffset, double yoffset) {
      _onEvent(_eventFabric->getMouseScrollEvent(xoffset, yoffset));
    });

  glfwSetMouseButtonCallback(
    _window, [](GLFWwindow* window, int button, int action, int mods) {
      switch (action) {
        case GLFW_PRESS:
          _onEvent(_eventFabric->getMousePressedEvent(button, action, mods));
          break;
        case GLFW_RELEASE:
          _onEvent(_eventFabric->getMouseReleasedEvent(button, action, mods));
          break;
      }
    });

  glfwSetKeyCallback(
    _window,
    [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      switch (action) {
        case GLFW_PRESS:
          _onEvent(_eventFabric->getKeyPressEvent(key, scancode, mods));
          break;
        case GLFW_RELEASE:
          _onEvent(_eventFabric->getKeyReleaseEvent(key, scancode, mods));
          break;
        case GLFW_REPEAT:
          _onEvent(_eventFabric->getKeyRepeatEvent(key, scancode, mods));
          break;
      }
    });

  glEnable(GL_DEPTH_TEST);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(_window);
  glfwTerminate();
}

float GlfwWindow::width() const
{
  return _param.width;
}

float GlfwWindow::height() const
{
  return _param.height;
}

void GlfwWindow::update()
{
  glfwPollEvents();

  int display_w, display_h;
  glfwGetFramebufferSize(_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void GlfwWindow::show()
{
  glfwSwapBuffers(_window);
}

void GlfwWindow::getCursorPos(double* xpos, double* ypos) const
{
  glfwGetCursorPos(_window, xpos, ypos);
}

void GlfwWindow::setOnEvent(
  std::function<void(std::unique_ptr<Event> event)> onEvent)
{
  _onEvent = onEvent;
}

bool GlfwWindow::shouldClose()
{
  return glfwWindowShouldClose(_window);
}

void GlfwWindow::close()
{
  glfwSetWindowShouldClose(_window, true);
}
