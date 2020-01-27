#include "Layers.h"

void Layers::add(std::unique_ptr<Layer> l)
{
  _layers.push_back(std::move(l));
}

void Layers::remove()
{
  _layers.pop_back();
}
void Layers::render()
{
  for (auto& l : _layers) {
    l->render();
  }
}
