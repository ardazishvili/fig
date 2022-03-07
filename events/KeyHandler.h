#pragma once

#include <map>

#include "EventManager.h"

namespace fig {

using KeyboardKey = int;
using KeyHandlerFunction = std::function<void(EventManager*)>;

struct Action {
  KeyHandlerFunction action;
  std::string description;
  bool isCustom{false};
};

using ActionMap = std::map<KeyboardKey, Action>;

class KeyHandler {
 public:
  KeyHandler();
  void process(KeyboardKey key, EventManager* m);
  void setHandler(KeyboardKey, KeyHandlerFunction f, std::string description);
  ActionMap getCustomHandlers() const;

 private:
  ActionMap _handlers;
};

}  // namespace fig
