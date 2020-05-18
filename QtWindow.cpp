#include <QApplication>
#include <QFrame>
#include <QMenu>
#include <QPlainTextEdit>
#include <qpushbutton.h>

#include "Core.h"
#include "QtWindow.h"
#include "editor/events/EditorEventFabric.h"
#include "events/Event.h"

fig::EventFabric* fig::QtWindow::_eventFabric = nullptr;
std::function<void(std::unique_ptr<fig::Event> event)> fig::QtWindow::_onEvent =
  [](std::unique_ptr<fig::Event> event) {
  };

namespace fig
{
QtWindow::QtWindow(fig::Window::Param param,
                   EventFabric* eventFabric,
                   std::function<void(void)> appInitFn,
                   std::function<void(void)> appTickFn) :
  fig::Window(param),
  _appInitFn(appInitFn), _appTickFn(appTickFn)
{
  /* FG_CORE_TRACE("creating the QtWindow window"); */
  _eventFabric = eventFabric;
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

  /* auto* newSphere = _mainWindow.findChild<QPushButton*>("newSphereButton");
   */
  /* QObject::connect(newSphere, &QPushButton::clicked, [log] { */
  /* log->appendPlainText("clicked"); */
  /* }); */
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
  _onEvent = onEvent;
}

void QtWindow::update()
{
  /* FG_CORE_DEBUG("updating QtWindow window") */

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

void QtWindow::mouseMoveEvent(QMouseEvent* e)
{
  auto mods = QGuiApplication::keyboardModifiers();
  /* if (mods.testFlag(Qt::ShiftModifier)) { */
  emit addToLog(QString("Mouse moved at the position: (") +
                QString::number(e->x()) + QString(", ") +
                QString::number(e->y()) + QString(")"));
  _onEvent(_eventFabric->getMouseMoveEvent(e->x(), e->y()));
  /* } */
}

void QtWindow::mousePressEvent(QMouseEvent* e)
{
  emit addToLog(QString("Mouse pressed at the position: (") +
                QString::number(e->x()) + QString(", ") +
                QString::number(e->y()) + QString(")"));
  // TODO downcast
  auto f = dynamic_cast<EditorEventFabric*>(_eventFabric);
  _onEvent(f->getMousePressedEvent(e));
}

void QtWindow::mouseReleaseEvent(QMouseEvent* e)
{
  emit addToLog(QString("Mouse released at the position: (") +
                QString::number(e->x()) + QString(", ") +
                QString::number(e->y()) + QString(")"));
  // TODO downcast
  auto f = dynamic_cast<EditorEventFabric*>(_eventFabric);
  _onEvent(f->getMouseReleasedEvent(e));
}

void QtWindow::keyPressEvent(QKeyEvent* e)
{
  // TODO downcast
  auto f = dynamic_cast<EditorEventFabric*>(_eventFabric);
  if (!e->isAutoRepeat()) {
    emit addToLog(QString("Key is pressed: ") +
                  QKeySequence(e->key()).toString());
    _onEvent(f->getKeyPressEvent(e));
  } else {
    emit addToLog(QString("Key is repeated: ") +
                  QKeySequence(e->key()).toString());
    _onEvent(f->getKeyRepeatEvent(e));
  }
}

void QtWindow::keyReleaseEvent(QKeyEvent* e)
{
  emit addToLog(QString("Key is released: ") +
                QKeySequence(e->key()).toString());
  // TODO downcast
  auto f = dynamic_cast<EditorEventFabric*>(_eventFabric);
  _onEvent(f->getKeyReleaseEvent(e));
}

void QtWindow::setWorldLayer(WorldLayer* l)
{
  _worldLayer = l;

  auto* newSphere = _mainWindow.findChild<QPushButton*>("newSphereButton");
  QObject::connect(newSphere, &QPushButton::clicked, [this] {
    _worldLayer->addSphere(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 40);
    std::cout << "sdfsdf" << std::endl;
  });
}
}
