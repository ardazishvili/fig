#include "WorldLayer.h"
#include "../Light.h"
#include "../events/Event.h"
#include "EditorEventManager.h"

WorldLayer::WorldLayer(Window* w,
                       Camera* c,
                       glm::mat4& view,
                       glm::mat4& projection) :
  _window(w),
  _camera(c), _view(view), _projection(projection)
{
}

void WorldLayer::init()
{
  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), *_camera, _view, _projection);
  _lampShader = std::make_unique<PhongShader>(
    _light.get(),
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_light.vs",
    "/home/roman/repos/colony/shaders/fragment_light.fs");
  _light->setShader(_lampShader.get());
  _skyboxShader = std::make_unique<SkyboxShader>(
    _light.get(),
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  _skybox = std::make_unique<Skybox>(*_skyboxShader);
  _eventManager = std::make_shared<EditorEventManager>(_window);
}

void WorldLayer::update()
{
}

void WorldLayer::render()
{
  _camera->updateSpeed();
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());
  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.0f);
  _eventManager->tick();
  _skybox.get()->render();
}

std::function<void(std::unique_ptr<Event> event)> WorldLayer::onEvent()
{
  return [this](std::unique_ptr<Event> event) {
    event->process(_camera, _eventManager.get());
  };
}
