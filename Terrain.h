#ifndef TERRAIN_H
#define TERRAIN_H

#include "MainTerrainMesh.h"
#include "Shader.h"

namespace fig
{
class Terrain
{
public:
  Terrain(Shader& shader,
          Camera& camera,
          float bottomLeftX,
          float bottomLeftY,
          float topRightX,
          float topRightY,
          int divisions,
          float zScale);
  void render();
  void renderSub();
  glm::vec3 getXYZ(glm::vec2 xy) const;
  glm::vec3 getRgbColor(float x, float y) const;
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);
  void growLivingArea(std::shared_ptr<LivingArea> area, float radius);
  std::pair<float, float> getMaxXy() const;
  void getSegmentVertices(glm::vec2 bottomLeft,
                          glm::vec2 topRight,
                          std::vector<VertexColor>& v,
                          SegmentDimensions* sd);
  void getSegmentObstaclesMap(glm::vec2 bottomLeft,
                              glm::vec2 topRight,
                              std::vector<bool>& m,
                              SegmentDimensions* sd);
  float halfWidth() const;
  float halfHeight() const;
  static const float SUBTERRAIN_OFFSET;

private:
  Shader& _shader;
  Camera& _camera;
  MainTerrainMesh _mainMesh;
  SubTerrainMesh _subMesh;
  float _maxX;
  float _maxY;
  float _zScale;
};
}

#endif
