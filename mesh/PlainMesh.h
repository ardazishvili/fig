#pragma once

#include <string>

#include "globals.h"
#include "mesh/Mesh.h"
#include "mesh/ModelMesh.h"

namespace fig {
class PlainMesh : public Mesh {
 public:
  void render();
  void initSurface(float bottomLeftX, float bottomLeftY, float topRightX,
                   float topRightY, int divisions,
                   std::string texturePath = assets_dir + "/grey.png");
  void loadTexture(const std::string& filename, TexturePackType type);

 private:
  std::vector<ModelMesh::MeshMetadata> _meshesData;
  Textures _initialTextures;
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
};
}  // namespace fig
