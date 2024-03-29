#include "misc/ImGuiLogger.h"

void ImGuiLogger::log(const std::string& str, float f) {
  ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
  ImGui::Begin("Log");
  _log.AddLog("[%.4f] %s=%f\n", ImGui::GetTime(), str.c_str(), f);
  ImGui::End();
  _log.Draw("Log");
}

void ImGuiLogger::log(const std::string& str) {
  ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
  ImGui::Begin("Log");
  _log.AddLog("[%.4f] %s\n", ImGui::GetTime(), str.c_str());
  ImGui::End();
  _log.Draw("Log");
}

void ImGuiLogger::render() { _log.Draw("Log"); }
