#include "gtest/gtest.h"
#include "../Functions/BaseFunc.h"
#include "../Functions/FuncFactory.h"
#include "../NewOperators.h"
#include "../Root.h"
#include <iostream>

class ArithmeticTests : public ::testing::Test {
public:
    FuncFactory factory;
    std::shared_ptr<BaseFunc> a, b, c, d;

    void SetUp() override
    {
        a = factory.create("polynomial", {1, -2, 1});
        b = factory.create("polynomial", {0, 0, 0, 2});
        c = factory.create("polynomial", {0, 1, 0});
        d = factory.create("exp", -2);
    }
};


TEST_F(ArithmeticTests, SumTests) {
    EXPECT_STREQ((a + b) -> ToString().c_str(), "(1-2*x+x^2)+(2*x^3)");
    EXPECT_DOUBLE_EQ((a+b)->GetDerivativeAtPoint(1), 6);
    EXPECT_DOUBLE_EQ((a+b)->GetDerivativeAtPoint(0), -2);

}


TEST_F(ArithmeticTests, ProdAndDivOnlyDerivatives) {
    EXPECT_DOUBLE_EQ((c*b)->GetDerivativeAtPoint(1), 8);
    EXPECT_DOUBLE_EQ((b/c)->GetDerivativeAtPoint(1), 4);
    EXPECT_THROW((b/c)->GetDerivativeAtPoint(0), std::logic_error);
}

TEST_F(ArithmeticTests, GetRootTests) {

    auto r = getRoot(a, 10, 0.1, 220);
    std::cout << r << std::endl;
    EXPECT_NEAR(getRoot(a, 10, 0.1, 220), 1, 0.1);
    EXPECT_NEAR(getRoot(b, 10, 0.1, 250), 0, 0.1);
    EXPECT_NEAR(getRoot(c, 10, 0.1, 220), 0, 0.1);

}

TEST(ErrorTests, TestOperationsErrors) {
    FuncFactory fact;
    auto fun = fact.create("exp", 2);
    ASSERT_THROW(fun + "Hello", std::logic_error);
    ASSERT_THROW("Darkness" + fun, std::logic_error);
    ASSERT_THROW(fun + 42, std::logic_error);
    ASSERT_THROW(fun - 42, std::logic_error);
    ASSERT_THROW(42 + fun, std::logic_error);
    ASSERT_THROW(42 - fun, std::logic_error);
    ASSERT_THROW("My" - fun, std::logic_error);
    ASSERT_THROW(fun - "Old", std::logic_error);
    ASSERT_THROW(fun * "Friend", std::logic_error);
    ASSERT_THROW("I" * fun, std::logic_error);
    ASSERT_THROW(fun * 1, std::logic_error);
    ASSERT_THROW(2.2 * fun, std::logic_error);
    ASSERT_THROW(fun / "Come", std::logic_error);
    ASSERT_THROW("To Talk with you again" / fun, std::logic_error);
    ASSERT_THROW(fun / 1, std::logic_error);
    ASSERT_THROW(2.2 / fun, std::logic_error);
}

TEST(Functions, TestPowerString) {
    FuncFactory fact;
    auto fun_1 = fact.create("power", 2);
    ASSERT_EQ("x^(2.000000)", fun_1->ToString());
}

TEST(Functions, TestPolynomialString) {
    FuncFactory fact;
    auto fun_1 = fact.create("polynomial", {7, 11, 0,  3, 1, 20});
    ASSERT_EQ("7+11*x3*x^3+x^4+20*x^5", fun_1->ToString());
}


TEST(Functions, TestIdentString) {
    FuncFactory fact;
    auto fun_1 = fact.create("ident");
    ASSERT_EQ("x", fun_1->ToString());
}

TEST(Functions, TestExpString) {
    FuncFactory fact;
    auto fun_1 = fact.create("exp", 2);
    ASSERT_EQ("exp(2.000000*x)", fun_1->ToString());
}


TEST(Functions, TestConstString) {
    FuncFactory fact;
    auto fun_1 = fact.create("const", 2);
    ASSERT_EQ("2", fun_1->ToString());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}