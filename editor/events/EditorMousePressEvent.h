#ifndef EDITOR_MOUSE_PRESS_EVENT_H
#define EDITOR_MOUSE_PRESS_EVENT_H

#include <QMouseEvent>

#include "../../events/Event.h"

class EditorMousePressEvent : public fig::MousePressEvent
{
public:
  EditorMousePressEvent(QMouseEvent* event);
  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

private:
  void handleMousePressedLeft();
  void handleMousePressedRight();
  void handleMousePressedMiddle(fig::EventManager* eventManager);
  QMouseEvent* _qtEvent;
};

#endif
