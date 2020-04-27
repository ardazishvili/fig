#include <QApplication>
#include <QDebug>
#include <QFileSystemModel>
#include <QStringList>
#include <QSurface>
#include <QTreeView>
#include <QVBoxLayout>
#include <memory>

#include "../Core.h"
#include "EditorApplication.h"
#include "globals.h"

#include "TriangleWindow.h"
#include "mainwindow.h"
/* #include "myglwidget.h" */

int main(int argc, char** argv)
{
  /* QApplication a(argc, argv); */
  /* MainWindow w; */
  /* w.show(); */

  /* QSurfaceFormat format; */
  /* format.setSamples(16); */

  /* EditorApplication<SpdBackend> window; */
  /* window.setFormat(format); */
  /* window.resize(640, 480); */
  /* window.setAnimating(true); */

  /* auto* container = QWidget::createWindowContainer(&window); */
  /* auto* layout = w.findChild<QVBoxLayout*>("layout"); */
  /* layout->addWidget(container); */

  /* a.exec(); */

  auto app = appInit(std::make_unique<QApplication>(argc, argv));
  app->run();

  return 0;
}
