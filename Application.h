#ifndef APPLICATION_H
#define APPLICATION_H

#include "Layers.h"
#include "Log.h"
#include "SpdBackend.h"
#include "Window.h"

#include <memory>

template<typename T>
class Application
{
public:
  Application() : _log(Type::App)
  {
  }
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = default;
  Application& operator=(Application&&) = default;
  virtual ~Application() = default;

  void addLayer(std::unique_ptr<Layer> l);
  void removeLayer();
  void update();
  void render();
  virtual void run() = 0;
  template<typename... Params>

  void log(Level l, Params&&... params)
  {
    _log.print(l, params...);
  }

protected:
  std::unique_ptr<Window> _window;
  Log<T> _log;

private:
  Layers _layers;
};

#define FG_APP_TRACE(...) gApp()->log(Level::Trace, __VA_ARGS__);
#define FG_APP_DEBUG(...) gApp()->log(Level::Debug, __VA_ARGS__);
#define FG_APP_INFO(...) gApp()->log(Level::Info, __VA_ARGS__);
#define FG_APP_WARN(...) gApp()->log(Level::Warn, __VA_ARGS__);
#define FG_APP_ERROR(...) gApp()->log(Level::Error, __VA_ARGS__);
#define FG_APP_CRITICAL(...) gApp()->log(Level::Critical, __VA_ARGS__);

#endif
