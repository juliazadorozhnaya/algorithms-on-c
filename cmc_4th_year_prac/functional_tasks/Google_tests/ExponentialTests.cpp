#include "gtest/gtest.h"
#include "../Functions/BaseFunc.h"
#include "../Functions/FuncFactory.h"
#include <math.h>


class ExponentTests : public ::testing::Test {
protected:
    std::shared_ptr<BaseFunc> a, b, c;
    void SetUp() override {
        FuncFactory factory;
        a = factory.create("exp", 0);
        b = factory.create("exp", {0, 1});
        c = factory.create("exp", {-1, -1, 2, -2, 0, 1});
    }
};


TEST_F(ExponentTests, ToStringTest) {
    EXPECT_STREQ(a->ToString().c_str(), "1");
    EXPECT_STREQ(b->ToString().c_str(), "1");
    EXPECT_STREQ(c->ToString().c_str(), "exp(-1.000000*x)");
}

TEST_F(ExponentTests, OperatorParenthesesTest) {
    EXPECT_DOUBLE_EQ((*a)(0), 1);
    EXPECT_DOUBLE_EQ((*a)(-12), 1);
    EXPECT_NEAR((*c)(-12), exp(12), 0.01);
    EXPECT_NEAR((*c)(12), exp(-12), 0.01);
}