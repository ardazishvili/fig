#include "Log.h"
#include "LogBackend.h"
#include "SpdBackend.h"

std::unique_ptr<LogBackend> Log::_backend;

Log::Log(std::unique_ptr<LogBackend> backend)
{
  _backend = std::move(backend);
  _backend->init();
}

void Log::logCore(Level l, const std::string& m)
{
  _backend->log(Type::Core, l, m);
}

void Log::logApp(Level l, const std::string& m)
{
  _backend->log(Type::App, l, m);
}

std::unique_ptr<Log> createSpdlog()
{
  return std::make_unique<Log>(std::make_unique<SpdBackend>());
}
