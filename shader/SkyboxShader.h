#pragma once

#include "shader/Shader.h"

namespace fig {
class SkyboxShader : public Shader {
 public:
  SkyboxShader(Light* light, Camera& camera, glm::mat4& view,
               glm::mat4& projection, const std::string& vertexPath,
               const std::string& fragmentPath);
  void configure() override;
};
}  // namespace fig
