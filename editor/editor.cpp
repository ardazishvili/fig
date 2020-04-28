#include <memory>

#include "../Core.h"
#include "EditorApplication.h"
#include "globals.h"

int main(int argc, char** argv)
{
  auto app = appInit(std::make_unique<QApplication>(argc, argv));
  app->run();

  return 0;
}
