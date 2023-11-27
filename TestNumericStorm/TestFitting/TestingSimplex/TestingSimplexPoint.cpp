
#include "pch.h"
#include <cmath>

namespace TestingSimplexPoint{
using namespace NumericStorm::Fitting;

struct TestData
	{
		std::array<double, 2> a1{ 1.0,2.0 };
		std::array<int, 2> a2{ 1,5 };

		Parameters<2> p1{ a1 };
		Parameters<2, int> p2{ a2 };
		double t1 = 1.0;
		int t2 = 5;
	};

//template<typename T_d>
//typedef std::vector<T_d>(*model)(std::array<double, 2> param,std::vector<T_d>arguments);

std::vector<double> modelOfLine(std::vector<double>& x, Parameters<2> arguments) {
		size_t s = x.size();
		std::vector<double> y; y.resize(s);
		for (size_t i = 0; i < s; ++i)
			y[i] = arguments[0] * x[i] + arguments[1];
		return y;
	}
double chi2(const std::vector<double>& mother, const std::vector<double>& child)
	{
		size_t s = child.size();
		std::vector <double> v; v.resize(s);

		for (size_t i = 0; i < s; i++)
			v[i] = std::pow((mother[i] - child[i]), 2);
		double error = std::accumulate(v.begin(), v.end(), 0.0);
		return error;

	};

using model = std::vector<double>(*)(std::vector<double>& args, Parameters<2> param);
using ErrorModel = double(*)(const std::vector<double>& mother, const std::vector<double>& child);

struct CreatingSimpelxPoint :public testing::Test
{
	TestData testdata;
};

struct OperatorSimplexPoint :public testing::Test
{
	TestData testdata;
	SimplexPoint<2> d1{ testdata.p1 };
	SimplexPoint<2, int> d2{ testdata.p2 };
};

struct BoundsSetting : public testing::Test
	{
		Bounds<4> minBounds{ 1,2,3,4 };
		Bounds<4> maxBounds{ 11,12,13,14 };

		SimplexPoint<4> P_onlymin{ 0.1,0.2,0.3,0.4 };
		SimplexPoint<4> P_onlymax{ 21,22,23,24 };
		SimplexPoint<4> P_mix{ 21,0.1,28,0.5 };


	};
struct ModelAndError : public testing::Test {

		SimplexPoint<2> linearModel{ 1.0, 2.0 };
		model linmodel = modelOfLine;
		ErrorModel errormodel = chi2;

