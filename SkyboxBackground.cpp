
#include "SkyboxBackground.h"

SkyboxBackground::SkyboxBackground(Camera* camera,
                                   glm::mat4& view,
                                   glm::mat4& projection)
{
  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), *camera, view, projection);
  _lampShader = std::make_unique<PhongShader>(
    _light.get(),
    *camera,
    view,
    projection,
    "/home/roman/repos/colony/shaders/vertex_light.vs",
    "/home/roman/repos/colony/shaders/fragment_light.fs");
  _light->setShader(_lampShader.get());
  _skyboxShader = std::make_unique<SkyboxShader>(
    _light.get(),
    *camera,
    view,
    projection,
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  _skybox = std::make_unique<Skybox>(*_skyboxShader);
}

void SkyboxBackground::render()
{
  _skybox.get()->render();
}

void SkyboxBackground::bind(Window* window)
{
}
