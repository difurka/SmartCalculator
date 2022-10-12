#ifndef SRC_VIEW_VIEWCALCULATOR_GRAPH_H_
#define SRC_VIEW_VIEWCALCULATOR_GRAPH_H_

#include <QMainWindow>
#include<QVector>

#include "../../Controller/controller.h"


namespace Ui {
class Graph;
}

class Graph : public QMainWindow {
    Q_OBJECT

 public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    void drawGraph(QString formula, double xBegin, double xEnd, double yBegin, double yEnd);
 private:
    Ui::Graph *ui;
    s21::Controller *controller;

 public slots:
    void slot(QString formula, double xBegin, double xEnd, double yBegin, double yEnd);
};

#endif  // SRC_VIEW_VIEWCALCULATOR_GRAPH_H_
