#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "Mesh.h"
#include "TerrainMesh.h"

namespace fig
{
class SphereMesh : public Mesh
{
public:
  void init(float r, unsigned int divisions);
  void render();

private:
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
};
}

#endif
