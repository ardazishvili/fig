#ifndef APPLICATION_H
#define APPLICATION_H

#include "Layers.h"
#include "Window.h"

class Application
{
public:
  Application() = default;
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  virtual ~Application() = default;

  void addLayer(std::unique_ptr<Layer> l);
  void removeLayer();
  void update();
  void render();
  virtual void run() = 0;

protected:
  std::unique_ptr<Window> _window;

private:
  Layers _layers;
};

#endif
