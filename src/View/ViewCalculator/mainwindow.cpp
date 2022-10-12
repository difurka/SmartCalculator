#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "QAbstractSpinBox"
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->spinXbegin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinXend->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinYbegin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinYend->setButtonSymbols(QAbstractSpinBox::NoButtons);
    graph = new Graph();
    connect(this, &MainWindow::signal, graph, &Graph::slot);
    credit = new Credit();

    connect(ui->buttonZero, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonOne, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonTwo, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonThree, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonFour, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonFive, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonSix, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonSeven, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonEight, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonNine, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonBracketOpen, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonBracketClose, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonDivide, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonMod, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonMult, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonPower, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonX, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonDot, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonEp, SIGNAL(clicked()), this, SLOT(printOneSymbol()));
    connect(ui->buttonEm, SIGNAL(clicked()), this, SLOT(printOneSymbol()));

    connect(ui->buttonCos, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonSin, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonTan, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonAcos, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonAsin, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonAtan, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonLn, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonLog, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
    connect(ui->buttonSqrt, SIGNAL(clicked()), this, SLOT(printSeveralSymbols()));
}

MainWindow::~MainWindow() {
    delete credit;
    delete graph;
    delete ui;
}

QLineEdit* MainWindow::getEdit() {
    QLineEdit* editWithFocus = ui->lineFormula;
    if (ui->lineX->hasFocus())
        editWithFocus = ui->lineX;
    return editWithFocus;
}

void MainWindow::printOneSymbol() {
    QPushButton *button = (QPushButton *)sender();
    getEdit()->insert(button->text());
}

void MainWindow::printSeveralSymbols() {
    QPushButton *button = (QPushButton *)sender();
    getEdit()->insert(button->text() + "()");
    getEdit()->cursorBackward(false);
}

void MainWindow::on_buttonClean_clicked() {
    getEdit()->setText("");
}

void MainWindow::on_buttonBrackets_clicked() {
    getEdit()->insert("()");
    getEdit()->cursorBackward(false);
}

void MainWindow::on_buttonDeleteOne_clicked() {
    getEdit()->backspace();
}

void MainWindow::on_buttonEqual_clicked() {
    controller = new s21::Controller();
    QString formula = ui->lineFormula->text();
    QString x = ui->lineX->text();
    controller->makeAnswer(formula.toStdString(), x.toStdString());
    ui->labelAnswer->setText(QString::fromStdString(controller->getAnswer()));
    delete controller;
}

void MainWindow::on_buttonGraph_clicked() {
     emit signal(ui->lineFormula->text(), ui->spinXbegin->value(),
                 ui->spinXend->value(), ui->spinYbegin->value(), ui->spinYend->value());
     graph->show();
}

void MainWindow::on_buttonCredit_clicked() {
     credit->show();
}

