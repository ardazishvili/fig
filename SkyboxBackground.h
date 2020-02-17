#ifndef SKYBOX_BACKGROUND_H
#define SKYBOX_BACKGROUND_H

#include <memory>

#include "PhongShader.h"
#include "Skybox.h"
#include "SkyboxShader.h"
#include "WindowBackground.h"

class SkyboxBackground : public WindowBackground
{
public:
  SkyboxBackground(Camera* camera, glm::mat4& view, glm::mat4& projection);

  void render() override;
  void bind(Window* window) override;

private:
  std::unique_ptr<Light> _light;
  std::unique_ptr<PhongShader> _lampShader;
  std::unique_ptr<SkyboxShader> _skyboxShader;
  std::unique_ptr<Skybox> _skybox;
};

#endif
