#include "Timer.h"

std::chrono::milliseconds Timer::elapsed() const {
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = now - _start;
  return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
}

void Timer::reload() { _start = std::chrono::system_clock::now(); }
