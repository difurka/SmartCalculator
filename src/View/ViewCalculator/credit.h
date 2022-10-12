#ifndef SRC_VIEW_VIEWCALCULATOR_CREDIT_H_
#define SRC_VIEW_VIEWCALCULATOR_CREDIT_H_

#include <QMainWindow>
#include "../../Controller/controller.h"
namespace Ui {
class Credit;
}

class Credit : public QMainWindow {
    Q_OBJECT

 public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

 private slots:
    void on_pushButton_clicked();

 private:
    Ui::Credit *ui;
    s21::Controller *controller;
};
#endif  // SRC_VIEW_VIEWCALCULATOR_CREDIT_H_
