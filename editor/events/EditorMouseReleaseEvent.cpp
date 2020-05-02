#include "EditorMouseReleaseEvent.h"
#include "../EditorEventManager.h"

EditorMouseReleaseEvent::EditorMouseReleaseEvent(QMouseEvent* event) :
  MouseReleaseEvent(event->button()), _qtEvent(event)
{
}

void EditorMouseReleaseEvent::process(fig::Camera* camera,
                                      fig::EventManager* eventManager)
{
  switch (_qtEvent->button()) {
    case Qt::LeftButton:
      handleMouseReleasedLeft(eventManager);
      break;
    case Qt::MiddleButton:
      handleMouseReleasedMiddle(eventManager);
      break;
    default:
      return;
  }
}

void EditorMouseReleaseEvent::handleMouseReleasedMiddle(
  fig::EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<fig::EditorEventManager*>(eventManager);
  m->releaseMouse(fig::MouseButton::MIDDLE);
}

void EditorMouseReleaseEvent::handleMouseReleasedLeft(
  fig::EventManager* eventManager)
{
}
