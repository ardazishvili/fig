#include <QApplication>
#include <QDebug>
#include <QFrame>
#include <QMenu>
#include <QPlainTextEdit>
#include <QScreen>
#include <QVBoxLayout>

#include "Core.h"
#include "QtWindow.h"

#include <QOpenGLContext>
#include <functional>
#include <qnamespace.h>

static const char* vertexShaderSource = "#version 330 core\n"
                                        "layout(location = 0) in vec3 aPos;\n"
                                        "void main() {\n"
                                        "   gl_Position.xyz = aPos;\n"
                                        "   gl_Position.w = 1.0;\n"
                                        "}\n";

static const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main(){\n"
  "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

namespace fig
{
QtWindow::QtWindow(fig::Window::Param param,
                   std::function<void(void)> appTickFn) :
  fig::Window(param),
  _appTickFn(appTickFn), m_program(0), m_frame(0)
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

  /* QSurfaceFormat format; */
  /* format.setSamples(16); */
  /* setFormat(format); */
};

void QtWindow::initialize()
{
  m_program = new QOpenGLShaderProgram();
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fragmentShaderSource);
  auto res = m_program->link();
  std::cout << "shader link= " << res << std::endl;
  /* m_posAttr = m_program->attributeLocation("aPos"); */
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
  /* FG_CORE_DEBUG("update window") */

  /* const qreal retinaScale = devicePixelRatio(); */
  /* glViewport(0, 0, width() * retinaScale, height() * retinaScale); */
  /* std::cout << "width() * retinaScale= " << width() * retinaScale <<
   * std::endl; */
  /* std::cout << "height() * retinaScale= " << height() * retinaScale */
  /*           << std::endl; */
  /* glClearColor(_color.r, _color.g, _color.b, _color.alfa); */
  /* glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); */
  /* glProvokingVertex(GL_FIRST_VERTEX_CONVENTION); */
}

/* void QtWindow::show() */
/* { */
/*   _context->swapBuffers(this); */
/* } */

bool QtWindow::shouldClose()
{
}

void QtWindow::close()
{
}

/* void QtWindow::prepareGlewContext() */
/* { */
/*   _context->makeCurrent(this); */
/*   GLenum err = glewInit(); */
/*   if (GLEW_OK != err) { */
/*     qDebug() << "[Error] GLEW failed to initialize. " */
/*              << (const char*)glewGetErrorString(err); */
/*   } */
/* } */

void QtWindow::render()
{
  /* _context->makeCurrent(this); */
  /* _appTickFn(); */
  /* update(); */
  glViewport(0, 0, 1763, 941);
  glClear(GL_COLOR_BUFFER_BIT);
  auto res = m_program->bind();

  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f,  -0.5f, 0.0f, // right
    0.0f,  0.5f,  0.0f  // top
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  m_program->release();

  ++m_frame;
}
}
