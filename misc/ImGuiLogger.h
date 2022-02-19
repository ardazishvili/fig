#pragma once

#include <string>

#include "misc/ImGuiLog.h"
#include "third/gui/imgui/imgui.h"

class ImGuiLogger {
 public:
  void log(const std::string& str, float f);
  void log(const std::string& str);
  void render();

 private:
  ImGuiLog _log;
};
