#ifndef SPD_BACKEND_H
#define SPD_BACKEND_H

#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"

#include "LogBackend.h"

class SpdBackend : public LogBackend
{
public:
  SpdBackend(Type t);
  void init(Type t) override;

  template<typename... Args>
  void log(Level l, Args&&... args)
  {
    switch (l) {
      case Level::Trace:
        _logger->trace(args...);
        break;
      case Level::Debug:
        _logger->debug(args...);
        break;
      case Level::Info:
        _logger->info(args...);
        break;
      case Level::Warn:
        _logger->warn(args...);
        break;
      case Level::Error:
        _logger->error(args...);
        break;
      case Level::Critical:
        _logger->error(args...);
        break;
      default:
        break;
    }
  }

private:
  std::shared_ptr<spdlog::logger> _logger;
};

#endif
