#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Camera.h"
#include "shader/Shader.h"

namespace fig {
class Light {
 public:
  Light(glm::vec3 position, Camera& camera, glm::mat4& view,
        glm::mat4& projection);
  ~Light();
  void setShader(Shader* shader);
  void render();
  glm::vec3 position() const;
  void setPosition(glm::vec3 position);

 private:
  void init();

  glm::vec3 _position;
  unsigned int _vao;
  unsigned int _vbo;
  Shader* _shader;
  Camera& _camera;
  glm::mat4 _view;
  glm::mat4 _projection;
  glm::mat4 _model;
};
}  // namespace fig
