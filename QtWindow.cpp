#include <QDebug>
#include <QVBoxLayout>

#include "Core.h"
#include "QtWindow.h"

#include <QOpenGLContext>
#include <functional>

namespace fig
{
QtWindow::QtWindow(fig::Window::Param param,
                   std::function<void(void)> appTickFn) :
  fig::Window(param),
  _appTickFn(appTickFn)
{

  QSurfaceFormat format;
  format.setSamples(16);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(4, 5);
  format.setRenderableType(QSurfaceFormat::OpenGL);

  setFormat(format);
  resize(param.width, param.height);
  setAnimating(true);

  _mainWindow.show();
  auto* container = QWidget::createWindowContainer(this);
  auto* layout = _mainWindow.findChild<QVBoxLayout*>("layout");
  layout->addWidget(container);
};

float QtWindow::width() const
{
  return size().width();
}

float QtWindow::height() const
{
  return size().height();
}

void QtWindow::getCursorPos(double* xpos, double* ypos) const
{
}

void QtWindow::setOnEvent(
  std::function<void(std::unique_ptr<Event> event)> onEvent)
{
}

void QtWindow::update()
{
  FG_CORE_DEBUG("update window")

  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClearColor(_color.r, _color.g, _color.b, _color.alfa);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void QtWindow::show()
{
  _context->swapBuffers(this);
}

bool QtWindow::shouldClose()
{
}

void QtWindow::close()
{
}

void QtWindow::initialize()
{
}

void QtWindow::render()
{
  _appTickFn();
  update();
}
}
