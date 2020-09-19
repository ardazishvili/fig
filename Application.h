#ifndef APPLICATION_H
#define APPLICATION_H

#include "Layers.h"
#include "Log.h"
#include "SpdBackend.h"
#include "Window.h"

#include <memory>

namespace fig
{

struct AppEnv
{
  fig::Window* window;
  fig::Camera* camera;
  fig::Light* light;
  glm::mat4& view;
  glm::mat4& projection;
};

class AppEnvPrivate
{
public:
  AppEnvPrivate(std::unique_ptr<Window> window) :
    window(std::move(window)), camera(glm::vec3(0.0f, -45.0f, 60.0f),
                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(0.0f, 0.0f, 1.0f))
  {
    view = glm::lookAt(camera.eye(), camera.reference(), camera.up());
    projection =
      glm::perspective(glm::radians(camera.fov()),
                       this->window->width() / this->window->height(),
                       0.01f,
                       1000.0f);
    light = std::make_unique<fig::Light>(
      glm::vec3(1.2f, 0.0f, 5.0f), camera, view, projection);
  }

  fig::Camera camera;
  std::unique_ptr<Window> window;
  std::unique_ptr<Light> light;
  glm::mat4 view;
  glm::mat4 projection;
};
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
   * @brief Initialize application
   */
  void init();

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

  AppEnv getEnv()
  {
    return AppEnv{ _appEnv->window.get(),
                   &_appEnv->camera,
                   _appEnv->light.get(),
                   _appEnv->view,
                   _appEnv->projection };
  }

protected:
  /**
   * @brief App environment
   */
  std::unique_ptr<AppEnvPrivate> _appEnv;

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
}

#endif
