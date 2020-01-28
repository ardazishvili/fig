#ifndef SPD_BACKEND_H
#define SPD_BACKEND_H

#include "spdlog/spdlog.h"

#include "LogBackend.h"

class SpdBackend : public LogBackend
{
public:
  void init() override;
};

#endif
