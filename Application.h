#ifndef APPLICATION_H
#define APPLICATION_H

#include "Layers.h"
#include "Log.h"
#include "SpdBackend.h"
#include "Window.h"

#include <memory>

/**
 * @brief Application abstraction
 *
 * It is suggested that will be only one Application
 *
 * @tparam T policy to parametrize Log class, e.g SpdBackend
 */
template<typename T>
class Application
{
public:
  Application() : _log(Type::App)
  {
  }
  Application(const Application&) = delete;
  Application(Application&&) = delete;

  /**
   * @brief Default copy operator=
   *
   * @param other
   *
   * @return
   */
  Application& operator=(const Application& other) = default;

  /**
   * @brief Default move operator=
   *
   * @param other
   *
   * @return
   */
  Application& operator=(Application&& other) = default;
  virtual ~Application() = default;

  /**
   * @brief Add layer
   *
   * @param l
   */
  void addLayer(std::unique_ptr<Layer> l);

  /**
   * @brief Remove top layer
   */
  void removeLayer();

  /**
   * @brief Update appliction
   */
  void update();

  /**
   * @brief Render application
   */
  void render();

  /**
   * @brief Run application
   */
  virtual void run() = 0;

  /**
   * @brief One tick
   */
  virtual void tick() = 0;

  /**
   * @brief Log
   *
   * @tparam Params
   * @param l
   * @param params
   */
  template<typename... Params>
  void log(Level l, Params&&... params)
  {
    _log.print(l, params...);
  }

protected:
  /**
   * @brief Window
   */
  std::unique_ptr<Window> _window;

  /**
   * @brief Log parametrized with log backend
   */
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
