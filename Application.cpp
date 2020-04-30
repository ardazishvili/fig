#include "Application.h"
#include "Core.h"
#include "SpdBackend.h"

namespace fig
{
template<typename T>
void Application<T>::addLayer(std::unique_ptr<Layer> l)
{
  FG_CORE_TRACE("adding layer to Application")
  _layers.add(std::move(l));
}

template<typename T>
void Application<T>::removeLayer()
{
  FG_CORE_TRACE("removing layer to Application")
  _layers.remove();
}

template<typename T>
void Application<T>::render()
{
  /* FG_CORE_DEBUG("rendering layers") */
  _layers.render();
}

template<typename T>
void Application<T>::update()
{
  /* FG_CORE_DEBUG("updating layers") */
  _layers.update();
}

template class Application<SpdBackend>;
}
