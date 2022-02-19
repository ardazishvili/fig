#pragma once

#include <memory>
#include <vector>

#include "Layer.h"

class Layers {
 public:
  void add(std::unique_ptr<Layer> l);
  void remove();
  void update();
  void render();
  void init();

 private:
  std::vector<std::unique_ptr<Layer>> _layers;
};
