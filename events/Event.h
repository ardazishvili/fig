#pragma once

#include "Core.h"
#include "Window.h"
#include "events/KeyHandler.h"

namespace fig {
class EventManager;
class Camera;
class Event {
 public:
  Event() = default;
  Event(const Event&) = delete;
  Event(Event&&) = delete;
  Event& operator=(const Event&) = delete;
  Event& operator=(Event&&) = delete;
  ~Event() = default;

  virtual void process(Camera* camera, EventManager* eventManager) = 0;
};

class KeyboardEvent : public Event {
 public:
  KeyboardEvent(KeyboardKey key, int scancode, int mods)
      : _key(key), _scancode(), _mods(mods) {}

  KeyboardEvent(KeyboardKey key, int mods)
      : _key(key), _scancode(), _mods(mods) {}

 protected:
  KeyboardKey _key;
  int _scancode;
  int _mods;
  KeyHandler _handler;
};

class KeyboardPressEvent : public KeyboardEvent {
 public:
  KeyboardPressEvent(KeyboardKey key, int scancode, int mods)
      : KeyboardEvent(key, scancode, mods){FG_CORE_TRACE("key pressed")}

        KeyboardPressEvent(KeyboardKey key, int mods)
      : KeyboardEvent(key, mods) {
    FG_CORE_TRACE("key pressed")
  }
};

class KeyboardReleaseEvent : public KeyboardEvent {
 public:
  KeyboardReleaseEvent(KeyboardKey key, int scancode, int mods)
      : KeyboardEvent(key, scancode, mods){FG_CORE_TRACE("key released")}

        KeyboardReleaseEvent(KeyboardKey key, int mods)
      : KeyboardEvent(key, mods) {
    FG_CORE_TRACE("key released")
  }
  void process(Camera* camera, EventManager* eventManager) override {
    _handler.process(_key, eventManager);
  }
};

class KeyboardRepeatEvent : public KeyboardEvent {
 public:
  KeyboardRepeatEvent(KeyboardKey key, int scancode, int mods)
      : KeyboardEvent(key, scancode,
                      mods){FG_CORE_TRACE("key repeatedly pressed")}

        KeyboardRepeatEvent(KeyboardKey key, int mods)
      : KeyboardEvent(key, mods) {
    FG_CORE_TRACE("key repeatedly pressed")
  }
};

class MouseEvent : public Event {};

class MouseButtonEvent : public MouseEvent {
 public:
  MouseButtonEvent(int button) : _button(button) {}

 protected:
  int _button;
};

class MousePressEvent : public MouseButtonEvent {
 public:
  MousePressEvent(int button) : MouseButtonEvent(button) {
    /* FG_CORE_TRACE("mouse pressed") */
  }
};

class MouseReleaseEvent : public MouseButtonEvent {
 public:
  MouseReleaseEvent(int button) : MouseButtonEvent(button) {
    /* FG_CORE_TRACE("mouse released") */
  }
};

class MouseMoveEvent : public MouseEvent {
 public:
  MouseMoveEvent(double xpos, double ypos) : _xpos(xpos), _ypos(ypos) {
    /* FG_CORE_TRACE("mouse moved") */
  }

 protected:
  double _xpos;
  double _ypos;
};

class MouseScrollEvent : public MouseEvent {
 public:
  MouseScrollEvent(double xoffset, double yoffset)
      : _xoffset(xoffset), _yoffset(yoffset) {
    /* FG_CORE_TRACE("mouse scrolled") */
  }

 protected:
  double _xoffset;
  double _yoffset;
};
}  // namespace fig
