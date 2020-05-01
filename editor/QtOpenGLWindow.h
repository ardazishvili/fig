#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <GL/glew.h>

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_5_Core>
/* #include <QOpenGLFunctions> */
#include <QWindow>

#include <memory>

class OpenGLWindow
  : public QWindow
  , protected QOpenGLFunctions_4_5_Core
{
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow* parent = 0);

  virtual void render() = 0;
  virtual void initialize() = 0;
  /* virtual void show() = 0; */

  void mouseMoveEvent(QMouseEvent* e) final;
  void mousePressEvent(QMouseEvent* e) final;
  void setAnimating(bool animating);

public slots:
  void renderLater();
  void renderNow();

signals:
  void addToLog(const QString& text);

protected:
  bool event(QEvent* event) override;
  std::unique_ptr<QOpenGLContext> _context;
  void exposeEvent(QExposeEvent* event) override;

private:
  bool _animating{ false };
  bool _initialized{ false };
};

#endif
