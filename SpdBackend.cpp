#include <iostream>

#include "SpdBackend.h"

void SpdBackend::init()
{
  std::cout << "test" << std::endl;
  spdlog::set_pattern("%^[%T] %n: %v%$");
}
