#include "EditorKeyPressEvent.h"
#include "EditorEventManager.h"

EditorKeyPressEvent::EditorKeyPressEvent(QKeyEvent* event) :
  fig::KeyboardPressEvent(event->key(), event->modifiers()), _event(event)
{
}

void EditorKeyPressEvent::process(fig::Camera* camera,
                                  fig::EventManager* eventManager)
{
  switch (_event->modifiers()) {
    case Qt::ShiftModifier:
      eventManager->pressKey(fig::KeyButton::LEFT_SHIFT);
      break;
    default:
      return;
  }
}
