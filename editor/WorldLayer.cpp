#include "WorldLayer.h"
#include "../Light.h"
#include "../events/Event.h"
#include "EditorEventManager.h"
#include "globals.h"

namespace fig
{
WorldLayer::WorldLayer(Window* w,
                       Camera* c,
                       glm::mat4& view,
                       glm::mat4& projection,
                       std::unique_ptr<WindowBackground> background) :
  _window(w),
  _camera(c), _view(view), _projection(projection),
  _background(std::move(background))
{
}

void WorldLayer::init()
{
  _eventManager = std::make_shared<EditorEventManager>(_window);
  _background->bind(_window);
}

void WorldLayer::update()
{
  FG_APP_INFO("WorldLayer update");
}

void WorldLayer::render()
{
  FG_APP_INFO("WorldLayer render");
  _camera->updateSpeed();
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());

  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.0f);
  _background->render();
  _eventManager->tick();
}

std::function<void(std::unique_ptr<Event> event)> WorldLayer::onEvent()
{
  return [this](std::unique_ptr<Event> event) {
    event->process(_camera, _eventManager.get());
  };
}
}
