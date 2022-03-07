#include "events/KeyHandler.h"

#include <GLFW/glfw3.h>

#include <utility>

#include "EventManager.h"

namespace fig {

KeyHander::KeyHander() {
  _handlers = {{GLFW_KEY_A, {[](EventManager* m) { return; }, "A is pressed"}},
               {GLFW_KEY_B, {[](EventManager* m) { return; }, "B is pressed"}},
               {GLFW_KEY_C, {[](EventManager* m) { return; }, "C is pressed"}},
               {GLFW_KEY_D, {[](EventManager* m) { return; }, "D is pressed"}},
               {GLFW_KEY_E, {[](EventManager* m) { return; }, "E is pressed"}},
               {GLFW_KEY_F, {[](EventManager* m) { return; }, "F is pressed"}},
               {GLFW_KEY_G, {[](EventManager* m) { return; }, "G is pressed"}},
               {GLFW_KEY_H, {[](EventManager* m) { return; }, "H is pressed"}},
               {GLFW_KEY_I, {[](EventManager* m) { return; }, "I is pressed"}},
               {GLFW_KEY_J, {[](EventManager* m) { return; }, "J is pressed"}},
               {GLFW_KEY_K, {[](EventManager* m) { return; }, "K is pressed"}},
               {GLFW_KEY_L, {[](EventManager* m) { return; }, "L is pressed"}},
               {GLFW_KEY_M, {[](EventManager* m) { return; }, "M is pressed"}},
               {GLFW_KEY_N, {[](EventManager* m) { return; }, "N is pressed"}},
               {GLFW_KEY_O, {[](EventManager* m) { return; }, "O is pressed"}},
               {GLFW_KEY_P, {[](EventManager* m) { return; }, "P is pressed"}},
               {GLFW_KEY_Q, {[](EventManager* m) { return; }, "Q is pressed"}},
               {GLFW_KEY_R, {[](EventManager* m) { return; }, "R is pressed"}},
               {GLFW_KEY_S, {[](EventManager* m) { return; }, "S is pressed"}},
               {GLFW_KEY_T, {[](EventManager* m) { return; }, "T is pressed"}},
               {GLFW_KEY_U, {[](EventManager* m) { return; }, "U is pressed"}},
               {GLFW_KEY_V, {[](EventManager* m) { return; }, "V is pressed"}},
               {GLFW_KEY_W, {[](EventManager* m) { return; }, "W is pressed"}},
               {GLFW_KEY_X, {[](EventManager* m) { return; }, "X is pressed"}},
               {GLFW_KEY_Y, {[](EventManager* m) { return; }, "Y is pressed"}},
               {GLFW_KEY_Z, {[](EventManager* m) { return; }, "Z is pressed"}},

               {GLFW_KEY_LEFT_SHIFT,
                {[](EventManager* m) { return; }, "LEFT SHIFT is pressed"}},
               {GLFW_KEY_ESCAPE,
                {[](EventManager* m) { return; }, "ESCAPE is pressed"}}};
}

void KeyHander::process(KeyboardKey key, EventManager* m) {
  _handlers[key].first(m);
}

void KeyHander::setHandler(KeyboardKey key, KeyHandlerFunction f,
                           std::string description) {
  _handlers[key] = std::pair(f, description);
}

}  // namespace fig
