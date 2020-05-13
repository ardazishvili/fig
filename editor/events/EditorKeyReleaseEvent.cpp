#include "EditorKeyReleaseEvent.h"
#include "EditorEventManager.h"
#include <qnamespace.h>

EditorKeyReleaseEvent::EditorKeyReleaseEvent(QKeyEvent* event) :
  KeyboardReleaseEvent(event->key(), event->modifiers()), _event(event)
{
}

void EditorKeyReleaseEvent::process(fig::Camera* camera,
                                    fig::EventManager* eventManager)
{
  // TODO downcast
  auto em = dynamic_cast<fig::EditorEventManager*>(eventManager);

  switch (_event->key()) {
    case Qt::Key_Escape:
      em->_window->close();
      break;
    case Qt::Key_Shift:
      em->releaseKey(fig::KeyButton::LEFT_SHIFT);
      std::cout << "shift is released" << std::endl;
      break;
    default:
      break;
  }
}
