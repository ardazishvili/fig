#include "Log.h"

Log::Log(std::unique_ptr<LogBackend> backend) : _backend(std::move(backend))
{
  _backend->init();
}
