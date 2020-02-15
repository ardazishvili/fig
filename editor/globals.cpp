#include "globals.h"
#include "EditorApplication.h"

Application<SpdBackend>* gApp()
{
  static auto app = std::make_unique<EditorApplication<SpdBackend>>();
  return app.get();
}
