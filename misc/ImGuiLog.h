#pragma once

#include "third/gui/imgui/imgui.h"

struct ImGuiLog {
  ImGuiTextBuffer Buf;
  ImGuiTextFilter Filter;
  ImVector<int> LineOffsets;
  bool AutoScroll;

  ImGuiLog();
  void Clear();
  void AddLog(const char* fmt, ...);
  void Draw(const char* title, bool* p_open = NULL);
};
