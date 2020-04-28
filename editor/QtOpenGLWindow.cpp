#include "QtOpenGLWindow.h"
#include "globals.h"

#include <GL/glew.h>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <memory>

OpenGLWindow::OpenGLWindow(QWindow* parent) : QWindow(parent), _animating(false)
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
    _context = std::make_unique<QOpenGLContext>(this);
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

void OpenGLWindow::mouseMoveEvent(QMouseEvent* e)
{
  std::cout << "mouse x ix = " << e->x() << std::endl;
  std::cout << "mouse y ix = " << e->y() << std::endl;
  /* std::cout << "mouse global x ix = " << e->globalX() << std::endl; */
  /* std::cout << "mouse global y ix = " << e->globalY() << std::endl; */
}

void OpenGLWindow::mousePressEvent(QMouseEvent* e)
{
  std::cout << "mousePressEvent" << std::endl;
}
