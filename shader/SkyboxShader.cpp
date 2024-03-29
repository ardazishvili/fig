#include "shader/SkyboxShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fig {
SkyboxShader::SkyboxShader(Light* light, Camera& camera, glm::mat4& view,
                           glm::mat4& projection, const std::string& vertexPath,
                           const std::string& fragmentPath)
    : Shader(light, camera, view, projection, vertexPath, fragmentPath) {}

void SkyboxShader::configure() {
  auto v = glm::mat4(glm::mat3(_view));
  setTransformation("view", glm::value_ptr(v));
  setTransformation("projection", glm::value_ptr(_projection));
  setInt("skybox", 0);
}
}  // namespace fig
