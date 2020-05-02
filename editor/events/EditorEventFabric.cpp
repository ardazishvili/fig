#include "EditorEventFabric.h"
#include "../Application.h"
#include "EditorKeyReleaseEvent.h"
#include "EditorMouseMoveEvent.h"
#include "EditorMousePressEvent.h"
#include "EditorMouseReleaseEvent.h"
#include "globals.h"

namespace fig
{
class StubEvent : public Event
{

  void process(Camera* camera, EventManager* eventManager) override
  {
    FG_APP_INFO("StubEvent output");
  }
};

std::unique_ptr<Event> EditorEventFabric::getKeyPressEvent(int key,
                                                           int scancode,
                                                           int mods)
{
  return std::make_unique<StubEvent>();
}

std::unique_ptr<Event> EditorEventFabric::getKeyReleaseEvent(int key,
                                                             int scancode,
                                                             int mods)
{
  return std::make_unique<EditorKeyReleaseEvent>(key, scancode, mods);
}

std::unique_ptr<Event> EditorEventFabric::getKeyRepeatEvent(int key,
                                                            int scancode,
                                                            int mods)
{
  return std::make_unique<StubEvent>();
}

std::unique_ptr<Event> EditorEventFabric::getMouseScrollEvent(double xoffset,
                                                              double yoffset)
{
  return std::make_unique<StubEvent>();
}

std::unique_ptr<Event> EditorEventFabric::getMouseMoveEvent(double xpos,
                                                            double ypos)
{
  return std::make_unique<EditorMouseMoveEvent>(xpos, ypos);
}

std::unique_ptr<Event> EditorEventFabric::getMousePressedEvent(int button,
                                                               int action,
                                                               int mods)
{
  return std::make_unique<StubEvent>();
}

std::unique_ptr<Event> EditorEventFabric::getMouseReleasedEvent(int button,
                                                                int action,
                                                                int mods)
{
  return std::make_unique<StubEvent>();
}

std::unique_ptr<Event> EditorEventFabric::getMousePressedEvent(
  QMouseEvent* event)
{
  return std::make_unique<EditorMousePressEvent>(event);
}

std::unique_ptr<Event> EditorEventFabric::getMouseReleasedEvent(
  QMouseEvent* event)
{
  return std::make_unique<EditorMouseReleaseEvent>(event);
}
}
