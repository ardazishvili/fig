#pragma once

#include "mesh/SubTerrainMesh.h"
#include "mesh/TerrainMesh.h"

namespace fig {
class MainTerrainMesh : public TerrainMesh {
 public:
  void calculateHeights(unsigned int width, float bottomLeftX,
                        float bottomLeftY) override;
  void calculateColors(unsigned int width,
                       unsigned int augmentedWidth) override;
  float getZ(float x, float y) const;
  glm::vec3 getRgbColor(float x, float y) const;
  void getSegmentObstaclesMap(glm::vec2 bottomLeft, glm::vec2 topRight,
                              std::vector<bool>& m, SegmentDimensions* sd);
  void calculateIndices(int divisionsX, int divisionsY,
                        unsigned int latticeWidth) override;

 private:
  std::vector<bool> _obstaclesMap;
};
}  // namespace fig
