#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

     QApplication app(argc, argv);
  s21::Model model;
  s21::Controller controller = s21::Controller(&model);
  MainWindow window;
  window.SetController(&controller);
  window.show();
  return app.exec();
}
