#pragma once

#include <vector>

#include "shader/Shader.h"

namespace fig {
class Skybox {
 public:
  Skybox(Shader& shader);
  void loadCubemap();
  void render();

 private:
  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  unsigned int _id;
};
}  // namespace fig
