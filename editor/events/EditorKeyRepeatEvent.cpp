#include "EditorKeyRepeatEvent.h"

EditorKeyRepeatEvent::EditorKeyRepeatEvent(QKeyEvent* event) :
  fig::KeyboardRepeatEvent(event->key(), event->modifiers()), _event(event)
{
}

void EditorKeyRepeatEvent::process(fig::Camera* camera,
                                   fig::EventManager* eventManager)
{
  switch (_event->key()) {
    case Qt::Key_Left:
      camera->rotateLeft();
      break;
    case Qt::Key_Right:
      camera->rotateRight();
      break;
    case Qt::Key_W:
      camera->moveForward();
      break;
    case Qt::Key_S:
      camera->moveBackward();
      break;
    case Qt::Key_A:
      camera->moveLeft();
      break;
    case Qt::Key_D:
      camera->moveRight();
      break;
  }
}
