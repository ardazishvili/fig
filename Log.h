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

#endif
