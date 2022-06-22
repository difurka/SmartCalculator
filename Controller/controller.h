#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"
#include "../Model/credit.h"

namespace s21 {
class Controller {
 public:
    Controller() {
        model = new Model();
        credit = new Credit();
    }
    Controller(Model* model_new) : model(model_new) {
        credit = new Credit();
    }
    
    ~Controller() {
        delete model;
        delete credit;
    }

    std::string getAnswer() {
        model->counting();
        std::string answer = deleteZeros(model->getAnswer());
        return answer;
    }

    bool formulaIsGood() {
        return (model->getPolishView().back() == ERROR) ? false : true;
    }

    void makeAnswer(std::string formula, std::string x) {
        Simplifier strWithoutX = Simplifier(formula);
        std::string xForInsert = "(" + x + ")";
        strWithoutX.insertSubstr("x", xForInsert);
        strWithoutX.modifyToSimpleForm();
        std::string formulaWithoutX = strWithoutX.getStr();

        Modifier preparForCalculate = Modifier(formulaWithoutX);
        preparForCalculate.splitting();
        preparForCalculate.polishing();
        std::vector<double> strForCalculate = preparForCalculate.getPolishView();

        model->setPolishView(strForCalculate);
    }

    double substitudeX(double x) {
        model->setMeaningOfX(x);
        return atof(model->getAnswer().c_str());
    }

    void makeCountingAfterSubstitudeX() {model->counting();}

    void setCredit(double summ, int months, double percents) {
        credit->setSumm(summ);
        credit->setPercents(percents);
        credit->setMonths(months);
    }

    void countForDifferentiated() {
        credit->countDifferentiated();
    }

    void countForAnnuity() {
        credit->countAnnuity();
    }

    double getMoreFromController() {return credit->getMore();}
    double getFirstPaymentFromController() {return credit->getFirstPayment();}
    double getTotalFromController() {return credit->getTotal();}
    std::string getListOfPaymentsFromController() {return credit->getListOfPayments();}

 private:
    Model* model;
    Credit *credit;
};

}  // namespace s21
#endif  // SRC_CONTROLLER_CONTROLLER_H_
