#ifndef EVENT_H
#define EVENT_H

#include "../Core.h"
#include "../Window.h"

class EventManager;
class Camera;
class Event
{
public:
  Event() = default;
  Event(const Event&) = delete;
  Event(Event&&) = delete;
  Event& operator=(const Event&) = delete;
  Event& operator=(Event&&) = delete;
  ~Event() = default;

  virtual void process(Camera* camera, EventManager* eventManager) = 0;
};

class KeyboardEvent : public Event
{
public:
  KeyboardEvent(int key, int scancode, int mods) :
    _key(key), _scancode(), _mods(mods)
  {
  }

protected:
  int _key;
  int _scancode;
  int _mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
  KeyboardPressEvent(int key, int scancode, int mods) :
    KeyboardEvent(key, scancode, mods)
  {
    FG_CORE_TRACE("key pressed")
  }
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
  KeyboardReleaseEvent(int key, int scancode, int mods) :
    KeyboardEvent(key, scancode, mods)
  {
    FG_CORE_TRACE("key released")
  }
};

class KeyboardRepeatEvent : public KeyboardEvent
{
public:
  KeyboardRepeatEvent(int key, int scancode, int mods) :
    KeyboardEvent(key, scancode, mods)
  {
    FG_CORE_TRACE("key repeatedly pressed")
  }
};

class MouseEvent : public Event
{
};

class MouseButtonEvent : public MouseEvent
{
public:
  MouseButtonEvent(int button) : _button(button)
  {
  }

protected:
  int _button;
};

class MousePressEvent : public MouseButtonEvent
{
public:
  MousePressEvent(int button) : MouseButtonEvent(button)
  {
    FG_CORE_TRACE("mouse pressed")
  }
};

class MouseReleaseEvent : public MouseButtonEvent
{
public:
  MouseReleaseEvent(int button) : MouseButtonEvent(button)
  {
    FG_CORE_TRACE("mouse released")
  }
};

class MouseMoveEvent : public MouseEvent
{
public:
  MouseMoveEvent(double xpos, double ypos) : _xpos(xpos), _ypos(ypos)
  {
    FG_CORE_TRACE("mouse moved")
  }

protected:
  double _xpos;
  double _ypos;
};

class MouseScrollEvent : public MouseEvent
{
public:
  MouseScrollEvent(double xoffset, double yoffset) :
    _xoffset(xoffset), _yoffset(yoffset)
  {
    FG_CORE_TRACE("mouse scrolled")
  }

protected:
  double _xoffset;
  double _yoffset;
};

#endif
