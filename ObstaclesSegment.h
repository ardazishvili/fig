#pragma once

#include <memory>

#include "mesh/TerrainMeshSegment.h"

namespace fig {
class ObstaclesSegment : public TerrainMeshSegment {
 public:
  ObstaclesSegment(Shader& colorShader, Terrain& terrain, glm::vec2 bottomLeft,
                   glm::vec2 topRight);
  const std::vector<VertexColor>& vertices() const;
  const std::vector<bool>& obstacles() const;
  SegmentDimensions dimensions() const;

 protected:
  SegmentDimensions initVertices() override;
  std::vector<bool> _o;
  SegmentDimensions _sd;
};

std::unique_ptr<ObstaclesSegment> makeObstaclesSegment(Shader& colorShader,
                                                       Terrain& terrain,
                                                       glm::vec2 bottomLeft,
                                                       glm::vec2 topRight);
}  // namespace fig
