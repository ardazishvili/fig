#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include "Window.h"
#include "editor/QtOpenGLWindow.h"
#include "mainwindow.h"
#include <functional>

namespace fig
{
class QtWindow
  : public Window
  , public OpenGLWindow
{
public:
  QtWindow(Window::Param param, std::function<void(void)> appTickFn);
  float width() const override;
  float height() const override;
  void getCursorPos(double* xpos, double* ypos) const override;
  void setOnEvent(
    std::function<void(std::unique_ptr<Event> event)> onEvent) override;
  void update() override;
  void show() override;
  bool shouldClose() override;
  void close() override;
  void initialize() override;
  void render() override;

private:
  MainWindow _mainWindow;
  std::function<void(void)> _appTickFn;
};
}

#endif
