#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Light.h"
#include "PhongShader.h"
#include "globals.h"

PhongShader::PhongShader(Light* light,
                         Camera& camera,
                         glm::mat4& view,
                         glm::mat4& projection,
                         const GLchar* vertexPath,
                         const GLchar* fragmentPath) :
  Shader(light, camera, view, projection, vertexPath, fragmentPath)
{
}

void PhongShader::configure()
{
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
  ImGui::Begin("fogWater");
  ImGui::SetWindowPos(ImVec2(0, 710));
  ImGui::SetWindowSize(ImVec2(200, 160));
  ImGui::SliderFloat("fog_b", &fog_b, 0.0f, 10.0f);
  ImGui::SliderFloat("fog_e", &fog_e, 0.0f, 10.0f);
  ImGui::SliderFloat("fog_h", &fog_h, -1.0f, 1.0f);
  ImGui::SliderFloat("water_b", &water_b, 0.0f, 1000.0f);
  ImGui::SliderFloat("water_e", &water_e, 0.0f, 1000.0f);
  ImGui::SliderFloat("water_h", &water_h, -0.31f, -0.25f);
  ImGui::End();
  auto cp = _camera.eye();
  setVec3("camPosition", cp);

  setFloat("fog_b", fog_b);
  setFloat("fog_e", fog_e);
  setFloat("fog_h", fog_h);
  setFloat("water_b", water_b);
  setFloat("water_e", water_e);
  setFloat("water_h", water_h);

  ImGui::Begin("view");
  ImGui::SetWindowPos(ImVec2(0, 310));
  ImGui::SetWindowSize(ImVec2(200, 40));
  ImGui::Checkbox("state", &flatView);
  ImGui::End();
  setBool("flatView", flatView);

  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
