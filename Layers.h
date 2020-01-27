#ifndef LAYERS_H
#define LAYERS_H

#include <memory>
#include <vector>

#include "Layer.h"

class Layers
{
public:
  void add(std::unique_ptr<Layer> l);
  void remove();
  void render();

private:
  std::vector<std::unique_ptr<Layer>> _layers;
};

#endif
