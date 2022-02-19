#include "shader/PhongShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"
#include "globals.h"

namespace fig {
PhongShader::PhongShader(Light* light, Camera& camera, glm::mat4& view,
                         glm::mat4& projection, const std::string& vertexPath,
                         const std::string& fragmentPath, bool& flatView)
    : Shader(light, camera, view, projection, vertexPath, fragmentPath),
      _flatView(flatView) {}

void PhongShader::configure() {
  auto cameraPosition = _camera.reference();
  setVec3("viewPos", cameraPosition);
  // material properties
  setInt("material.diffuse", 0);
  setInt("material.specular", 1);
  setFloat("material.shininess", 64.0f);

  // light properties
  auto lightPosition = _light->position();
  setVec3("light.position", lightPosition);
  setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
  setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
  setVec3("light.specular", 1.0f, 1.0f, 1.0f);

  static float fog_b = 0.603;
  static float fog_e = 8.276;
  static float fog_h = 1.0f;
  static float water_b = 1000;
  static float water_e = 1000;
  static float water_h = -0.287f;
  auto cp = _camera.eye();
  setVec3("camPosition", cp);

  setFloat("fog_b", fog_b);
  setFloat("fog_e", fog_e);
  setFloat("fog_h", fog_h);
  setFloat("water_b", water_b);
  setFloat("water_e", water_e);
  setFloat("water_h", water_h);

  setBool("flatView", _flatView);

  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
}  // namespace fig
