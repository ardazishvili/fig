#include "events/KeyHandler.h"

#include <GLFW/glfw3.h>

#include <numeric>
#include <utility>

#include "EventManager.h"

namespace fig {

KeyHandler::KeyHandler() {
  _handlers = {
      {GLFW_KEY_A, Action{[](EventManager* m) { return; }, "A is pressed"}},
      {GLFW_KEY_B, Action{[](EventManager* m) { return; }, "B is pressed"}},
      {GLFW_KEY_C, Action{[](EventManager* m) { return; }, "C is pressed"}},
      {GLFW_KEY_D, Action{[](EventManager* m) { return; }, "D is pressed"}},
      {GLFW_KEY_E, Action{[](EventManager* m) { return; }, "E is pressed"}},
      {GLFW_KEY_F, Action{[](EventManager* m) { return; }, "F is pressed"}},
      {GLFW_KEY_G, Action{[](EventManager* m) { return; }, "G is pressed"}},
      {GLFW_KEY_H, Action{[](EventManager* m) { return; }, "H is pressed"}},
      {GLFW_KEY_I, Action{[](EventManager* m) { return; }, "I is pressed"}},
      {GLFW_KEY_J, Action{[](EventManager* m) { return; }, "J is pressed"}},
      {GLFW_KEY_K, Action{[](EventManager* m) { return; }, "K is pressed"}},
      {GLFW_KEY_L, Action{[](EventManager* m) { return; }, "L is pressed"}},
      {GLFW_KEY_M, Action{[](EventManager* m) { return; }, "M is pressed"}},
      {GLFW_KEY_N, Action{[](EventManager* m) { return; }, "N is pressed"}},
      {GLFW_KEY_O, Action{[](EventManager* m) { return; }, "O is pressed"}},
      {GLFW_KEY_P, Action{[](EventManager* m) { return; }, "P is pressed"}},
      {GLFW_KEY_Q, Action{[](EventManager* m) { return; }, "Q is pressed"}},
      {GLFW_KEY_R, Action{[](EventManager* m) { return; }, "R is pressed"}},
      {GLFW_KEY_S, Action{[](EventManager* m) { return; }, "S is pressed"}},
      {GLFW_KEY_T, Action{[](EventManager* m) { return; }, "T is pressed"}},
      {GLFW_KEY_U, Action{[](EventManager* m) { return; }, "U is pressed"}},
      {GLFW_KEY_V, Action{[](EventManager* m) { return; }, "V is pressed"}},
      {GLFW_KEY_W, Action{[](EventManager* m) { return; }, "W is pressed"}},
      {GLFW_KEY_X, Action{[](EventManager* m) { return; }, "X is pressed"}},
      {GLFW_KEY_Y, Action{[](EventManager* m) { return; }, "Y is pressed"}},
      {GLFW_KEY_Z, Action{[](EventManager* m) { return; }, "Z is pressed"}},

      {GLFW_KEY_LEFT_SHIFT,
       {[](EventManager* m) { return; }, "LEFT SHIFT is pressed"}},
      {GLFW_KEY_ESCAPE,
       {[](EventManager* m) { return; }, "ESCAPE is pressed"}}};
}

void KeyHandler::process(KeyboardKey key, EventManager* m) {
  _handlers[key].action(m);
}

void KeyHandler::setHandler(KeyboardKey key, KeyHandlerFunction f,
                            std::string description) {
  _handlers[key] = Action(f, description, true);
}

ActionMap KeyHandler::getCustomHandlers() const {
  return std::accumulate(std::begin(_handlers), std::end(_handlers),
                         ActionMap(),
                         [](const ActionMap& acc, const auto& key_to_action) {
                           auto [key, action] = key_to_action;
                           if (action.isCustom) {
                             auto new_acc = acc;
                             new_acc.emplace(key, action);
                             return new_acc;
                           }
                           return acc;
                         });
}

}  // namespace fig
