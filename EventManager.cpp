#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "EventManager.h"

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

bool EventManager::shiftPressed() const
{
  return _shiftPressed;
}

bool EventManager::mousePressed(MouseButton b) const
{
  switch (b) {
    case MouseButton::MIDDLE:
      return _middleButtonPressed;
  }
}
