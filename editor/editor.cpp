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
  /* try { */
  /* a = std::make_unique<QApplication>(argc, argv); */
  /* mainWindow = std::make_unique<MainWindow>(); */
  /* app = std::make_unique<EditorApplication<SpdBackend>>(); */
  /* MainWindow window; */
  /* window.show(); */
  /* auto app = gApp(); */

  /* app->run(); */
  /* a->exec(); */
  /* } catch (const std::exception& e) { */
  /* std::cout << e.what() << std::endl; */
  /* } */

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  QSurfaceFormat format;
  format.setSamples(16);

  TriangleWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.setAnimating(true);

  auto* container = QWidget::createWindowContainer(&window);
  auto* layout = w.findChild<QVBoxLayout*>("layout");
  layout->addWidget(container);

  a.exec();

  return 0;
}
