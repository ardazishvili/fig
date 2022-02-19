#pragma once

#include <iostream>
#include <memory>

enum class Level { Trace, Debug, Info, Warn, Error, Critical };
enum class Type { Core, App };

class LogBackend;

/**
 * @brief Abstraction for log
 * Interface methods of the policy described if 'private' section
 * @tparam T - policy to handle logging, e.g. SpdBackend.
 */
template <typename T>
class Log : public T {
 public:
  /**
   * @brief Construct log using described type
   * @param t
   */
  Log(Type t) : T(t) {}
  Log(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(const Log&) = delete;
  Log& operator=(Log&&) = delete;

  /**
   * @brief Add message to stdout or file
   *
   * @tparam Params Variadic template pack of params
   * @param l Level of message, e.g. Error of Trace
   * @param params Params actual message

   */
  template <typename... Params>
  void print(Level l, Params&&... params) {
    log(l, params...);
  }

 private:
  using T::log;
};
