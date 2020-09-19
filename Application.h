#ifndef APPLICATION_H
#define APPLICATION_H

#include "Camera.h"
#include "Layers.h"
#include "Light.h"
#include "Log.h"
#include "SpdBackend.h"
#include "Window.h"

#include <memory>
#include <vector>

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
  AppEnvPrivate(std::unique_ptr<Window> window,
                std::vector<std::unique_ptr<Camera>> cameras,
                std::vector<glm::vec3> lightsCoords) :
    window(std::move(window)),
    cameras(std::move(cameras))
  {
    view = glm::lookAt(getCurrentCamera().eye(),
                       getCurrentCamera().reference(),
                       getCurrentCamera().up());
    projection =
      glm::perspective(glm::radians(getCurrentCamera().fov()),
                       this->window->width() / this->window->height(),
                       0.01f,
                       1000.0f);
    for (const auto lightCoord : lightsCoords) {
      lights.push_back(std::make_unique<Light>(
        lightCoord, getCurrentCamera(), view, projection));
    }
  }

  Light& getCurrentLight()
  {
    return *lights.at(0);
  }

  Camera& getCurrentCamera()
  {
    return *cameras.at(0);
  }

  std::vector<std::unique_ptr<fig::Camera>> cameras;
  std::vector<std::unique_ptr<fig::Light>> lights;
  std::unique_ptr<Window> window;
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
                   &_appEnv->getCurrentCamera(),
                   &_appEnv->getCurrentLight(),
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
