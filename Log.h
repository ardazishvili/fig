#ifndef LOG_H
#define LOG_H

#include <memory>

enum class Level { Trace, Debug, Info, Warn, Error, Critical };
enum class Type { Core, App };

class LogBackend;
class Log
{
public:
  Log(std::unique_ptr<LogBackend> backend);
  Log(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(const Log&) = delete;
  Log& operator=(Log&&) = delete;

  static void logCore(Level l, const std::string& m);
  static void logApp(Level l, const std::string& m);

private:
  static std::unique_ptr<LogBackend> _backend;
};

std::unique_ptr<Log> createSpdlog();

#define FG_CORE_TRACE(...) ::Log::logCore(Level::Trace, __VA_ARGS__);
#define FG_CORE_DEBUG(...) ::Log::logCore(Level::Debug, __VA_ARGS__);
#define FG_CORE_INFO(...) ::Log::logCore(Level::Info, __VA_ARGS__);
#define FG_CORE_WARN(...) ::Log::logCore(Level::Warn, __VA_ARGS__);
#define FG_CORE_ERROR(...) ::Log::logCore(Level::Error, __VA_ARGS__);
#define FG_CORE_CRITICAL(...) ::Log::logCore(Level::Critical, __VA_ARGS__);

#define FG_APP_TRACE(...) ::Log::logApp(Level::Trace, __VA_ARGS__);
#define FG_APP_DEBUG(...) ::Log::logApp(Level::Debug, __VA_ARGS__);
#define FG_APP_INFO(...) ::Log::logApp(Level::Info, __VA_ARGS__);
#define FG_APP_WARN(...) ::Log::logApp(Level::Warn, __VA_ARGS__);
#define FG_APP_ERROR(...) ::Log::logApp(Level::Error, __VA_ARGS__);
#define FG_APP_CRITICAL(...) ::Log::logApp(Level::Critical, __VA_ARGS__);

#endif
