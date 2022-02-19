#pragma once

#include <GL/glew.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Texture.h"
#include "mesh/ModelMesh.h"
#include "shader/Shader.h"

namespace fig {
class Model {
 public:
  Model(Shader& shader);

  bool load(const std::string& Filename);

  void render();
  void animate(Shader& shader, Animation::Type type, float percent);
  void bindTexture(Texture& texture);
  void loadTexture(const std::string& filename, TexturePackType type);
  void setActiveTexturesPack(TexturePackType type);

 private:
  bool init(const aiScene* pScene, const std::string& Filename);

  const aiScene* _scene;
  Assimp::Importer _importer;

  ModelMesh _meshes;
  Shader& _shader;
};
}  // namespace fig
