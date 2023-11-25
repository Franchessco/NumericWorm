#include "pch.h"



using namespace NumericStorm::Fitting;

namespace BoundsTesting {


struct TestBounds :public testing::Test
{
public:

    // Test data

    Bounds<2, int> p1{ 1, 2 };
    Bounds<2> p2{ 1.0, 2.2 };


    std::array<int, 2> d1{ 1, 2 };
    std::array<double, 2> d2{ 1.0, 2.2 };

};



TEST_F(TestBounds, constructingBoundsbylist)
{
    auto a = p1.getParameters();
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);

    std::array<int, 2> a1{ 1,2 };
    std::array<int, 2> a2{ 1,3 };
    bool b1 = (a == a1), b2 = (a == a2);

    EXPECT_EQ(b1, 1);
    EXPECT_EQ(b2, 0);

}
TEST_F(TestBounds, constructingBoundsbyarray)
{
    Bounds<2, int> p4{ d1 };
    Bounds<2> p5{ d2 };

    bool b1 = (p4.getParameters() == d1), b2 = (p5.getParameters() == d2);

    EXPECT_EQ(b1, 1);
    EXPECT_EQ(b2, 1);
}
TEST_F(TestBounds, operatorequal)
{
    EXPECT_EQ(p1, d1);
    EXPECT_EQ(p2, d2);
}
TEST_F(TestBounds, gettingBounds)
{
    int a1; double a2;

    a1 = p1[1]; a2 = p2[1];
    int t1 = d1[1]; double t2 = d2[1];

    EXPECT_EQ(a1, t1);
    EXPECT_EQ(a2, t2);

}

TEST_F(TestBounds, settingBounds)
{
    int t1 = 5; double t2 = 15.8;

    p1[1] = t1; p2[1] = t2;
    EXPECT_EQ(p1[1], t1);
    EXPECT_EQ(p2[1], t2);
}

struct TestBoundsAddSubOverload :public testing::Test
{
    Bounds<2> p1{ 1,2 }, p2{ 2,3 }, p3{ 3,5 };
    Bounds<2> p1_s{ 1,2 }, p2_s{ 2,3 }, p3_s{ -1,-1 };
    double add = 2, sub = 2;
};
struct TestBoundsMulDivOverload :public testing::Test
{
    Bounds<2> p1{ 1,2 }, p2{ 1,2 };
    Bounds<2> p1_d{ 2,4 }, p2_d{ 2,4 };
    int mull = 2, div = 2;
};
TEST_F(TestBoundsAddSubOverload, additionBetweenParameters)
{
    Bounds<2> result = p1 + p2;
    Bounds<2> result2 = p1_s - p2_s;

    EXPECT_NEAR(result[0], p3[0], 0.001);
    EXPECT_NEAR(result[1], p3[1], 0.001);

    EXPECT_NEAR(result2[0], p3_s[0], 0.001);
    EXPECT_NEAR(result2[1], p3_s[1], 0.001);
}
TEST_F(TestBoundsAddSubOverload, compoundAddition)
{
    Bounds<2> result = p1, result2 = p1_s;
    result += p2;
    result2 -= p2_s;
    EXPECT_NEAR(result[0], p3[0], 0.001);
    EXPECT_NEAR(result[1], p3[1], 0.001);
    EXPECT_NEAR(result2[0], p3_s[0], 0.001);
    EXPECT_NEAR(result2[1], p3_s[1], 0.001);
}
TEST_F(TestBoundsAddSubOverload, additionWithScalar)
{
    //Parameters<2> p1{ 1,2 }, p2{ 2,3 }, p3{ 3,5 };
    //Parameters<2> p1_s{ 1,2 }, p2_s{ 2,3 }, p3_s{ -1,-1 };
    Bounds<2> result = p1, result2 = p1_s, result3 = p2, result4 = p2_s;
    result = p1 + add;
    result2 = p1_s - sub;
    result3 += add;
    result4 -= sub;

    EXPECT_NEAR(result[0], 3, 0.001);
    EXPECT_NEAR(result[1], 4, 0.001);

    EXPECT_NEAR(result2[0], -1, 0.001);
    EXPECT_NEAR(result2[1], 0, 0.001);

    EXPECT_NEAR(result3[0], 4, 0.001);
    EXPECT_NEAR(result3[1], 5, 0.001);

    EXPECT_NEAR(result4[0], 0, 0.001);
    EXPECT_NEAR(result4[1], 1, 0.001);

}
TEST_F(TestBoundsMulDivOverload, muldiv)
{
    Bounds<2> result1 = p1, result2 = p2;
    Bounds<2> result3 = p1_d, result4 = p2_d;

    result1 = p1 * mull; result2 *= mull;
    result3 = p1_d / div; result4 /= div;

    EXPECT_NEAR(result1[0], 2, 0.001);
    EXPECT_NEAR(result1[1], 4, 0.001);

    EXPECT_NEAR(result2[0], 2, 0.001);
    EXPECT_NEAR(result2[1], 4, 0.001);

    EXPECT_NEAR(result3[0], 1, 0.001);
    EXPECT_NEAR(result3[1], 2, 0.001);

    EXPECT_NEAR(result4[0], 1, 0.001);
    EXPECT_NEAR(result4[1], 2, 0.001);
}
}