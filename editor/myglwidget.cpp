#include "myglwidget.h"

#include "globals.h"

namespace fig
{
MyGLWidget::MyGLWidget(QWidget* parent) : QOpenGLWidget(parent), _app(gApp())
{
}

void MyGLWidget::initializeGL()
{
}

void MyGLWidget::resizeGL(int w, int h)
{
  // Update projection matrix and other size related settings:
}

void MyGLWidget::paintGL()
{
  _app->tick();
  // Draw the scene:
  glClear(GL_COLOR_BUFFER_BIT);
  std::cout << "_qcolor.redF()= " << _qcolor.redF() << std::endl;
  glClearColor(static_cast<GLclampf>(_qcolor.redF()),
               static_cast<GLclampf>(_qcolor.greenF()),
               static_cast<GLclampf>(_qcolor.blueF()),
               1.0f);
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
  std::cout << "mouseReleasedEvent" << std::endl;
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    qDebug() << "Color choosen : " << color.name();
    _qcolor = color;
    update();
  }
}
}
