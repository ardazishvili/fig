#include "QtOpenGLWindow.h"
#include <QGuiApplication>

#include <QMouseEvent>

#include "../Core.h"

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
