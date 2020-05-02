#ifndef EDITOR_MOUSE_RELEASE_EVENT_H
#define EDITOR_MOUSE_RELEASE_EVENT_H

#include <QMouseEvent>

#include "../../events/Event.h"

class EditorMouseReleaseEvent : public fig::MouseReleaseEvent
{
public:
  EditorMouseReleaseEvent(QMouseEvent* event);
  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

private:
  void handleMouseReleasedMiddle(fig::EventManager* eventManager);
  void handleMouseReleasedLeft(fig::EventManager* eventManager);
  QMouseEvent* _qtEvent;
};

#endif
