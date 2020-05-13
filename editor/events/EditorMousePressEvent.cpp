#include "EditorMousePressEvent.h"
#include "../EditorEventManager.h"

EditorMousePressEvent::EditorMousePressEvent(QMouseEvent* event) :
  MousePressEvent(event->button()), _qtEvent(event)
{
}

void EditorMousePressEvent::process(fig::Camera* camera,
                                    fig::EventManager* eventManager)
{
  switch (_qtEvent->button()) {
    case Qt::LeftButton:
      handleMousePressedLeft();
      break;
    case Qt::MiddleButton:
      handleMousePressedMiddle(eventManager);
      break;
    case Qt::RightButton:
      handleMousePressedRight();
      break;
    default:
      return;
  }
}

void EditorMousePressEvent::handleMousePressedLeft()
{
}

void EditorMousePressEvent::handleMousePressedRight()
{
}

void EditorMousePressEvent::handleMousePressedMiddle(
  fig::EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<fig::EditorEventManager*>(eventManager);

  m->pressMouse(fig::MouseButton::MIDDLE);
  m->_middleLastPressed = glm::vec2(_qtEvent->x(), _qtEvent->y());
  std::cout << "variable" << std::endl;
}
