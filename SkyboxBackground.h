#ifndef SKYBOX_BACKGROUND_H
#define SKYBOX_BACKGROUND_H

#include <memory>

#include "Skybox.h"
#include "WindowBackground.h"
#include "shader/PhongShader.h"
#include "shader/SkyboxShader.h"

namespace fig
{
class SkyboxBackground : public WindowBackground
{
public:
  SkyboxBackground(Camera* camera, glm::mat4& view, glm::mat4& projection, bool& flatView);

  void render() override;
  void bind(Window* window) override;

private:
  std::unique_ptr<Light> _light;
  std::unique_ptr<PhongShader> _lampShader;
  std::unique_ptr<SkyboxShader> _skyboxShader;
  std::unique_ptr<Skybox> _skybox;
};
}

#endif
