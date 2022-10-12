#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graph) {
    ui->setupUi(this);
}

Graph::~Graph() {
    delete ui;
}

void Graph::slot(QString formula, double xBegin, double xEnd, double yBegin, double yEnd) {
    drawGraph(formula, xBegin, xEnd, yBegin, yEnd);
}

void Graph::drawGraph(QString formula, double xBegin, double xEnd, double yBegin, double yEnd) {
    ui->setupUi(this);
    controller = new s21::Controller();
    if (xBegin >= xEnd) {
        xBegin = -10;
        xEnd = 10;
    }
    if (yBegin >= yEnd) {
        yBegin = -10;
        yEnd = 10;
    }

    double h, X, Y;
    QVector<double> x, y;

    controller->makeAnswer(formula.toStdString(), "x");
    if (controller->formulaIsGood()) {
    setWindowTitle(formula);

    h = (xEnd - xBegin)/ 100000;

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    for (X = xBegin; X <= xEnd; X+=h) {
        controller->substitudeX(X);
        controller->makeCountingAfterSubstitudeX();
        Y = std::stod(controller->getAnswer());
        if (yBegin < Y && Y < yEnd) {
            y.push_back(Y);
            x.push_back(X);
        }
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    } else {
        setWindowTitle("error in the formula");
    }
    delete controller;
}
