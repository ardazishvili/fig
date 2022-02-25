#pragma once

#include <glm/glm.hpp>

#include "shader/Shader.h"

namespace fig {
class PhongShader : public Shader {
 public:
  PhongShader(Light* light, Camera& camera, glm::mat4& view,
              glm::mat4& projection, const std::string& vertexPath,
              const std::string& fragmentPath, bool& flatView);
  void configure() override;
  bool& _flatView;
};
}  // namespace fig
