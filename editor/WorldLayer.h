#ifndef WORLD_LAYER_H
#define WORLD_LAYER_H

#include "../Camera.h"
#include "../EventManager.h"
#include "../Layer.h"
#include "../PhongShader.h"
/* #include "../Skybox.h" */
/* #include "../SkyboxShader.h" */
#include "../Sphere.h"
#include "../Window.h"
#include "../WindowBackground.h"
#include <qgridlayout.h>

namespace fig
{
class WorldLayer : public Layer
{
public:
  WorldLayer(Window* w,
             Camera* c,
             glm::mat4& view,
             glm::mat4& projection,
             std::unique_ptr<WindowBackground> background);
  void init() override;
  void update() override;
  void render() override;

  std::function<void(std::unique_ptr<Event> event)> onEvent();

  Sphere* addSphere(glm::vec3 pos, float radius, int divisions);

private:
  Window* _window;
  Camera* _camera;
  glm::mat4& _view;
  glm::mat4& _projection;
  std::unique_ptr<WindowBackground> _background;
  std::unique_ptr<PhongShader> _colorShader;
  std::unique_ptr<Light> _light;
  /* std::unique_ptr<Skybox> _skybox; */
  /* std::unique_ptr<PhongShader> _lampShader; */
  /* std::unique_ptr<SkyboxShader> _skyboxShader; */
  std::shared_ptr<EventManager> _eventManager;
  /* std::unique_ptr<Sphere> _sphere; */
  std::vector<std::unique_ptr<FObject>> _objects;
};
}

#endif
