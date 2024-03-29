#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "shader/Shader.h"

namespace fig {
using Points = std::vector<glm::vec3>;
using Indices = std::vector<unsigned int>;
class LinesObject {
 public:
  LinesObject(Shader& shader);
  void initBuffers();
  void render();

  virtual ~LinesObject() = default;
  LinesObject(const LinesObject&) = delete;
  LinesObject(LinesObject&&) = delete;
  LinesObject& operator=(const LinesObject&) = delete;
  LinesObject& operator=(LinesObject&&) = delete;

 protected:
  virtual unsigned int indicesToRender();

  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  unsigned int _ebo;
  Points _v;
  Indices _i;
};
}  // namespace fig
