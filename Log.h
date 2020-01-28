#ifndef LOG_H
#define LOG_H

#include <memory>

#include "LogBackend.h"

class Log
{
public:
  Log(std::unique_ptr<LogBackend> backend);
  Log(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(const Log&) = delete;
  Log& operator=(Log&&) = delete;

private:
  std::unique_ptr<LogBackend> _backend;
};

#endif
