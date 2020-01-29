#ifndef LOG_BACKEND_H
#define LOG_BACKEND_H

#include "Log.h"

class LogBackend
{
public:
  LogBackend() = default;
  LogBackend(const LogBackend&) = delete;
  LogBackend(LogBackend&&) = delete;
  LogBackend& operator=(const LogBackend&) = delete;
  LogBackend& operator=(LogBackend&&) = delete;
  ~LogBackend() = default;

  virtual void init() = 0;
  virtual void log(Type t, Level l, const std::string& m) = 0;
};

#endif
