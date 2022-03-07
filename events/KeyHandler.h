#pragma once

#include <map>

#include "EventManager.h"

namespace fig {

using KeyboardKey = int;
using KeyHandlerFunction = std::function<void(EventManager*)>;

class KeyHander {
 public:
  KeyHander();
  void process(KeyboardKey key, EventManager* m);
  void setHandler(KeyboardKey, KeyHandlerFunction f, std::string description);

 private:
  std::map<KeyboardKey, std::pair<KeyHandlerFunction, std::string> > _handlers;
};

}  // namespace fig
