#include "../EventManager.h"
#include "events/EditorKeyReleaseEvent.h"
#include "events/EditorMouseMoveEvent.h"
#include "events/EditorMousePressEvent.h"
#include "events/EditorMouseReleaseEvent.h"

namespace fig
{
class EditorMousePressEvent;

class EditorEventManager : public EventManager
{
  friend class ::EditorMousePressEvent;
  friend class ::EditorMouseReleaseEvent;
  friend class ::EditorMouseMoveEvent;
  friend class ::EditorKeyReleaseEvent;

public:
  EditorEventManager(Window* window);
  EditorEventManager(const EditorEventManager&) = delete;
  EditorEventManager(EditorEventManager&&) = delete;
  EditorEventManager& operator=(const EditorEventManager&) = delete;
  EditorEventManager& operator=(EditorEventManager&&) = delete;

  void tick() override;

private:
  Window* _window;
};
}
