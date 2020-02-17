#ifndef EDITOR_EVENT_FABRIC_H
#define EDITOR_EVENT_FABRIC_H

#include "../events/EventFabric.h"

class EditorEventFabric : public EventFabric
{
public:
  std::unique_ptr<Event> getKeyPressEvent(int key,
                                          int scancode,
                                          int mods) override;
  std::unique_ptr<Event> getKeyReleaseEvent(int key,
                                            int scancode,
                                            int mods) override;
  std::unique_ptr<Event> getKeyRepeatEvent(int key,
                                           int scancode,
                                           int mods) override;
  std::unique_ptr<Event> getMouseScrollEvent(double xoffset,
                                             double yoffset) override;
  std::unique_ptr<Event> getMouseMoveEvent(double xpos, double ypos) override;
  std::unique_ptr<Event> getMousePressedEvent(int button,
                                              int action,
                                              int mods) override;
  std::unique_ptr<Event> getMouseReleasedEvent(int button,
                                               int action,
                                               int mods) override;
};

#endif
