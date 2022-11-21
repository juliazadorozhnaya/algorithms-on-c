#include "gtest/gtest.h"
#include "../Functions/BaseFunc.h"
#include "../Functions/FuncFactory.h"

class PolynomialTests: public ::testing::Test {
public:
    std::shared_ptr<BaseFunc> c, d, e;
    void SetUp( ) {
        FuncFactory factory;
        c = factory.create("polynomial", {-1, -1, 3, -4, 0, 1});
        d = factory.create("ident", {1, 0, 1});
        e = factory.create("const", 1.456);
    }

    void TearDown() {
        // code to run after each test;
        // can be used instead of a destructor,
        // but exceptions can be handled in this function only
    }

};

TEST_F(PolynomialTests, ToStringTest) {
    EXPECT_STREQ(c->ToString().c_str(), "-1-x+3*x^2-4*x^3+x^5");
    EXPECT_STREQ(d->ToString().c_str(), "x");
    EXPECT_STREQ(e->ToString().c_str(), "1.456");
}

TEST_F(PolynomialTests, OperatorParenthesesTest) {
    EXPECT_DOUBLE_EQ((*c)(1), -2);
    EXPECT_DOUBLE_EQ((*d)(-123), -123);
    EXPECT_DOUBLE_EQ((*e)(-123), 1.456);
}

TEST_F(PolynomialTests, DerivativesTest) {
    EXPECT_DOUBLE_EQ(c->GetDerivativeAtPoint(1), -2);
    EXPECT_DOUBLE_EQ(c->GetDerivativeAtPoint(0), -1);
    EXPECT_DOUBLE_EQ(c->GetDerivativeAtPoint(-1), -14);
}