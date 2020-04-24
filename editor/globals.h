#include "../Application.h"
#include "../SpdBackend.h"
/* #include "EditorApplication.h" */
#include "mainwindow.h"

#include <QApplication>

/* extern std::unique_ptr<EditorApplication<SpdBackend>> app; */
extern std::unique_ptr<QApplication> a;
extern std::unique_ptr<MainWindow> mainWindow;

Application<SpdBackend>* gApp();
