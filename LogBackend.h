#ifndef LOG_BACKEND_H
#define LOG_BACKEND_H

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
};

#endif
