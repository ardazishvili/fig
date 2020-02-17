#ifndef EVENT_FABRIC_H
#define EVENT_FABRIC_H

#include <memory>

#include "Event.h"

class EventFabric
{
public:
  EventFabric() = default;
  EventFabric(const EventFabric&) = delete;
  EventFabric(EventFabric&&) = delete;
  EventFabric& operator=(const EventFabric&) = delete;
  EventFabric& operator=(EventFabric&&) = delete;
  ~EventFabric() = default;

  virtual std::unique_ptr<Event> getKeyPressEvent(int key,
                                                  int scancode,
                                                  int mods) = 0;
  virtual std::unique_ptr<Event> getKeyReleaseEvent(int key,
                                                    int scancode,
                                                    int mods) = 0;
  virtual std::unique_ptr<Event> getKeyRepeatEvent(int key,
                                                   int scancode,
                                                   int mods) = 0;
  virtual std::unique_ptr<Event> getMouseScrollEvent(double xoffset,
                                                     double yoffset) = 0;
  virtual std::unique_ptr<Event> getMouseMoveEvent(double xpos,
                                                   double ypos) = 0;
  virtual std::unique_ptr<Event> getMousePressedEvent(int button,
                                                      int action,
                                                      int mods) = 0;
  virtual std::unique_ptr<Event> getMouseReleasedEvent(int button,
                                                       int action,
                                                       int mods) = 0;
};

#endif
