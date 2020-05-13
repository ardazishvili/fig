#ifndef EDITOR_KEY_RELEASE_EVENT_H
#define EDITOR_KEY_RELEASE_EVENT_H

#include "../events/Event.h"
#include <QKeyEvent>

class EditorKeyReleaseEvent : public fig::KeyboardReleaseEvent
{
public:
  EditorKeyReleaseEvent(QKeyEvent* event);
  void process(fig::Camera* camera, fig::EventManager* eventManager) override;

private:
  QKeyEvent* _event;
};

#endif
