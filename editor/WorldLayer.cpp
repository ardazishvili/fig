#include "WorldLayer.h"
#include "../Light.h"
#include "../events/Event.h"
#include "EditorEventManager.h"
#include "globals.h"
#include <memory>
static const char* vertexShaderSource = "attribute highp vec4 posAttr;\n"
                                        "attribute lowp vec4 colAttr;\n"
                                        "varying lowp vec4 col;\n"
                                        "uniform highp mat4 matrix;\n"
                                        "void main() {\n"
                                        "   col = colAttr;\n"
                                        "   gl_Position = matrix * posAttr;\n"
                                        "}\n";

static const char* fragmentShaderSource = "varying lowp vec4 col;\n"
                                          "void main() {\n"
                                          "   gl_FragColor = col;\n"
                                          "}\n";

namespace fig
{
WorldLayer::WorldLayer(Window* w,
                       Camera* c,
                       glm::mat4& view,
                       glm::mat4& projection,
                       std::unique_ptr<WindowBackground> background) :
  _window(w),
  _camera(c), _view(view), _projection(projection),
  _background(std::move(background))
{
}

void WorldLayer::init()
{
  assert(_camera);
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());

  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.f);
  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), *_camera, _view, _projection);
  _colorShader = std::make_unique<PhongShader>(
    _light.get(),
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color.vs",
    "/home/roman/repos/colony/shaders/fragment_color.fs");
  _sphere = std::make_unique<Sphere>(
    *_colorShader, glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, 10);
  _eventManager = std::make_shared<EditorEventManager>(_window);
  _background->bind(_window);

  /* m_program = new QOpenGLShaderProgram(); */
  /* m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
   * vertexShaderSource); */
  /* m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, */
  /*                                    fragmentShaderSource); */
  /* m_program->link(); */
  /* m_posAttr = m_program->attributeLocation("posAttr"); */
  /* m_colAttr = m_program->attributeLocation("colAttr"); */
  /* m_matrixUniform = m_program->uniformLocation("matrix"); */
}

void WorldLayer::update()
{
  /* FG_APP_INFO("WorldLayer update"); */
}

void WorldLayer::render()
{
  /* FG_APP_INFO("WorldLayer render"); */

  /* _camera->updateSpeed(); */
  /* _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());
   */

  /* _projection = glm::perspective(glm::radians(_camera->fov()), */
  /*                                _window->width() / _window->height(), */
  /*                                0.01f, */
  /*                                1000.0f); */
  /* _background->render(); */
  /* _eventManager->tick(); */

  /* _sphere->render(); */

  /* glViewport(0, 0, 1763, 941); */
  /* glClear(GL_COLOR_BUFFER_BIT); */

  /* m_program->bind(); */

  /* QMatrix4x4 matrix; */
  /* matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f); */
  /* matrix.translate(0, 0, -2); */
  /* matrix.rotate(100.0f * m_frame / 59, 0, 1, 0); */

  /* m_program->setUniformValue(m_matrixUniform, matrix); */

  /* GLfloat vertices[] = { 0.0f, 0.707f, -0.5f, -0.5f, 0.5f, -0.5f }; */

  /* GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
   * }; */

  /* glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices); */
  /* glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors); */

  /* glEnableVertexAttribArray(0); */
  /* glEnableVertexAttribArray(1); */

  /* glDrawArrays(GL_TRIANGLES, 0, 3); */

  /* glDisableVertexAttribArray(1); */
  /* glDisableVertexAttribArray(0); */

  /* m_program->release(); */

  /* ++m_frame; */
}

std::function<void(std::unique_ptr<Event> event)> WorldLayer::onEvent()
{
  return [this](std::unique_ptr<Event> event) {
    event->process(_camera, _eventManager.get());
  };
}
}
