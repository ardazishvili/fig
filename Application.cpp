#include "Application.h"
#include "SpdBackend.h"

template<typename T>
void Application<T>::addLayer(std::unique_ptr<Layer> l)
{
  _layers.add(std::move(l));
}

template<typename T>
void Application<T>::removeLayer()
{
  _layers.remove();
}

template<typename T>
void Application<T>::render()
{
  _layers.render();
}

template<typename T>
void Application<T>::update()
{
  _layers.update();
}

template class Application<SpdBackend>;
