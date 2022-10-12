#ifndef SRC_VIEW_VIEWCALCULATOR_MAINWINDOW_H_
#define SRC_VIEW_VIEWCALCULATOR_MAINWINDOW_H_

#include <QMainWindow>
#include <QLineEdit>

#include "credit.h"
#include "graph.h"
#include "../../Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLineEdit* getEdit();



 private slots:
    void printOneSymbol();

    void printSeveralSymbols();

    void on_buttonClean_clicked();

    void on_buttonBrackets_clicked();

    void on_buttonDeleteOne_clicked();

    void on_buttonEqual_clicked();

    void on_buttonGraph_clicked();

    void on_buttonCredit_clicked();

 private:
    Ui::MainWindow *ui;
    s21::Controller* controller;
    Graph *graph;
    Credit *credit;

 signals:
    void signal(QString, double, double, double, double);
    void signalCredit();
};
#endif  // SRC_VIEW_VIEWCALCULATOR_MAINWINDOW_H_
