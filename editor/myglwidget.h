#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "../Application.h"

#include <QColorDialog>
#include <QDebug>
#include <QOpenGLWidget>

class MyGLWidget : public QOpenGLWidget
{
public:
  MyGLWidget(QWidget* parent);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h);
  void paintGL() override;
  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  QColor _qcolor;
  Application<SpdBackend>* _app;
};

#endif // MYGLWIDGET_H
