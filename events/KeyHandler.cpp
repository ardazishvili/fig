#include "events/KeyHandler.h"

#include <GLFW/glfw3.h>

#include <numeric>
#include <utility>

#include "EventManager.h"
#include "globals.h"

namespace fig {

KeyHandler::KeyHandler() {
  _handlers = {
      {GLFW_KEY_A, Handler{[](EventManager* m) { return; }, "A is pressed"}},
      {GLFW_KEY_B, Handler{[](EventManager* m) { return; }, "B is pressed"}},
      {GLFW_KEY_C, Handler{[](EventManager* m) { return; }, "C is pressed"}},
      {GLFW_KEY_D, Handler{[](EventManager* m) { return; }, "D is pressed"}},
      {GLFW_KEY_E, Handler{[](EventManager* m) { return; }, "E is pressed"}},
      {GLFW_KEY_F, Handler{[](EventManager* m) { return; }, "F is pressed"}},
      {GLFW_KEY_G, Handler{[](EventManager* m) { return; }, "G is pressed"}},
      {GLFW_KEY_H, Handler{[](EventManager* m) { return; }, "H is pressed"}},
      {GLFW_KEY_I, Handler{[](EventManager* m) { return; }, "I is pressed"}},
      {GLFW_KEY_J, Handler{[](EventManager* m) { return; }, "J is pressed"}},
      {GLFW_KEY_K, Handler{[](EventManager* m) { return; }, "K is pressed"}},
      {GLFW_KEY_L, Handler{[](EventManager* m) { return; }, "L is pressed"}},
      {GLFW_KEY_M, Handler{[](EventManager* m) { return; }, "M is pressed"}},
      {GLFW_KEY_N, Handler{[](EventManager* m) { return; }, "N is pressed"}},
      {GLFW_KEY_O, Handler{[](EventManager* m) { return; }, "O is pressed"}},
      {GLFW_KEY_P, Handler{[](EventManager* m) { return; }, "P is pressed"}},
      {GLFW_KEY_Q, Handler{[](EventManager* m) { return; }, "Q is pressed"}},
      {GLFW_KEY_R, Handler{[](EventManager* m) { return; }, "R is pressed"}},
      {GLFW_KEY_S, Handler{[](EventManager* m) { return; }, "S is pressed"}},
      {GLFW_KEY_T, Handler{[](EventManager* m) { return; }, "T is pressed"}},
      {GLFW_KEY_U, Handler{[](EventManager* m) { return; }, "U is pressed"}},
      {GLFW_KEY_V, Handler{[](EventManager* m) { return; }, "V is pressed"}},
      {GLFW_KEY_W, Handler{[](EventManager* m) { return; }, "W is pressed"}},
      {GLFW_KEY_X, Handler{[](EventManager* m) { return; }, "X is pressed"}},
      {GLFW_KEY_Y, Handler{[](EventManager* m) { return; }, "Y is pressed"}},
      {GLFW_KEY_Z, Handler{[](EventManager* m) { return; }, "Z is pressed"}},

      {GLFW_KEY_LEFT_SHIFT,
       Handler{[](EventManager* m) { return; }, "LEFT SHIFT is pressed"}},
      {GLFW_KEY_ESCAPE,
       Handler{[](EventManager* m) { return; }, "ESCAPE is pressed"}}};
}

void KeyHandler::process(KeyboardKey key, EventManager* m) {
  std::map<int, std::string> key_to_symbol = {
      {GLFW_KEY_A, "A"}, {GLFW_KEY_B, "B"}, {GLFW_KEY_C, "C"},
      {GLFW_KEY_D, "D"}, {GLFW_KEY_E, "E"}, {GLFW_KEY_F, "F"},
      {GLFW_KEY_G, "G"}, {GLFW_KEY_H, "H"}, {GLFW_KEY_I, "I"},
      {GLFW_KEY_J, "J"}, {GLFW_KEY_K, "K"}, {GLFW_KEY_L, "L"},
      {GLFW_KEY_M, "M"}, {GLFW_KEY_N, "N"}, {GLFW_KEY_O, "O"},
      {GLFW_KEY_P, "P"}, {GLFW_KEY_Q, "Q"}, {GLFW_KEY_R, "R"},
      {GLFW_KEY_S, "S"}, {GLFW_KEY_T, "T"}, {GLFW_KEY_U, "U"},
      {GLFW_KEY_V, "V"}, {GLFW_KEY_W, "W"}, {GLFW_KEY_X, "X"},
      {GLFW_KEY_Y, "Y"}, {GLFW_KEY_Z, "Z"}};

  auto config = CONFIG.get();
  for (auto [name, symbol] : config.controls) {
    if (key_to_symbol[key] == symbol) {
      _actions[name](m);
      return;
    }
  }
  _handlers[key].action(m);
  return;
}

void KeyHandler::setHandler(KeyboardKey key, KeyHandlerFunction f,
                            std::string description) {
  _handlers[key] = {f, description};
}

}  // namespace fig
