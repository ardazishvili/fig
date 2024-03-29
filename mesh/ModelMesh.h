#pragma once

#include <GL/glew.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <memory>
#include <vector>

#include "Animation.h"
#include "Texture.h"
#include "Vertex.h"
#include "mesh/Mesh.h"
#define INVALID_MATERIAL 0xFFFFFFFF

namespace fig {

enum class TexturePackType {
  PreBuild,
  Initial,
  OnSelection,
  UnderFire,
  Destroyed
};

using Textures = std::vector<std::shared_ptr<Texture>>;
class ModelMesh : public Mesh {
 public:
  ModelMesh();

  struct MeshMetadata {
    MeshMetadata() {
      numIndices = 0;
      baseVertex = 0;
      baseIndex = 0;
      materialIndex = INVALID_MATERIAL;
    }

    unsigned int numIndices;
    unsigned int baseVertex;
    unsigned int baseIndex;
    unsigned int materialIndex;
    std::string name;
  };

  void render();
  bool initModel(const aiScene* pScene, const std::string& Filename);
  void loadTexture(const std::string& filename, TexturePackType type);
  void setActiveTexturesPack(TexturePackType type);
  void animate(Shader& shader, Animation::Type type, float percent);

 private:
  void initMesh(unsigned int MeshIndex, const aiMesh* paiMesh);
  void loadBones(unsigned int MeshIndex, const aiMesh* pMesh);
  bool initMaterials(const aiScene* pScene, const std::string& Filename);

  BoneMapping _boneMapping;
  std::vector<MeshMetadata> _meshesData;
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
  unsigned int _numBones;
  BonesData _bonesData;
  Animation _animation;
  bool _hasAnimation;

  Textures _initialTextures;
  Textures _onSelectionTextures;
  Textures _preBuildTextures;
  Textures _underFireTextures;
  Textures _destroyedTextures;
  TexturePackType _texturesType{TexturePackType::Initial};
};
}  // namespace fig
