#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EditorEventManager.h"
#include "EditorKeyReleaseEvent.h"

namespace fig
{
EditorKeyReleaseEvent::EditorKeyReleaseEvent(int key, int scancode, int mods) :
  KeyboardReleaseEvent(key, scancode, mods)
{
}

void EditorKeyReleaseEvent::process(Camera* camera, EventManager* eventManager)
{
  // TODO downcast
  auto em = dynamic_cast<EditorEventManager*>(eventManager);

  if (_key == GLFW_KEY_ESCAPE) {
    em->_window->close();
  }
}
}
