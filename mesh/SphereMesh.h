#pragma once

#include "mesh/Mesh.h"
#include "mesh/TerrainMesh.h"

namespace fig {
class SphereMesh : public Mesh {
 public:
  void init(float r, unsigned int divisions);
  void render();

 private:
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
};
}  // namespace fig
