#include <QVBoxLayout>

#include "QtWindow.h"

namespace fig
{
QtWindow::QtWindow(fig::Window::Param param) : fig::Window(param)
{

  QSurfaceFormat format;
  format.setSamples(16);

  setFormat(format);
  resize(param.width, param.height);
  setAnimating(true);
};

void QtWindow::init()
{
  _mainWindow.show();

  auto* container = QWidget::createWindowContainer(this);
  auto* layout = _mainWindow.findChild<QVBoxLayout*>("layout");
  layout->addWidget(container);
}

float QtWindow::width() const
{
}

float QtWindow::height() const
{
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
}

void QtWindow::show()
{
}

bool QtWindow::shouldClose()
{
}

void QtWindow::close()
{
}

void QtWindow::initialize()
{
}

void QtWindow::render()
{
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT);
}
}
