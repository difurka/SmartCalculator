#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <iomanip>
#include <sstream>

#include "simplifier.h"
#include "modifier.h"

namespace s21 {
#define ERROR -18

class Model {
 public:
    inline void setMeaningOfX(double x) {meaningOfX_ = x;}
    inline void setPolishView(std::vector<double> polishView) {polishView_ = polishView;}
    inline std::string getAnswer() {return answer_;}
    inline std::vector<double> getPolishView() {return polishView_;}

    inline void counting();

 private:
    std::string answer_ {"0"};
    double meaningOfX_ {0};
    std::vector<double> polishView_ {std::vector<double>()};
};

void Model::counting() {
    answer_ = "unknown";
    if (polishView_.back() == ERROR) {
        answer_ = "error in the formula";
    } else {
        std::stack<double> stackOfCalculations;
        for (size_t i = 0; i < polishView_.size(); ++i) {
            if (polishView_[i] >= 0) {
                stackOfCalculations.push(polishView_[i]);
            } else if (polishView_[i] >= -8 && stackOfCalculations.size() > 1) {
                double argOne = stackOfCalculations.top();
                stackOfCalculations.pop();
                double argTwo = stackOfCalculations.top();
                stackOfCalculations.pop();
                double resultOfOperation = calculateOfPair(argTwo, argOne, polishView_[i]);
                stackOfCalculations.push(resultOfOperation);
            } else if (polishView_[i] >= -17 && stackOfCalculations.size() > 0) {
                double argOne = stackOfCalculations.top();
                stackOfCalculations.pop();
                double resultOfOperation = calculateOfOne(argOne, polishView_[i]);
                stackOfCalculations.push(resultOfOperation);
            } else if (polishView_[i] == -19) {
            stackOfCalculations.push(meaningOfX_);
            } else {
                answer_ = "error in the formula";
                break;
            }
        }
        if (stackOfCalculations.size() == 1) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(7) << stackOfCalculations.top();
            answer_ = stream.str();
        } else {
            answer_ = "error in the formula";
        }
    }
}

};  // namespace s21
#endif  // SRC_MODEL_MODEL_H_
