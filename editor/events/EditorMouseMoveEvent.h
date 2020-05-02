#ifndef EDITOR_MOUSE_MOVE_EVENT_H
#define EDITOR_MOUSE_MOVE_EVENT_H

#include "../../events/Event.h"

class EditorMouseMoveEvent : public fig::MouseMoveEvent
{
public:
  EditorMouseMoveEvent(double xpos, double ypos);
  void process(fig::Camera* camera, fig::EventManager* eventManager) override;
};

#endif
