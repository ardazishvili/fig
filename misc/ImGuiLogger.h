#ifndef IMGUI_LOGGER_H
#define IMGUI_LOGGER_H

#include <string>

#include "../third/gui/imgui/imgui.h"
#include "ImGuiLog.h"

class ImGuiLogger
{
public:
  void log(const std::string& str, float f);
  void log(const std::string& str);
  void render();

private:
  ImGuiLog _log;
};

#endif
