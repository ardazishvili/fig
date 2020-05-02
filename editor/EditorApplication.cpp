#include "EditorApplication.h"
#include "../ColorBackground.h"
#include "../QtWindow.h"
#include "WorldLayer.h"
#include "events/EditorEventFabric.h"

namespace fig
{
template<typename T>
EditorApplication<T>::EditorApplication(std::unique_ptr<QApplication> app) :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f)),
  _qapp(std::move(app))
{
  _eventFabric = std::make_unique<EditorEventFabric>();
  this->_window = std::make_unique<QtWindow>(
    Window::Param{ 1500, 1000 },
    _eventFabric.get(),
    [this] {
      this->init();
    },
    [this] {
      tick();
    });

  Color c = { 194.0f / 255, 194.0f / 255, 214.0f / 255, 1 };
  auto worldLayer =
    std::make_unique<WorldLayer>(this->_window.get(),
                                 &_camera,
                                 _view,
                                 _projection,
                                 std::make_unique<ColorBackground>(c));
  this->_window->setOnEvent(worldLayer->onEvent());
  this->addLayer(std::move(worldLayer));
}

template<typename T>
void EditorApplication<T>::run()
{
  _qapp->exec();
}

template<typename T>
void EditorApplication<T>::tick()
{
  this->update();
  this->render();
}

template class EditorApplication<SpdBackend>;
}
