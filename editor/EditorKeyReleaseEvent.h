#ifndef EDITOR_KEY_RELEASE_EVENT_H
#define EDITOR_KEY_RELEASE_EVENT_H

#include "../events/Event.h"

namespace fig
{
class EditorKeyReleaseEvent : public KeyboardReleaseEvent
{
public:
  EditorKeyReleaseEvent(int key, int scancode, int mods);
  void process(Camera* camera, EventManager* eventManager);
};
}

#endif
