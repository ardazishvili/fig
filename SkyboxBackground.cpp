#include <filesystem>

#include "SkyboxBackground.h"

namespace fig
{
SkyboxBackground::SkyboxBackground(Camera* camera,
                                   glm::mat4& view,
                                   glm::mat4& projection,
                                   bool& flatView)
{
  auto shaders_dir = std::filesystem::current_path().string() + "/shaders";
  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), *camera, view, projection);
  _lampShader =
    std::make_unique<PhongShader>(_light.get(),
                                  *camera,
                                  view,
                                  projection,
                                  shaders_dir + "/vertex_light.vs",
                                  shaders_dir + "/fragment_light.fs",
                                  flatView);
  _light->setShader(_lampShader.get());
  _skyboxShader =
    std::make_unique<SkyboxShader>(_light.get(),
                                   *camera,
                                   view,
                                   projection,
                                   shaders_dir + "/vertex_skybox.vs",
                                   shaders_dir + "/fragment_skybox.fs");
  _skybox = std::make_unique<Skybox>(*_skyboxShader);
}

void SkyboxBackground::render()
{
  _skybox.get()->render();
}

void SkyboxBackground::bind(Window* window)
{
}
}
