#pragma once

#include "SpdBackend.h"

class Core {
 public:
  Core();
  Core(const Core&) = delete;
  Core(Core&&) = delete;
  Core& operator=(const Core&) = delete;
  Core& operator=(Core&&) = delete;

  template <typename... Params>
  void log(Level l, Params&&... params) {
    _log.print(l, params...);
  }

 private:
  Log<SpdBackend> _log;
};

extern Core gCore;

#define FG_CORE_TRACE(...) gCore.log(Level::Trace, __VA_ARGS__);
#define FG_CORE_DEBUG(...) gCore.log(Level::Debug, __VA_ARGS__);
#define FG_CORE_INFO(...) gCore.log(Level::Info, __VA_ARGS__);
#define FG_CORE_WARN(...) gCore.log(Level::Warn, __VA_ARGS__);
#define FG_CORE_ERROR(...) gCore.log(Level::Error, __VA_ARGS__);
#define FG_CORE_CRITICAL(...) gCore.log(Level::Critical, __VA_ARGS__);
