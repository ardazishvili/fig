#pragma once

#include <map>
#include <memory>

#include "Model.h"
#include "types.h"

namespace fig {
enum class Models {
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

using ModelsMapping = std::map<Models, std::shared_ptr<Model>>;
using MenuTexturesMapping = std::map<MenuTextures, std::shared_ptr<Texture>>;
class ModelLoader {
 public:
  ModelLoader(Shader& shader);
  void load();
  ModelsMapping models();
  MenuTexturesMapping menuTextures();

 private:
  Shader& _shader;
  ModelsMapping _models;
  MenuTexturesMapping _menuTextures;
};
}  // namespace fig
