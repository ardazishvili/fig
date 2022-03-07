#pragma once

#include <memory>

#include "mesh/TerrainMeshSegment.h"

namespace fig {
class HeightsSegment : public TerrainMeshSegment {
 public:
  HeightsSegment(Shader& colorShader, Terrain& terrain, glm::vec2 bottomLeft,
                 glm::vec2 topRight);

 protected:
  SegmentDimensions initVertices() override;
};

std::unique_ptr<HeightsSegment> makeHeightsSegment(Shader& colorShader,
                                                   Terrain& terrain,
                                                   glm::vec2 bottomLeft,
                                                   glm::vec2 topRight);
}  // namespace fig
