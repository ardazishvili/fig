#include "EditorApplication.h"
#include "../ColorBackground.h"
/* #include "../GlfwWindow.h" */
#include "../QtWindow.h"
#include "EditorEventFabric.h"
/* #include "EditorGuiLayer.h" */
#include "WorldLayer.h"

#include "globals.h"
#include <memory>

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
  int screenWidth = 640;
  int screenHeight = 480;
  Window::Param param = { screenWidth, screenHeight };
  this->_window = std::make_unique<QtWindow>(param);
  this->_window->init();

  Color c = { 194.0f / 255, 194.0f / 255, 214.0f / 255, 1 };
  auto worldLayer =
    std::make_unique<WorldLayer>(this->_window.get(),
                                 &_camera,
                                 _view,
                                 _projection,
                                 std::make_unique<ColorBackground>(c));
  worldLayer->init();
  this->_window->setOnEvent(worldLayer->onEvent());
  this->addLayer(std::move(worldLayer));

  /* auto guiLayer = std::make_unique<EditorGuiLayer>( */
  /*   param, this->_window.get(), _view, _projection); */
  /* guiLayer->init(); */
  /* this->addLayer(std::move(guiLayer)); */
}

template<typename T>
void EditorApplication<T>::run()
{
  /* while (!this->_window->shouldClose()) { */
  /*   tick(); */
  /* } */
  _qapp->exec();
}

template<typename T>
void EditorApplication<T>::tick()
{
  /* this->_window->update(); */

  /* this->update(); */
  /* this->render(); */
  /* this->_window->show(); */
}

template class EditorApplication<SpdBackend>;
}
