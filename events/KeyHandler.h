#pragma once

#include <map>

#include "EventManager.h"

namespace fig {

using KeyboardKey = int;
using KeyHandlerFunction = std::function<void(EventManager*)>;

struct Handler {
  KeyHandlerFunction action;
  std::string description;
};

using HandlerMap = std::map<KeyboardKey, Handler>;
using Actions = std::map<std::string, KeyHandlerFunction>;

class KeyHandler {
 public:
  KeyHandler();
  void process(KeyboardKey key, EventManager* m);
  void setHandler(KeyboardKey, KeyHandlerFunction f, std::string description);
  void setAction(std::string name, KeyHandlerFunction action) {
    _actions[name] = action;
  }

 private:
  HandlerMap _handlers;
  Actions _actions;
};

}  // namespace fig
