#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include <glm/glm.hpp>

#include "Shader.h"

namespace fig
{
class PhongShader : public Shader
{
public:
  PhongShader(Light* light,
              Camera& camera,
              glm::mat4& view,
              glm::mat4& projection,
              const std::string& vertexPath,
              const std::string& fragmentPath,
              bool& flatView);
  void configure() override;
  bool& _flatView;
};
}

#endif
