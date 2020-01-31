#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <memory>

enum class Level { Trace, Debug, Info, Warn, Error, Critical };
enum class Type { Core, App };

class LogBackend;

template<typename T>
class Log : public T
{
public:
  Log(Type t) : T(t)
  {
  }
  Log(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(const Log&) = delete;
  Log& operator=(Log&&) = delete;

  template<typename... Params>
  void print(Level l, Params&&... params)
  {
    log(l, params...);
  }

private:
  using T::log;
};

#endif
