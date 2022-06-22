#ifndef SRC_MODEL_CREDIT_H_
#define SRC_MODEL_CREDIT_H_

#include <iostream>
#include <cmath>
#include <sstream>


namespace s21 {

class Credit {
 public:
    Credit(double summ, int months, double percents):
        summa_ {summ}, months_ {months}, percents_ {percents} {}
    Credit() {}
    double getMore() {return more_;}
    double getFirstPayment() {return firstPayment_;}
    double getTotal() {return total_;}
    std::string getListOfPayments() {return listOfPayments_;}

    void setSumm(double summ) {summa_ = summ;}
    void setPercents(double percents) {percents_ = percents;}
    void setMonths(int months) {months_ = months;}

    inline void countDifferentiated();
    inline void countAnnuity();

 private:
    double summa_ {0};
    int months_ {0};
    double percents_ {0};

    double more_ {0};
    double total_ {0};
    double firstPayment_ {0};
    std::string listOfPayments_ {""};
};

void Credit::countAnnuity() {
        double ps = percents_ / (100*12.0);
        firstPayment_ = round((summa_ * (ps + ps / (pow(1.0 + ps, months_) - 1)))*100) / 100;
        total_ = firstPayment_ * months_;
        more_ = total_ - summa_;
}

void Credit::countDifferentiated() {
        listOfPayments_ = "";
        double summaTemp = summa_;
        double base = ceil((summa_/months_)*100)/100;
        firstPayment_ = round((base + summa_*percents_/1200)*100)/100;
        std::string strOfPayments;
        std::stringstream  buffer;
        for (int i = 0; i < months_; i++) {
            strOfPayments = "";
            double nextPayment = ceil((base + summaTemp*percents_/1200)*100)/100;
            summaTemp -= (base);
            strOfPayments += std::to_string(i + 1);
            strOfPayments += " - ";
            buffer.precision(2);
            buffer << std::fixed << nextPayment;
            strOfPayments += buffer.str();
            buffer.str("");
            strOfPayments += "; ";
            if (i % 12 == 11) strOfPayments += "\n\n";
            listOfPayments_ += strOfPayments;
        }
        more_ = round(((percents_ * summa_ * months_ + 1) / 12 / 2.0)/100);
        total_ = more_ + summa_;
}

};  // namespace s21
#endif  // SRC_MODEL_CREDIT_H_
