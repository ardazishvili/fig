#include <QApplication>
#include <QDebug>
#include <QFileSystemModel>
#include <QStringList>
#include <QTreeView>

#include "../Core.h"
#include "EditorApplication.h"
#include "globals.h"

#include "mainwindow.h"
#include "myglwidget.h"

int main(int argc, char** argv)
{
  try {
    a = std::make_unique<QApplication>(argc, argv);
    mainWindow = std::make_unique<MainWindow>();
    /* app = std::make_unique<EditorApplication<SpdBackend>>(); */
    /* MainWindow window; */
    /* window.show(); */
    auto app = gApp();

    app->run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  /* QFileSystemModel model; */
  /* model.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files); */
  /* QStringList filters; */
  /* filters << "*.txt"; */
  /* model.setNameFilters(filters); */
  /* model.setNameFilterDisables(false); */
  /* model.setRootPath(QDir::currentPath()); */

  /* qDebug() << QDir::currentPath(); */

  /* auto* tree = w.findChild<QTreeView*>("directoryView"); */
  /* if (tree == nullptr) { */
  /*   std::cout << "tree == nullptr" << std::endl; */
  /* } */
  /* tree->setModel(&model); */
  /* tree->hideColumn(1); */
  /* tree->hideColumn(2); */
  /* tree->hideColumn(3); */
  /* tree->setAnimated(false); */
  /* tree->setIndentation(20); */
  /* tree->setSortingEnabled(true); */
  /* tree->setRootIndex(model.index(QDir::currentPath())); */
  /* tree->setWindowTitle(QObject::tr("Dir view")); */

  /* QObject::connect( */
  /*   tree, &QTreeView::clicked, [&tree](const QModelIndex& index) { */
  /*     qDebug() << tree->model()->data(index).toString(); */
  /*   }); */

  a->exec();

  return 0;
}
