#ifndef APPLICATION_H
#define APPLICATION_H

#include "Log.h"

class Application
{
public:
  Application() = default;
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  virtual ~Application() = default;

  void init();
  virtual void run() = 0;

protected:
  virtual void initLog() = 0;
  std::unique_ptr<Log> _log;
};

#endif
