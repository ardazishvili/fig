#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

class Window
{
public:
  struct Param
  {
    int width;
    int height;
  };

  Window(const Param& param);
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  virtual ~Window() = default;

  virtual float width() const = 0;
  virtual float height() const = 0;
  virtual void getCursorPos(double* xpos, double* ypos) const = 0;

  // TODO make non-public
  GLFWwindow* _window;

protected:
  Param _param;
};

#endif
