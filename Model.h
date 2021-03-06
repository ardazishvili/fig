#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Texture.h"
#include "mesh/ModelMesh.h"
#include "shader/Shader.h"

namespace fig
{
class Model
{
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
}

#endif
