#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QWindow>

class OpenGLWindow
  : public QWindow
  , protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow* parent = 0);

  virtual void render() = 0;
  virtual void initialize() = 0;
  void setAnimating(bool animating);

public slots:
  void renderLater();
  void renderNow();

protected:
  bool event(QEvent* event) override;

  void exposeEvent(QExposeEvent* event) override;

private:
  bool _animating;

  QOpenGLContext* _context;
  QOpenGLPaintDevice* _device;
};

#endif
