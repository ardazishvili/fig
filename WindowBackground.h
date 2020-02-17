#ifndef WINDOW_BACKGROUND_H
#define WINDOW_BACKGROUND_H

#include "Camera.h"
#include "Light.h"

class Window;
class WindowBackground
{
public:
  /* WindowBackground(Light* light, */
  /*                  Camera* camera, */
  /*                  glm::mat4& view, */
  /*                  glm::mat4& projection); */
  WindowBackground() = default;
  WindowBackground(const WindowBackground&) = delete;
  WindowBackground(WindowBackground&&) = delete;
  WindowBackground& operator=(const WindowBackground&) = delete;
  WindowBackground& operator=(WindowBackground&&) = delete;
  ~WindowBackground() = default;

  virtual void render() = 0;
  virtual void bind(Window* window) = 0;

protected:
  /* Light* _light; */
  /* Camera* _camera; */
  /* glm::mat4& _view; */
  /* glm::mat4& _projection; */
};

#endif
