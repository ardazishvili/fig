#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <GL/glew.h>

#include <QOpenGLContext>
#include <QWindow>

#include <memory>

class OpenGLWindow : public QWindow
{
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow* parent = 0);

  virtual void render() = 0;
  virtual void initialize() = 0;
  virtual void show() = 0;
  void setAnimating(bool animating);

  void mouseMoveEvent(QMouseEvent* e) override;
  void mousePressEvent(QMouseEvent* e) override;

public slots:
  void renderLater();
  void renderNow();

protected:
  bool event(QEvent* event) override;
  std::unique_ptr<QOpenGLContext> _context;
  void exposeEvent(QExposeEvent* event) override;

private:
  bool _animating;
};

#endif
