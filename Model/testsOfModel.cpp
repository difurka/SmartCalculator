#include "model.h"
#include "modifier.h"
#include "credit.h"

#include "simplifier.h"
#include "gtest/gtest.h"

TEST(model, test_get_error) {
    std::vector<std::string> str = {"177777777777777777777777777777777777777777999999999977777",
        "123456789123456789", "34-",
        "99(", "cos(8+9)cos", "/67", "1//2", "df", "c", "c(", "78+lna(5)"};
    for (int i = 0; i < str.size(); i++) {
        s21::Simplifier strWithoutX = s21::Simplifier(str[i]);
        strWithoutX.modifyToSimpleForm();
        std::string formulaWithoutX = strWithoutX.getStr();
        s21::Modifier preparForCalculate = s21::Modifier(formulaWithoutX);
        preparForCalculate.splitting();
        preparForCalculate.polishing();
        std::vector<double> strForCalculate = preparForCalculate.getPolishView();
        s21::Model model = s21::Model();
        model.setPolishView(strForCalculate);
        model.counting();
        std::string answer = model.getAnswer();
        std::string answer_original = "error in the formula";
        EXPECT_EQ(answer, answer_original);
    }
}


TEST(model, test_get_right) {
    std::vector<std::string> str = {"cos(0)", "1 / 10",  "1/(-30)",  "1 / 0.3", "1/0.03",
        "1/(-11)", "ln(3)", "atan(sqrt(78)) - 45/sin(8)", "atan(sqrt(78))",
        "45/sin(8)", "-(2*3)", "-4-3", "(-10*16)", "23+(-sin(12) + 66)",
        "-9-0", "- cos(10) + tan(2) - acos(0.5) - asin(0.5) + log(6.9)",
        "2^6 - 4.5mod0.2 ", "2--4+5", "+--+-4--++7"};
    std::vector<std::string> str_original =
    {"1", "0.1", "-0.03333333",  "3.33333333", "33.33333333",
        "-0.09090909", "1.09861229", "-44.02598101", "1.45804881",
        "45.48402983", "-6", "-7", "-160", "89.53657292", "-9", "-2.07791557",
        "63.9", "11", "3"};


    for (int i = 0; i < 3; i++) {
        s21::Simplifier strWithoutX = s21::Simplifier(str[i]);
        strWithoutX.modifyToSimpleForm();
        std::string formulaWithoutX = strWithoutX.getStr();
        s21::Modifier preparForCalculate = s21::Modifier(formulaWithoutX);
        preparForCalculate.splitting();
        preparForCalculate.polishing();
        std::vector<double> strForCalculate = preparForCalculate.getPolishView();
        s21::Model model = s21::Model();
        model.setPolishView(strForCalculate);
        model.counting();
        std::string answer = model.getAnswer();
        EXPECT_NEAR(std::stod(answer), std::stod(str_original[i]), 1.e-7);
    }
}

TEST(model, test_credit_differentiated) {
    s21::Credit credit1 = s21::Credit(50000, 15, 4.9);
    credit1.countDifferentiated();
    EXPECT_EQ(credit1.getFirstPayment(), 3537.51);
    EXPECT_EQ(credit1.getTotal(), 51531);
    EXPECT_EQ(credit1.getMore(), 1531);

    s21::Credit credit2 = s21::Credit(300000, 6, 20);
    credit2.countDifferentiated();
    EXPECT_EQ(credit2.getFirstPayment(), 55000);
    EXPECT_EQ(credit2.getTotal(), 315000);
    EXPECT_EQ(credit2.getMore(), 15000);
}

TEST(model, test_credit_annuity) {
    s21::Credit credit3 = s21::Credit(50000, 15, 4.9);
    credit3.countAnnuity();
    EXPECT_EQ(credit3.getFirstPayment(), 3443.26);
    EXPECT_EQ(credit3.getTotal(), 51648.9);
    EXPECT_NEAR(credit3.getMore(), 1648.9, 1);
}

int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

