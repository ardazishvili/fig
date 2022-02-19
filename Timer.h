#pragma once

#include <chrono>

class Timer {
 public:
  std::chrono::milliseconds elapsed() const;
  void reload();

 private:
  std::chrono::time_point<std::chrono::system_clock> _start{
      std::chrono::system_clock::now()};
};
