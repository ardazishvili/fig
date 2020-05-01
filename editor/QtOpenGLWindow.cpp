#include "QtOpenGLWindow.h"
#include "../Core.h"

#include <QMouseEvent>

OpenGLWindow::OpenGLWindow(QWindow* parent) : QWindow(parent)
{
  setSurfaceType(QWindow::OpenGLSurface);
  QSurfaceFormat format;
  format.setSamples(16);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(4, 5);
  format.setRenderableType(QSurfaceFormat::OpenGL);
  setFormat(format);

  _context = std::make_unique<QOpenGLContext>(this);
  _context->setFormat(requestedFormat());
  _context->create();
}

void OpenGLWindow::renderLater()
{
  requestUpdate();
}

bool OpenGLWindow::event(QEvent* event)
{
  switch (event->type()) {
    case QEvent::UpdateRequest:
      renderNow();
      return true;
    default:
      return QWindow::event(event);
  }
}

void OpenGLWindow::exposeEvent(QExposeEvent* event)
{
  Q_UNUSED(event);

  if (isExposed())
    renderNow();
}

void OpenGLWindow::renderNow()
{
  if (!isExposed())
    return;
  _context->makeCurrent(this);
  GLenum err = glewInit();
  if (GLEW_OK != err)
    FG_CORE_DEBUG("[Error] GLEW failed to initialize");
  if (!_initialized) {
    initializeOpenGLFunctions();
    initialize();
    _initialized = true;
  }
  render();
  show();
  if (_animating)
    renderLater();
}

void OpenGLWindow::setAnimating(bool animating)
{
  _animating = animating;

  if (animating)
    renderLater();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* e)
{
  emit addToLog(QString("Mouse at the position: (") + QString::number(e->x()) +
                QString(", ") + QString::number(e->y()) + QString(")"));
}

void OpenGLWindow::mousePressEvent(QMouseEvent* e)
{
  std::cout << "mousePressEvent" << std::endl;
}
