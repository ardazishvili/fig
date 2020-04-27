#include "myopenglwindow.h"

#include <GL/glew.h>
#include <QDebug>
#include <QOpenGLContext>

OpenGLWindow::OpenGLWindow(QWindow* parent) :
  QWindow(parent), _animating(false), _context(0)
{
  setSurfaceType(QWindow::OpenGLSurface);
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
  bool needsInitialize = false;

  if (!_context) {
    _context = new QOpenGLContext(this);
    _context->setFormat(requestedFormat());
    auto f = requestedFormat();
    _context->create();

    needsInitialize = true;
  }
  _context->makeCurrent(this);
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    qDebug() << "[Error] GLEW failed to initialize. "
             << (const char*)glewGetErrorString(err);
  }
  if (needsInitialize) {
    initialize();
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
