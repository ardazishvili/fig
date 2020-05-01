#include <QApplication>
#include <QFrame>
#include <QMenu>
#include <QPlainTextEdit>

#include "Core.h"
#include "QtWindow.h"

namespace fig
{
QtWindow::QtWindow(fig::Window::Param param,
                   std::function<void(void)> appInitFn,
                   std::function<void(void)> appTickFn) :
  fig::Window(param),
  _appInitFn(appInitFn), _appTickFn(appTickFn)
{
  setAnimating(true);
  _mainWindow.setFixedSize(1920, 1200);
  _mainWindow.show();
  auto* frame = _mainWindow.findChild<QFrame*>("frame");
  auto* container = QWidget::createWindowContainer(this, frame);
  container->setFixedSize(frame->size());
  container->show();

  auto* log = _mainWindow.findChild<QPlainTextEdit*>("console");
  QObject::connect(
    this, &OpenGLWindow::addToLog, log, &QPlainTextEdit::appendPlainText);

  auto* menuFile = _mainWindow.findChild<QMenu*>("menuFile");
  assert(menuFile);
  auto aList = menuFile->actions();
  auto quitAction = aList.at(1);
  connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
};

void QtWindow::initialize()
{

  _appInitFn();
}

float QtWindow::width() const
{
  return size().width();
}

float QtWindow::height() const
{
  return size().height();
}

void QtWindow::getCursorPos(double* xpos, double* ypos) const
{
}

void QtWindow::setOnEvent(
  std::function<void(std::unique_ptr<Event> event)> onEvent)
{
}

void QtWindow::update()
{
  FG_CORE_DEBUG("updating QtWindow window")

  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClearColor(_color.r, _color.g, _color.b, _color.alfa);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void QtWindow::show()
{
  _context->swapBuffers(this);
}

bool QtWindow::shouldClose()
{
}

void QtWindow::close()
{
}

void QtWindow::render()
{
  update();
  _appTickFn();
}
}
