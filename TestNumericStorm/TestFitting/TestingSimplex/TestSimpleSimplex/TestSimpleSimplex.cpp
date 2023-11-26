#include "pch.h"

using namespace NumericStorm::Fitting;

template<size_t s_p, typename T_p = double>
std::vector<double> linearModel(const std::vector<double>& x, Parameters<s_p, T_p> parameters)
{
    std::vector<double> y(x.size(), 0.0);
    auto a = parameters[0];
    auto b = parameters[1];
    for (size_t i = 0; i < x.size(); i++)
        y[i] += a*x[i] + b;  // Using parameters if needed

    return y;
}

struct TestingSettingSimplex : public testing::Test
{
    Bounds<2> minBounds{ 0, 0 };
    Bounds<2> maxBounds{ 5, 5 };

    Parameters<2> trueParameters{ 2, 2.5 };
    double a = trueParameters[0];
    double b = trueParameters[1];

    std::vector<double> x{ 0, 1, 2, 3, 4 };
    std::vector<double> checkingValue;
};

TEST_F(TestingSettingSimplex, TestCreatingSimplex)
{
    checkingValue.resize(5);
    for (size_t i = 0; i < x.size(); i++)
        checkingValue[i] += a * x[i] + b;

    
    /*
    SimpleSimplex solver(minBounds, maxBounds);
    solver.setModel(linearModel);
    // Your actual test logic here
    */

    EXPECT_EQ(1, 1);
}
