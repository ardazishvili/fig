#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <glm/glm.hpp>

#include "Window.h"

enum class MouseButton { LEFT, MIDDLE, RIGHT };

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
  bool shiftPressed() const;
  bool mousePressed(MouseButton b) const;

  // TODO make non-public
  bool _shiftPressed{ false };
  bool _middleButtonPressed{ false };
  glm::vec2 _middleLastPressed{ 0.0f, 0.0f };

protected:
};

#endif
