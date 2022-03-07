#pragma once

#include <map>
#include <memory>

#include "Model.h"
#include "types.h"

namespace fig {
enum class ModelType {
  Shell,
  Tank,
  TankFactory,
  Hq,
  Plant,
  Tree,
  Barrier,
  Shroud,
  Turbine
};

using ModelsMapping = std::map<ModelType, std::shared_ptr<Model>>;
using MenuTexturesMapping = std::map<MenuTextures, std::shared_ptr<Texture>>;
class ModelLoader {
 public:
  ModelLoader(Shader& shader);
  void load();
  Model* getModel(ModelType model) { return _models[model].get(); }
  MenuTexturesMapping menuTextures();

 private:
  Shader& _shader;
  ModelsMapping _models;
  MenuTexturesMapping _menuTextures;
};
}  // namespace fig
