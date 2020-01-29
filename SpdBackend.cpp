#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"

#include "SpdBackend.h"

void SpdBackend::init()
{
  spdlog::set_pattern("%^[%T] %n: %v%$");
  _core = spdlog::stdout_color_mt("FIG");
  _core->set_level(spdlog::level::trace);
  _app = spdlog::stdout_color_mt("APP");
  _app->set_level(spdlog::level::trace);
}

void SpdBackend::log(Type t, Level l, const std::string& m)
{
  spdlog::logger* logger;
  switch (t) {
    case Type::Core:
      logger = _core.get();
      break;
    case Type::App:
      logger = _app.get();
      break;
    default:
      assert(0);
      break;
  }
  switch (l) {
    case Level::Trace:
      logger->trace(m);
      break;
    case Level::Debug:
      logger->debug(m);
      break;
    case Level::Info:
      logger->info(m);
      break;
    case Level::Warn:
      logger->warn(m);
      break;
    case Level::Error:
      logger->error(m);
      break;
    case Level::Critical:
      logger->error(m);
      break;
    default:
      break;
  }
}
