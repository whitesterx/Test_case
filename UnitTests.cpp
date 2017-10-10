#include "Calc.h"
#include "gtest/gtest.h"

namespace {

TEST(CustomerTests, First) {
    Calc testCalc;
    testCalc.setString(std::string("-1 + 5 - 3"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(1,testCalc.evaluate());
}

TEST(CustomerTests, Second) {
    Calc testCalc;
    testCalc.setString(std::string("-10 + (8 * 2.5) - (3 / 1,5)"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(8,testCalc.evaluate());
}

TEST(CustomerTests, Third) {
    Calc testCalc;
    testCalc.setString(std::string("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(11,testCalc.evaluate());
}

TEST(CustomerTests, Fourth) {
    Calc testCalc;
    testCalc.setString(std::string("1.1 + 2.1 + abc"));
    EXPECT_FALSE(testCalc.isCorrect());
    EXPECT_STREQ("Некорректный ввод, строка содержит недопустимое выражение abc", testCalc.getErrorString().c_str());
}

TEST(DeveloperTests, Addition) {
    Calc testCalc;
    testCalc.setString(std::string("2 + 2"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(4,testCalc.evaluate());
}

TEST(DeveloperTests, Distration) {
    Calc testCalc;
    testCalc.setString(std::string("2 - 2"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(0,testCalc.evaluate());
}

TEST(DeveloperTests, Multiplication) {
    Calc testCalc;
    testCalc.setString(std::string("10 * 10"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(100,testCalc.evaluate());
}

TEST(DeveloperTests, Division) {
    Calc testCalc;
    testCalc.setString(std::string("100 / 10"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(10,testCalc.evaluate());
}

TEST(DeveloperTests, OperationsOrder) {
    Calc testCalc;
    testCalc.setString(std::string("2 + 2 * 2"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(6,testCalc.evaluate());
}

TEST(DeveloperTests, BracketsOrder) {
    Calc testCalc;
    testCalc.setString(std::string("(((2 + 2) * 2) + 2) * 2"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(20,testCalc.evaluate());
}

TEST(DeveloperTests, ZeroDivision) {
    Calc testCalc;
    testCalc.setString(std::string("2 / 0"));
    try {
        testCalc.evaluate();
    }
    catch (std::overflow_error e) {
        EXPECT_STREQ("Ошибка! Деление на 0", e.what());
    }
}

TEST(DeveloperTests, DoubleOperation) {
    Calc testCalc;
    testCalc.setString(std::string("2 ++ 2"));
    EXPECT_FALSE(testCalc.isCorrect());
    EXPECT_STREQ("Некорректный ввод, строка содержит недопустимое выражение ++", testCalc.getErrorString().c_str());
}

TEST(DeveloperTests, MoreThanTwoDigitsAfterDot) {
    Calc testCalc;
    testCalc.setString(std::string("2.222 + 2.22"));
    EXPECT_FALSE(testCalc.isCorrect());
    EXPECT_STREQ("Некорректный ввод, строка содержит недопустимое выражение 2.222", testCalc.getErrorString().c_str());
}

TEST(DeveloperTests, CommasAndDots) {
    Calc testCalc;
    testCalc.setString(std::string("1.2 + 3,4"));
    EXPECT_TRUE(testCalc.isCorrect());
    EXPECT_EQ(4.6,testCalc.evaluate());
}


}
