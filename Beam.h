#pragma once

#include <glm/detail/type_vec.hpp>

#include "LinesObject.h"

namespace fig {
class Beam : public LinesObject {
 public:
  Beam(Shader& shader, glm::vec3 begin, glm::vec3 end, float r,
       unsigned int numLines);
  void render();

 private:
  void init(glm::vec3 begin, glm::vec3 end);

  float _rotateSpeed{8.0f};
  unsigned int _fragmentsNum{10};
  float _r;
  unsigned int _numLines;
  float _ozAngle;
  float _oyAngle;
  glm::vec3 _offset;
  static constexpr glm::vec3 _zUnit = glm::vec3(0.0f, 0.0f, 1.0f);
  static constexpr glm::vec3 _yUnit = glm::vec3(0.0f, 1.0f, 0.0f);
};
}  // namespace fig
