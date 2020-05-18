#include "WorldLayer.h"
#include "../Light.h"
#include "../events/Event.h"
#include "EditorEventManager.h"
#include "globals.h"
#include <memory>

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
  /* FG_APP_INFO("initiating world layer"); */
  assert(_camera);
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());

  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.f);
  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), *_camera, _view, _projection);

  _colorShader = std::make_unique<PhongShader>(
    _light.get(),
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color.vs",
    "/home/roman/repos/colony/shaders/fragment_color.fs");
  _eventManager = std::make_shared<EditorEventManager>(_window);
  _background->bind(_window);
}

void WorldLayer::update()
{
  /* FG_APP_INFO("updating world layer"); */
  _camera->updateSpeed();
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());

  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.0f);
  _eventManager->tick();
}

void WorldLayer::render()
{
  /* FG_APP_INFO("rendering world layer"); */
  _background->render();
  /* _sphere->render(); */
  for (auto& obj : _objects) {
    obj->render();
  }
}

std::function<void(std::unique_ptr<Event> event)> WorldLayer::onEvent()
{
  return [this](std::unique_ptr<Event> event) {
    event->process(_camera, _eventManager.get());
  };
}

void WorldLayer::addSphere(glm::vec3 pos, float radius, int divisions)
{
  _objects.emplace_back(
    std::make_unique<Sphere>(*_colorShader, pos, radius, divisions));
}
}
