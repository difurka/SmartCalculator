#include "credit.h"
#include "ui_credit.h"
#include <QDoubleValidator>

Credit::Credit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Credit) {
    controller = new s21::Controller();
    ui->setupUi(this);
    ui->radioBtnDiff->setChecked(true);
    ui->lineMonths->setValidator( new QIntValidator(0, 600, this));
    ui->linePercents->setValidator( new QDoubleValidator(0, 99.99, 2, this));
    ui->lineSumma->setValidator( new QDoubleValidator(0, 9999999999.99, 2, this));
}

Credit::~Credit() {
    delete ui;
    delete controller;
}

void Credit::on_pushButton_clicked() {
    ui->textDiff->setText("");
    controller->setCredit(ui->lineSumma->text().toDouble(), ui->lineMonths->text().toInt(),
                          ui->linePercents->text().toDouble());
    if (ui->radioBtnDiff->isChecked()) {
        controller->countForDifferentiated();
        ui->textDiff->setText("");
        ui->textDiff->setText(QString::fromStdString(controller->getListOfPaymentsFromController()));
    } else  if (ui->radioBtnAnnuity->isChecked()) {
        controller->countForAnnuity();
        ui->textDiff->setText("");
    }
    ui->labelPaymentResult->setText(QString::number(controller->getFirstPaymentFromController()));
    ui->labelTotalResult->setText(QString::number(controller->getTotalFromController()));
    ui->labelMoreResult->setText(QString::number(controller->getMoreFromController()));
}
