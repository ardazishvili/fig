#include "Application.h"

void Application::addLayer(std::unique_ptr<Layer> l)
{
  _layers.add(std::move(l));
}

void Application::removeLayer()
{
  _layers.remove();
}

void Application::render()
{
  _layers.render();
}

void Application::update()
{
  _layers.update();
}
