#ifndef SRC_MODEL_MODIFIER_H_
#define SRC_MODEL_MODIFIER_H_

#include "helperfunctions.h"
namespace s21 {
class Modifier {
 public:
    Modifier(): str_ {"0"} {};
    explicit Modifier(std::string str): str_ {str} {};

    std::vector<double> getPolishView() {return polishView_;}

    inline void splitting();
    inline void polishing();
 private:
    std::queue<double> formulaParsed_ {std::queue<double>({-20})};
    std::vector<double> polishView_ {std::vector<double>()};
    std::string str_ {"0"};
};

void Modifier::splitting() {
    int lenFormula = str_.size();
    for (int i = 0; i < lenFormula && formulaParsed_.back() != ERROR; ++i) {
        if (str_[i] == '(' &&
            (str_[i + 1] == '(' || isNumber(str_[i + 1]) ||
            isLetter(str_[i + 1]) || isX(str_[i + 1]))) {
                formulaParsed_.push(-2);
        } else if (str_[i] == ')' &&
                  (str_[i + 1] == ')' || isOperation(str_[i + 1]) || i + 1 == lenFormula)) {
                formulaParsed_.push(-1);
        } else if (isNumber(str_[i])) {
            formulaParsed_.push(numberToDouble(str_, &i));
            if ((isOperation(str_[i + 1]) || str_[i + 1] == ')') != true) formulaParsed_.push(ERROR);
        } else if (isLetter(str_[i]) && str_[i + 1] == '(') {
            formulaParsed_.push(letterToDouble(str_, &i));
        } else if (isOperation(str_[i]) &&
                  (str_[i + 1] == '(' || isNumber(str_[i + 1]) ||
                  isLetter(str_[i + 1]) || isX(str_[i + 1]))) {
            formulaParsed_.push(operationToDouble(str_, &i));
        } else if (isX(str_[i]) &&
                  (str_[i + 1] == ')' || isOperation(str_[i + 1]))) {
            formulaParsed_.push(-19);
        } else {
            formulaParsed_.push(ERROR);
        }
    }
    formulaParsed_.pop();
}

void Modifier::polishing() {
    if (formulaParsed_.back() == ERROR) {
        polishView_.push_back(ERROR);
    } else {
        std::stack<double> stackOfOperators;
        while (!formulaParsed_.empty()) {
            double front = formulaParsed_.front();
            if (front  >= 0 || front  == -19) {
                polishView_.push_back(front);
            } else if ((-17 <= front  && front <= -9) || front == -2) {
                stackOfOperators.push(front);
            } else if (front == -1) {
                while (stackOfOperators.top() != -2 && !stackOfOperators.empty()) {
                    polishView_.push_back(stackOfOperators.top());
                    stackOfOperators.pop();
                }
                if (!stackOfOperators.empty()) {
                    stackOfOperators.pop();
                } else {
                    polishView_.push_back(ERROR);
                    break;
                }
            } else if (-8 <= front && front <= -3) {
                while (stackOfOperators.size() > 0 && priorityOfSecondItem(front, stackOfOperators.top())) {
                    polishView_.push_back(stackOfOperators.top());
                    stackOfOperators.pop();
                }
                stackOfOperators.push(front);
            } else {
                polishView_.push_back(ERROR);
            }
            formulaParsed_.pop();
        }
        if (polishView_.back() != ERROR) {
            while (!stackOfOperators.empty()) {
                polishView_.push_back(stackOfOperators.top());
                stackOfOperators.pop();
            }
        }
    }
}
};  // namespace s21

#endif  // SRC_MODEL_MODIFIER_H_
