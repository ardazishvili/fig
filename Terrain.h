#pragma once

#include "mesh/MainTerrainMesh.h"
#include "shader/Shader.h"

namespace fig {
class Terrain {
 public:
  Terrain(Shader& shader, Camera& camera, float bottomLeftX, float bottomLeftY,
          float topRightX, float topRightY, int divisions, float zScale);
  void render();
  void renderSub();
  glm::vec3 getXYZ(glm::vec2 xy) const;
  glm::vec3 getRgbColor(float x, float y) const;
  std::unique_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(LivingArea* area);
  void growLivingArea(LivingArea* area, float radius);
  std::pair<float, float> getMaxXy() const;
  void getSegmentVertices(glm::vec2 bottomLeft, glm::vec2 topRight,
                          std::vector<VertexColor>& v, SegmentDimensions* sd);
  void getSegmentObstaclesMap(glm::vec2 bottomLeft, glm::vec2 topRight,
                              std::vector<bool>& m, SegmentDimensions* sd);

  static constexpr float SUBTERRAIN_OFFSET = 0.03f;

 private:
  Shader& _shader;
  Camera& _camera;
  MainTerrainMesh _mainMesh;
  SubTerrainMesh _subMesh;
  float _maxX;
  float _maxY;
  float _zScale;
};
}  // namespace fig
