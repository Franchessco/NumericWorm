#include "pch.h"
using namespace NumericStorm::Fitting;

namespace TestingOperationOnSimplexFigure {
	using vectorPointer = std::shared_ptr<std::vector<double>>;

std::vector<double> modelOfLine(const vectorPointer x, Parameters<2> arguments) 
	{
		int s = (*x).size();
		std::vector<double> y; 
		y.resize(s);
		for (int i = 0; i < s; ++i)
		{
			y[i] = arguments[0] * (*x)[i] + arguments[1];
		}
		return y;
	}

double chi2(const vectorPointer mother, const std::vector<double>& child)
	{
		size_t s = child.size();
		std::vector <double> v; v.resize(s);

		for (size_t i = 0; i < s; i++)
		{
			auto y = (*mother)[i] - child[i];
			v[i] = std::pow(y,2);
		}
		double error = std::accumulate(v.begin(), v.end(), 0.0);
		return error;
	};

using model = std::vector<double>(*)(vectorPointer args, Parameters<2> param);
using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);

	struct TestingSimpleOperationOnSimplexFigure :public testing::Test {
		std::vector<double> xVector{ 1, 2, 3, 4, 5 };
		SimplexPoint<2> truePoint{ 1.5,1.5 };
		std::vector<double> yVector{ 3,4.5,6,7.5,9 };
		vectorPointer xVectorPointer = std::make_unique<std::vector<double>>(xVector);
		vectorPointer trueYVectorPointer = std::make_unique<std::vector<double>>(yVector);

		Bounds<2> minBounds{ 1, 1 };
		Bounds<2> maxBounds{ 3, 3 };
		model linmodel = modelOfLine;
		ErrorModel errormodel = chi2;
		SimplexFigure<3> simplexFigure{ minBounds, maxBounds };
		SimplexFigureParameters methodParameters{ 1,0.5,2,0.5 };
		void SetUp()
		{
			simplexFigure.setModels(linmodel, errormodel);
			simplexFigure.setMotherCharacteristic(trueYVectorPointer);
			simplexFigure.setArgumentsToCalculatingData(xVectorPointer);
			simplexFigure.calculateErrors();
			simplexFigure.sort(true);
			simplexFigure.setSimplexParameters(methodParameters);
		}
	};

	TEST_F(TestingSimpleOperationOnSimplexFigure, TestingCentroidCalculation)
	{
		SetUp();
		SimplexPoint<2> trueCentroid = { 2,2 };
		SimplexPoint<2> checkingCentroind = simplexFigure.calculateCentroid();
		EXPECT_EQ(checkingCentroind, trueCentroid);
	}

	TEST_F(TestingSimpleOperationOnSimplexFigure, TestingReflection)
	{
		SetUp();
		SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
		SimplexPoint<2> trueReflectedPoint{ 1,1 };
		EXPECT_EQ(reflectedPoint, trueReflectedPoint);

	};
	TEST_F(TestingSimpleOperationOnSimplexFigure, TestingExpansion)
	{
		SetUp();
		SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
		simplexFigure.addPoint(reflectedPoint);
		SimplexPoint<2> expanedPoint = simplexFigure.expand();
		SimplexPoint<2> trueExpanedPoint{ 0,0 };
		EXPECT_EQ(expanedPoint, trueExpanedPoint);
	};

	TEST_F(TestingSimpleOperationOnSimplexFigure, TestingContraction)
	{
		SetUp();
		SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
		simplexFigure.addPoint(reflectedPoint);
		SimplexPoint<2> pointAboutContraction = simplexFigure.decidePointToContraction();
		SimplexPoint<2> contractedPoint = simplexFigure.contract();
		SimplexPoint<2> trueContractedPoint{ 1.5,1.5 };
		EXPECT_EQ(contractedPoint, trueContractedPoint);
	};

	TEST_F(TestingSimpleOperationOnSimplexFigure, TestingShrinking)
	{
		SetUp();
		std::vector<SimplexPoint<2>> shrikendPoints = simplexFigure.shrink();
		std::vector<SimplexPoint<2>> trueShrinkedPoint{ SimplexPoint<2>{2.5,2.5},SimplexPoint<2>{1.5,1.5} };
		for (int i = 0; i < 2; i++)
			EXPECT_EQ(shrikendPoints[i], trueShrinkedPoint[i]);
	};
}
