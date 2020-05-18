#ifndef SPHERE_H
#define SPHERE_H

#include "FObject.h"
#include "Shader.h"
#include "SphereMesh.h"
#include <glm/fwd.hpp>

namespace fig
{
class Sphere : public FObject
{
public:
  Sphere(Shader& shader,
         glm::vec3 center,
         float radius,
         unsigned int divisions);
  void render() override;
  void setPosition(glm::vec3 pos);
  glm::vec3 position() const;

private:
  Shader& _shader;
  SphereMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
};
}

#endif
