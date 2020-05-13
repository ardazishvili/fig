#ifndef EDITOR_KEY_PRESS_EVENT_H
#define EDITOR_KEY_PRESS_EVENT_H

#include "../../events/Event.h"
#include <QKeyEvent>

class EditorKeyPressEvent : public fig::KeyboardPressEvent
{
public:
  EditorKeyPressEvent(QKeyEvent* event);
  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

private:
  QKeyEvent* _event;
};

#endif
