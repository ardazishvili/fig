#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include <QApplication>
#include <memory>

#include "../Application.h"
#include "../Camera.h"
#include "../Light.h"
#include "../events/EventFabric.h"
#include "QtOpenGLWindow.h"

#include "../QtWindow.h"
#include "../Timer.h"
#include "mainwindow.h"

namespace fig
{
template<typename T>
class EditorApplication : public Application<T>
{
public:
  EditorApplication(std::unique_ptr<QApplication> app);
  void run() override;
  void tick() override;

private:
  Camera _camera;
  std::function<void(std::unique_ptr<Event> event)> _onEvent;
  std::unique_ptr<EventFabric> _eventFabric;
  std::unique_ptr<Light> _light;
  glm::mat4 _view;
  glm::mat4 _projection;

  std::unique_ptr<QApplication> _qapp;
};
}

#endif
