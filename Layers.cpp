#include "Layers.h"

void Layers::add(std::unique_ptr<Layer> l)
{
  _layers.push_back(std::move(l));
}

void Layers::remove()
{
  _layers.pop_back();
}

void Layers::update()
{
  for (auto& l : _layers) {
    l->update();
  }
}

void Layers::render()
{
  for (auto& l : _layers) {
    l->render();
  }
}

void Layers::init()
{
  for (auto& l : _layers) {
    l->init();
  }
}
