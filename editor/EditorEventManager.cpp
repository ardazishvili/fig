#include "EditorEventManager.h"
#include "../Application.h"
#include "globals.h"

namespace fig
{
EditorEventManager::EditorEventManager(Window* window) : _window(window)
{
}

void EditorEventManager::tick()
{
  FG_APP_INFO("EditorEventManager tick")
}
}
