#include "spdlog/sinks/stdout_color_sinks.h"

#include "SpdBackend.h"

SpdBackend::SpdBackend(Type t)
{
  init(t);
}

void SpdBackend::init(Type t)
{
  spdlog::set_pattern("%^[%T] %n: %v%$");
  switch (t) {
    case Type::App:
      _logger = spdlog::stdout_color_mt("APP");
      break;
    case Type::Core:
      _logger = spdlog::stdout_color_mt("FIG");
      break;
    default:
      assert(0);
  }
  _logger->set_level(spdlog::level::trace);
}
