#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <memory>

#include "Log.h"
#include "SpdBackend.h"

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

  template<typename... Params>
  void log(Level l, Params&&... params)
  {
    _log.print(l, params...);
  }

  virtual void run() = 0;

protected:
  Log<T> _log;
};

/* #define FG_CORE_TRACE(...) gApp()->logCore(Level::Trace, __VA_ARGS__); */
/* #define FG_CORE_DEBUG(...) gApp()->logCore(Level::Debug, __VA_ARGS__); */
/* #define FG_CORE_INFO(...) gApp()->logCore(Level::Info, __VA_ARGS__); */
/* #define FG_CORE_WARN(...) gApp()->logCore(Level::Warn, __VA_ARGS__); */
/* #define FG_CORE_ERROR(...) gApp()->logCore(Level::Error, __VA_ARGS__); */
/* #define FG_CORE_CRITICAL(...) gApp()->logCore(Level::Critical, __VA_ARGS__);
 */

#define FG_APP_TRACE(...) gApp()->log(Level::Trace, __VA_ARGS__);
#define FG_APP_DEBUG(...) gApp()->log(Level::Debug, __VA_ARGS__);
#define FG_APP_INFO(...) gApp()->log(Level::Info, __VA_ARGS__);
#define FG_APP_WARN(...) gApp()->log(Level::Warn, __VA_ARGS__);
#define FG_APP_ERROR(...) gApp()->log(Level::Error, __VA_ARGS__);
#define FG_APP_CRITICAL(...) gApp()->log(Level::Critical, __VA_ARGS__);

#endif
