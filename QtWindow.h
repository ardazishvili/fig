#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include "Window.h"
#include "editor/QtOpenGLWindow.h"
#include "events/EventFabric.h"
#include "mainwindow.h"

namespace fig
{
class QtWindow
  : public Window
  , public OpenGLWindow
{
public:
  QtWindow(Window::Param param,
           EventFabric* eventFabric,
           std::function<void(void)> appInitFn,
           std::function<void(void)> appTickFn);
  float width() const override;
  float height() const override;
  void getCursorPos(double* xpos, double* ypos) const override;
  void setOnEvent(
    std::function<void(std::unique_ptr<Event> event)> onEvent) override;
  void update() override;
  void show() override;
  bool shouldClose() override;
  void close() override;
  void render() override;
  void initialize() override;

  void mouseMoveEvent(QMouseEvent* e) final;
  void mousePressEvent(QMouseEvent* e) final;
  void mouseReleaseEvent(QMouseEvent* e) final;

private:
  static EventFabric* _eventFabric;
  static std::function<void(std::unique_ptr<Event> event)> _onEvent;
  MainWindow _mainWindow;
  std::function<void(void)> _appTickFn;
  std::function<void(void)> _appInitFn;
};
}

#endif
