#include "../Core.h"

#include "EditorApplication.h"
#include "globals.h"

int main(int argc, char** argv)
{
  try {
    auto app = gApp();

    app->run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
