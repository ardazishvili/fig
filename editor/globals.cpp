#include "globals.h"
#include "EditorApplication.h"

/* std::unique_ptr<EditorApplication<SpdBackend>> app; */
std::unique_ptr<QApplication> a;
std::unique_ptr<MainWindow> mainWindow;

Application<SpdBackend>* gApp()
{
  static auto app = std::make_unique<EditorApplication<SpdBackend>>();
  return app.get();
  /* return app.get(); */
}
