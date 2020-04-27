#include "globals.h"
#include "EditorApplication.h"
#include <algorithm>
#include <memory>

using namespace fig;

static std::unique_ptr<EditorApplication<SpdBackend>> app;
Application<SpdBackend>* appInit(std::unique_ptr<QApplication> a)
{
  app = std::make_unique<EditorApplication<SpdBackend>>(std::move(a));
  return app.get();
}

Application<SpdBackend>* gApp()
{
  return app.get();
}
