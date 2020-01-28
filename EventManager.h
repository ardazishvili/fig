#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <bitset>

#include <glm/glm.hpp>

#include "Window.h"

enum class MouseButton { LEFT, MIDDLE, RIGHT, _LAST };
enum class KeyButton { LEFT_SHIFT, _LAST };

class EventManager
{

public:
  EventManager() = default;
  EventManager(const EventManager&) = delete;
  EventManager(EventManager&&) = delete;
  EventManager& operator=(const EventManager&) = delete;
  EventManager& operator=(EventManager&&) = delete;
  virtual ~EventManager() = default;

  virtual void tick() = 0;

  static glm::vec3 unProject(Window* window, glm::mat4& view, glm::mat4& proj);
  void pressKey(KeyButton k);
  void pressMouse(MouseButton b);
  void releaseKey(KeyButton k);
  void releaseMouse(MouseButton b);
  bool isKeyPressed(KeyButton k) const;
  bool isMousePressed(MouseButton b) const;

protected:
  glm::vec2 _middleLastPressed{ 0.0f, 0.0f };
  std::bitset<static_cast<size_t>(KeyButton::_LAST)> _keyset;
  std::bitset<static_cast<size_t>(MouseButton::_LAST)> _mouseSet;
};

#endif
