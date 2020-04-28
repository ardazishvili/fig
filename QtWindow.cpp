#include <QDebug>
#include <QFrame>
#include <QPlainTextEdit>
#include <QVBoxLayout>

#include "Core.h"
#include "QtWindow.h"

#include <QOpenGLContext>
#include <functional>
#include <qnamespace.h>

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
  setAnimating(true);

  _mainWindow.setFixedSize(1920, 1200);
  _mainWindow.show();
  auto* layout = _mainWindow.findChild<QLayout*>("layout");
  auto* container = QWidget::createWindowContainer(this);
  container->setFixedSize(param.width, param.height);
  layout->addWidget(container);
  layout->setAlignment(container, Qt::AlignRight);

  auto* log = _mainWindow.findChild<QPlainTextEdit*>("log");
  QObject::connect(
    this, &OpenGLWindow::addToLog, log, &QPlainTextEdit::appendPlainText);

  container->show();
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
