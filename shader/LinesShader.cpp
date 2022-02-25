#include "shader/LinesShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fig {
LinesShader::LinesShader(Light* light, Camera& camera, glm::mat4& view,
                         glm::mat4& projection, const std::string& vertexPath,
                         const std::string& fragmentPath)
    : Shader(light, camera, view, projection, vertexPath, fragmentPath) {}

void LinesShader::configure() {
  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
}  // namespace fig
