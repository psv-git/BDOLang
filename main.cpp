#include "./src/Qt/mainwindow.hpp"
#include "./src/Qt/choosefilewindow.hpp"
#include <QApplication>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  ChooseFileWindow cfw;
  w.show();

  return a.exec();
}
