#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.h"

namespace fig {
class LinesShader : public Shader {
 public:
  LinesShader(Light* light, Camera& camera, glm::mat4& view,
              glm::mat4& projection, const std::string& vertexPath,
              const std::string& fragmentPath);
  void configure() override;

 private:
  GLFWwindow* _window;
};
}  // namespace fig
