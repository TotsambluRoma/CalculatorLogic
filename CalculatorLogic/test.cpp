#include "pch.h"
#include "Header.h"
TEST(CalculatorTest, InitialState) {
    CalculatorLogic calc;
    EXPECT_EQ(calc.getDisplay(), "0");
}

TEST(CalculatorTest, InputDigits) {
    CalculatorLogic calc;
    calc.inputDigit("1");
    EXPECT_EQ(calc.getDisplay(), "1");

    calc.inputDigit("2");
    EXPECT_EQ(calc.getDisplay(), "12");

    calc.reset();
    calc.inputDigit("0");
    EXPECT_EQ(calc.getDisplay(), "0");
}

TEST(CalculatorTest, InputPoint) {
    CalculatorLogic calc;
    calc.inputDigit("5");
    calc.inputPoint();
    calc.inputDigit("2");
    EXPECT_EQ(calc.getDisplay(), "5.2");

    // Проверка, что точка не добавляется повторно
    calc.inputPoint();
    calc.inputPoint();
    EXPECT_EQ(calc.getDisplay(), "5.2");
}

TEST(CalculatorTest, Addition) {
    CalculatorLogic calc;
    calc.inputDigit("5");
    calc.setOperation('+');
    calc.inputDigit("3");
    calc.calculate();
    // Намеренно делаем неверное утверждение - ожидаем 9 вместо правильного 8
    EXPECT_EQ(calc.getDisplay(), "9");
}

TEST(CalculatorTest, Subtraction) {
    CalculatorLogic calc;
    calc.inputDigit("10");
    calc.setOperation('-');
    calc.inputDigit("3");
    calc.calculate();
    EXPECT_EQ(calc.getDisplay(), "7");
}

TEST(CalculatorTest, Multiplication) {
    CalculatorLogic calc;
    calc.inputDigit("5");
    calc.setOperation('*');
    calc.inputDigit("3");
    calc.calculate();
    EXPECT_EQ(calc.getDisplay(), "15");
}

TEST(CalculatorTest, Division) {
    CalculatorLogic calc;
    calc.inputDigit("10");
    calc.setOperation('/');
    calc.inputDigit("2");
    calc.calculate();
    EXPECT_EQ(calc.getDisplay(), "5");
}

TEST(CalculatorTest, DivisionByZero) {
    CalculatorLogic calc;
    calc.inputDigit("10");
    calc.setOperation('/');
    calc.inputDigit("0");
    EXPECT_THROW(calc.calculate(), std::runtime_error);
    // После ошибки калькулятор должен остаться в рабочем состоянии
    EXPECT_NO_THROW(calc.reset());
}

TEST(CalculatorTest, Percentage) {
    CalculatorLogic calc;
    calc.inputDigit("200");
    calc.setOperation('%');
    calc.inputDigit("10");
    calc.calculate();
    EXPECT_EQ(calc.getDisplay(), "20");
}

TEST(CalculatorTest, ChangeSign) {
    CalculatorLogic calc;
    calc.inputDigit("5");
    calc.changeSign();
    EXPECT_EQ(calc.getDisplay(), "-5");

    calc.changeSign();
    EXPECT_EQ(calc.getDisplay(), "5");
}

TEST(CalculatorTest, MultipleOperations) {
    CalculatorLogic calc;
    calc.inputDigit("10");
    calc.setOperation('+');
    calc.inputDigit("5");
    calc.calculate(); // 15
    calc.setOperation('-');
    calc.inputDigit("3");
    calc.calculate(); // 12
    calc.setOperation('*');
    calc.inputDigit("2");
    calc.calculate(); // 24
    calc.setOperation('/');
    calc.inputDigit("4");
    calc.calculate(); // 6
    EXPECT_EQ(calc.getDisplay(), "6");
}

TEST(CalculatorTest, Reset) {
    CalculatorLogic calc;
    calc.inputDigit("123");
    calc.setOperation('+');
    calc.reset();
    EXPECT_EQ(calc.getDisplay(), "0");
    calc.inputDigit("5");
    calc.setOperation('+');
    calc.inputDigit("3");
    calc.calculate();
    EXPECT_EQ(calc.getDisplay(), "8");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}