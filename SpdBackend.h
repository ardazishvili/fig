#ifndef SPD_BACKEND_H
#define SPD_BACKEND_H

#include <memory>

#include "spdlog/spdlog.h"

#include "LogBackend.h"

class SpdBackend : public LogBackend
{
public:
  void init() override;
  void log(Type t, Level l, const std::string& m) override;

private:
  std::shared_ptr<spdlog::logger> _core;
  std::shared_ptr<spdlog::logger> _app;
};

#endif
