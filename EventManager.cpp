#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "EventManager.h"

namespace fig
{
glm::vec3 EventManager::unProject(Window* window,
                                  glm::mat4& view,
                                  glm::mat4& proj)
{
  GLfloat depth;

  double xpos, ypos;
  window->getCursorPos(&xpos, &ypos);
  glReadPixels(xpos,
               window->height() - ypos - 1,
               1,
               1,
               GL_DEPTH_COMPONENT,
               GL_FLOAT,
               &depth);

  glm::vec4 viewport = glm::vec4(0, 0, window->width(), window->height());
  glm::vec3 wincoord = glm::vec3(xpos, window->height() - ypos - 1, depth);
  glm::vec3 objcoord = glm::unProject(wincoord, view, proj, viewport);
  return objcoord;
}

bool EventManager::isKeyPressed(KeyButton k) const
{
  return _keyset.test(static_cast<size_t>(k));
}

bool EventManager::isMousePressed(MouseButton b) const
{
  return _mouseSet.test(static_cast<size_t>(b));
}

void EventManager::pressMouse(MouseButton b)
{
  _mouseSet.set(static_cast<size_t>(b));
}

void EventManager::pressKey(KeyButton k)
{
  _keyset.set(static_cast<size_t>(k));
}

void EventManager::releaseMouse(MouseButton b)
{
  _mouseSet.reset(static_cast<size_t>(b));
}

void EventManager::releaseKey(KeyButton k)
{
  _keyset.reset(static_cast<size_t>(k));
}
}
