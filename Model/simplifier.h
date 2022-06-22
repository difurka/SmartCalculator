#ifndef SRC_MODEL_SIMPLIFIER_H_
#define SRC_MODEL_SIMPLIFIER_H_


#include "helperfunctions.h"
namespace s21 {
class Simplifier {
 public:
    explicit Simplifier(std::string str): str_ {str} {}

    std::string getStr() {return str_;}

    inline void insertSubstr(std::string dst, std::string src);
    inline void substitude(std::string dst, std::string src);
    inline void modifyToSimpleForm();
 private:
    std::string str_ {"0"};
};

void Simplifier::substitude(std::string dst, std::string src) {
    insertSubstr(dst, src);
}

void Simplifier::modifyToSimpleForm() {
    if (str_.size() == 0) str_ = "0";
    substitude(" ", "");
    substitude(str_, "(" + str_ + ")");
    substitude("(-", "(0-");
    substitude("(+", "(0+");
    substitude("acos", "C");
    substitude("asin", "S");
    substitude("atan", "T");
    substitude("cos", "c");
    substitude("sin", "s");
    substitude("tan", "t");
    substitude("log", "l");
    substitude("ln", "L");
    substitude("sqrt", "q");
    substitude("mod", "m");

    size_t index = 0;
    while (str_.find("++", index) != std::string::npos ||
           str_.find("--", index) != std::string::npos ||
           str_.find("+-", index) != std::string::npos ||
           str_.find("-+", index) != std::string::npos) {
        substitude("++", "+");
        substitude("-+", "-");
        substitude("+-", "-");
        substitude("--", "+");
        index = 0;
    }
}

void Simplifier::insertSubstr(std::string dst, std::string src) {
    size_t lenSrc = src.size();
    size_t lenDst = dst.size();
    size_t index = 0;
    while (true) {
        index = str_.find(dst, index);
        if (index == std::string::npos) break;
        str_.replace(index, lenDst, src);
        index += lenSrc;
    }
}
};  // namespace s21

#endif  // SRC_MODEL_SIMPLIFIER_H_
