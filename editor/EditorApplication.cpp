#include "EditorApplication.h"
#include "../GlfwWindow.h"
#include "EditorEventFabric.h"
#include "WorldLayer.h"

template<typename T>
EditorApplication<T>::EditorApplication() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _eventFabric = std::make_unique<EditorEventFabric>();
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;
  Window::Param param = { screenWidth, screenHeight };
  this->_window =
    std::make_unique<GlfwWindow>(_view, _projection, _eventFabric.get(), param);

  auto worldLayer = std::make_unique<WorldLayer>(
    this->_window.get(), &_camera, _view, _projection);
  worldLayer->init();
  this->_window->setOnEvent(worldLayer->onEvent());
  this->addLayer(std::move(worldLayer));
}

template<typename T>
void EditorApplication<T>::run()
{
  while (!this->_window->shouldClose()) {
    this->_window->update();

    this->update();
    this->render();
    this->_window->show();
  }
}

template class EditorApplication<SpdBackend>;