		std::vector<double> x = { 0,1,2,3,4 };
		std::vector<double> y = { 2,3,4,5,6 };
		std::vector<double> y1 = { 2.1,3.1,4.1,5.1,6.1 };
		double trueError = 0.05;

	};

TEST_F(CreatingSimpelxPoint, creatingByList)
	{
		SimplexPoint< 2> d1(1.0, 2.0);
		SimplexPoint<2, int> d2(1, 2);
		double t1 = 1.0, e1 = d1.getParameters()[0];
		int t2 = 1, e2 = d2.getParameters()[0];
		EXPECT_EQ(e1, t1);
		EXPECT_EQ(e2, t2);
	}
TEST_F(CreatingSimpelxPoint, creatingByCreatedArray)
	{
		SimplexPoint<2> d1{ testdata.p1 };
		SimplexPoint<2, int> d2{ testdata.p2 };
		double e1 = d1.getParameters()[0];
		int e2 = d2.getParameters()[0];
		EXPECT_EQ(e1, testdata.p1[0]);
		EXPECT_EQ(e2, testdata.p2[0]);
	}
TEST_F(OperatorSimplexPoint, operatorEqual)
	{
		EXPECT_EQ(d1, testdata.p1);
		EXPECT_EQ(d2, testdata.p2);
	}
TEST_F(OperatorSimplexPoint, testingGettingAccesOperator)
	{
		EXPECT_EQ(d1[0], testdata.t1);
		EXPECT_EQ(d2[1], testdata.t2);

		EXPECT_NE(d2[1], testdata.t1);

		EXPECT_EQ(d1[10], testdata.t1);
		EXPECT_EQ(d1[-1], testdata.t1);

	}
TEST_F(OperatorSimplexPoint, settingAccesOperator)
	{
		testdata.t1 = 10.0;  testdata.t2 = 5;
		d1[1] = testdata.t1;
		d2[1] = testdata.t2;
		EXPECT_EQ(d1[1], testdata.t1);
		EXPECT_EQ(d2[1], testdata.t2);

		d1[-1] = testdata.t1;
		d2[10] = testdata.t2;
		EXPECT_EQ(d1[0], testdata.t1);
		EXPECT_EQ(d2[0], testdata.t2);
	}
TEST_F(BoundsSetting, TestBoundsSetting)
	{
		P_onlymin.setToBounds(minBounds, maxBounds);
		EXPECT_TRUE(P_onlymin == minBounds);

		P_onlymax.setToBounds(minBounds, maxBounds);
		EXPECT_TRUE(P_onlymax == maxBounds);
	};
TEST_F(ModelAndError, testingSettingModelAndError)
	{
		linearModel.setDataModel(modelOfLine);
		linearModel.setErrorModel(chi2);

		std::vector<double> calculatedData = linearModel.calculateData(x);
		double error = linearModel.calculateError(y, calculatedData);
		double secondError = linearModel.calculateError(y1, calculatedData);
		EXPECT_EQ(calculatedData, y);
		EXPECT_EQ(error, 0);
		EXPECT_NEAR(secondError, trueError, 0.0001);
	};


struct TestSimplexPointAddSubOverload :public testing::Test
	{
		SimplexPoint<2> p1{ 1,2 }, p2{ 2,3 }, p3{ 3,5 };
		SimplexPoint<2> p1_s{ 1,2 }, p2_s{ 2,3 }, p3_s{ -1,-1 };
		float add = 2, sub = 2;
	};
struct TestSimplexPointMulDivOverload :public testing::Test
	{
		SimplexPoint<2> p1{ 1,2 }, p2{ 1,2 };
		SimplexPoint<2> p1_d{ 2,4 }, p2_d{ 2,4 };
		double mull = 2, div = 2;
	};
TEST_F(TestSimplexPointAddSubOverload, additionBetweenSimplexPoint)
	{
		SimplexPoint<2> result = p1 + p2;
		SimplexPoint<2> result2 = p1_s - p2_s;

		EXPECT_NEAR(result[0], p3[0], 0.001);
		EXPECT_NEAR(result[1], p3[1], 0.001);

		EXPECT_NEAR(result2[0], p3_s[0], 0.001);
		EXPECT_NEAR(result2[1], p3_s[1], 0.001);
	}
TEST_F(TestSimplexPointAddSubOverload, compoundAddition)
	{
		SimplexPoint<2> result = p1, result2 = p1_s;
		result += p2;
		result2 -= p2_s;
		EXPECT_NEAR(result[0], p3[0], 0.001);
		EXPECT_NEAR(result[1], p3[1], 0.001);
		EXPECT_NEAR(result2[0], p3_s[0], 0.001);
		EXPECT_NEAR(result2[1], p3_s[1], 0.001);
	}
TEST_F(TestSimplexPointAddSubOverload, additionWithScalar)
	{
		//SimplexPoint<s_p, T_p, T_d><2> p1{ 1,2 }, p2{ 2,3 }, p3{ 3,5 };
		//SimplexPoint<s_p, T_p, T_d><2> p1_s{ 1,2 }, p2_s{ 2,3 }, p3_s{ -1,-1 };
		SimplexPoint<2> result = p1, result2 = p1_s, result3 = p2, result4 = p2_s;
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
TEST_F(TestSimplexPointMulDivOverload, mul)
	{
		SimplexPoint<2> result1 = p1, result2 = p2;
		SimplexPoint<2> result3 = p1_d, result4 = p2_d;

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
	};
}
