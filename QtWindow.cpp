#include <QApplication>
#include <QFormLayout>
#include <QFrame>
#include <QLineEdit>
#include <QMenu>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSlider>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qline.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qslider.h>
#include <qwidget.h>

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
    auto* s = _worldLayer->addSphere(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 40);
    getWidgets(s);
  });
}

void addControl(QGridLayout* l,
                int row,
                QString label,
                float value,
                std::function<void(QLineEdit*)> f,
                std::function<void(QSlider*)> g)
{
  auto* xEdit = new QLineEdit();
  xEdit->setText(QString::number(value));
  auto* xSlider = new QSlider(Qt::Orientation::Horizontal);
  xSlider->setRange(-30, 30);
  auto* xLabel = new QLabel(label);
  QObject::connect(xEdit, &QLineEdit::returnPressed, [f, xSlider, xEdit] {
    f(xEdit);
    xSlider->setValue(static_cast<int>(xEdit->text().toFloat()));
  });
  QObject::connect(xSlider, &QSlider::valueChanged, [g, xSlider, xEdit](int i) {
    g(xSlider);
    xEdit->setText(QString::number(i));
  });
  l->addWidget(xEdit, row, 0);
  l->addWidget(xSlider, row, 1);
  l->addWidget(xLabel, row, 2);
}

void QtWindow::getWidgets(Sphere* sphere)
{
  auto* properties = _mainWindow.findChild<QFrame*>("properties");
  assert(properties != nullptr);
  auto l = new QGridLayout();
  l->setColumnStretch(0, 3);
  l->setColumnStretch(1, 16);
  l->setColumnStretch(2, 1);

  auto pos = sphere->position();
  addControl(
    l,
    0,
    "x",
    pos.x,
    [sphere](QLineEdit* le) {
      auto pos = sphere->position();
      pos.x = le->text().toFloat();
      sphere->setPosition(pos);
    },
    [sphere](QSlider* slider) {
      auto pos = sphere->position();
      pos.x = slider->value();
      sphere->setPosition(pos);
    });
  addControl(
    l,
    1,
    "y",
    pos.y,
    [sphere](QLineEdit* le) {
      auto pos = sphere->position();
      pos.y = le->text().toFloat();
      sphere->setPosition(pos);
    },
    [sphere](QSlider* slider) {
      auto pos = sphere->position();
      pos.y = slider->value();
      sphere->setPosition(pos);
    });
  addControl(
    l,
    2,
    "z",
    pos.z,
    [sphere](QLineEdit* le) {
      auto pos = sphere->position();
      pos.z = le->text().toFloat();
      sphere->setPosition(pos);
    },
    [sphere](QSlider* slider) {
      auto pos = sphere->position();
      pos.z = slider->value();
      sphere->setPosition(pos);
    });
  QWidget* empty = new QWidget();
  empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  l->addWidget(empty, 3, 0, 3, 3);

  auto prevLayout = properties->layout();
  if (prevLayout != 0) {
    QLayoutItem* item;
    QWidget* widget;
    while ((item = prevLayout->takeAt(0)) != 0) {
      if ((widget = item->widget()) != 0) {
        widget->hide();
        delete widget;
      }
    }
  }
  delete prevLayout;
  properties->setLayout(l);
}
}
