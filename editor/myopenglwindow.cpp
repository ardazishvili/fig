#include "myopenglwindow.h"

#include <QPainter>

OpenGLWindow::OpenGLWindow(QWindow* parent) :
  QWindow(parent), _animating(false), _context(0), _device(0)
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
    _context->create();
    needsInitialize = true;
  }
  _context->makeCurrent(this);
  if (needsInitialize) {
    initializeOpenGLFunctions();
    initialize();
  }
  render();
  _context->swapBuffers(this);
  if (_animating)
    renderLater();
}

void OpenGLWindow::setAnimating(bool animating)
{
  _animating = animating;
  if (animating)
    renderLater();
}
