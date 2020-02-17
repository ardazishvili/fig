#include "../EventManager.h"

class EditorEventManager : public EventManager
{
public:
  EditorEventManager(Window* window);
  EditorEventManager(const EditorEventManager&) = delete;
  EditorEventManager(EditorEventManager&&) = delete;
  EditorEventManager& operator=(const EditorEventManager&) = delete;
  EditorEventManager& operator=(EditorEventManager&&) = delete;

  void tick() override;

private:
  Window* _window;

  friend class EditorKeyReleaseEvent;
};
