#include "EditorMouseMoveEvent.h"
#include "../../Camera.h"
#include "../EditorEventManager.h"

EditorMouseMoveEvent::EditorMouseMoveEvent(double xpos, double ypos) :
  MouseMoveEvent(xpos, ypos)
{
}

void EditorMouseMoveEvent::process(fig::Camera* camera,
                                   fig::EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<fig::EditorEventManager*>(eventManager);
  if (m->isMousePressed(fig::MouseButton::MIDDLE)) {
    auto deltaX = _xpos - m->_middleLastPressed.x;
    auto deltaY = _ypos - m->_middleLastPressed.y;

    if (deltaY < 0) {
      camera->rotateUp();
    } else if (deltaY > 0) {
      camera->rotateDown();
    }
    if (deltaX > 0) {
      camera->rotateLeft();
    } else if (deltaX < 0) {
      camera->rotateRight();
    }
    m->_middleLastPressed = glm::vec2(_xpos, _ypos);
  }
}
