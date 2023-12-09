#include "pch.h"
#include <memory>

using namespace NumericStorm::Fitting;
namespace TestingSimplexFigure
{

struct CreatingsimplexFigure : public testing::Test
{
	Bounds<3> minBounds{ 1, 1, 1 };
	Bounds<3> maxBounds{ 5,5,5 };
};
TEST_F(CreatingsimplexFigure, CreatingsimplexFigure)
	{
		SimplexFigure<4> simplexFigure(minBounds, maxBounds);

		EXPECT_EQ(simplexFigure[0], minBounds);
		EXPECT_EQ(simplexFigure[3], maxBounds);
	}

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

struct TestignSettingAndExecutingModelThrowingAnError: public testing::Test 
{
	Bounds<2> minBounds{1,1};
	Bounds<2> maxBounds{2,2};
	model linmodel = modelOfLine;
	ErrorModel errormodel = chi2;;
	SimplexFigure<3> simplexFigure{ minBounds,maxBounds };
};

TEST_F(TestignSettingAndExecutingModelThrowingAnError, TestThrowErrorTwoModelsNotSetted) 
{
	try 
	{simplexFigure.sort();}
	catch (const std::exception& e) 
	{
		std::string messege = static_cast<std::string>(e.what());
		EXPECT_STREQ("Data and Error no setted model", e.what());
	}
}
TEST_F(TestignSettingAndExecutingModelThrowingAnError, TestThrowErrorModelsNotSetted)
{
	simplexFigure.setDataModel(linmodel);
	try
	{
		simplexFigure.sort();
	}
	catch (const std::exception& e)
	{
		auto messege = e.what();
		EXPECT_STREQ("Error no setted model", messege);
	}
}

TEST_F(TestignSettingAndExecutingModelThrowingAnError, TestThrowErrorDataModelsNotSetted)
{
	simplexFigure.setErrorModel(errormodel);
	try
	{
		simplexFigure.sort();
	}
	catch (const std::exception& e)
	{
		std::string messege = static_cast<std::string>(e.what());
		EXPECT_STREQ("Data no setted model", e.what());
	}
}

struct TestignSettingAndExecutingModel : public testing::Test
{

	std::vector<double> xVector{1,2,3,4,5};
	SimplexPoint<2> truePoint{ 1.5,1.5 };
	std::vector<double> yVector{ 3,4.5,6,7.5,9};
	vectorPointer xVectorPointer = std::make_unique<std::vector<double>>(xVector);
	vectorPointer trueYVectorPointer = std::make_unique<std::vector<double>>(yVector);

	std::vector<double> yFor11{ 2,3,4,5,6};
	std::vector<double> yFor22{ 4,6,8,10,12};
	std::vector<double> yFor33{ 6,9,12,15,18};

	vectorPointer yFor11Pointer = std::make_shared<std::vector<double>>(yFor11);
	vectorPointer yFor22Pointer = std::make_shared<std::vector<double>>(yFor22);
	vectorPointer yFor33Pointer = std::make_shared<std::vector<double>>(yFor33);

	Bounds<2> minBounds{ 1,1 };
	Bounds<2> maxBounds{ 3,3 };
	model linmodel = modelOfLine;
	ErrorModel errormodel = chi2;;
	SimplexFigure<3> simplexfigure{ minBounds,maxBounds };
};
TEST_F(TestignSettingAndExecutingModel, checkingErrorModel)
{
	std::vector<double> trueErrorValues{ 22.5,	22.5,	202.5};
	simplexfigure.setModels(linmodel, errormodel);
	simplexfigure.setMotherCharacteristic(trueYVectorPointer);
	simplexfigure.setArgumentsToCalculatingData(xVectorPointer);

	simplexfigure.calculateErrors(); //! <- later on probably private, from API will be avalialbe sort method
	for (int i = 0; i < 3; i++)
	{
		double calculatedError = simplexfigure[i].getError();
		EXPECT_DOUBLE_EQ(calculatedError, trueErrorValues[i],0.1);
	}
};
//TEST_F(TestignSettingAndExecutingModel, checkingDataModel) {};
//TEST_F(TestignSettingAndExecutingModel, checkingSortingVertex) {};
//TODO: create tests for checking exeption mother characteristic no setted and arguments to calculating child characteristic
TEST_F(TestignSettingAndExecutingModel, testingSorting) 
{
	//TODO task for later, add test when each point has seperate value 
	
	simplexfigure.setModels(linmodel, errormodel);
	simplexfigure.setMotherCharacteristic(trueYVectorPointer);
	simplexfigure.setArgumentsToCalculatingData(xVectorPointer);

	simplexfigure.calculateErrors();
	simplexfigure.sort(true);
	double trueSortedOrderCoefficient[3] = {3,2,1};
	
	for (int i = 0; i < 3; i++)
	{
		auto p = trueSortedOrderCoefficient[i];
		SimplexPoint<2> truePoint{ p,p };
		EXPECT_EQ(simplexfigure[i], truePoint);
	}


};

struct TestingSimpleOperationOnSimplexFigure :public testing::Test{
	std::vector<double> xVector{ 1, 2, 3, 4, 5 };
	SimplexPoint<2> truePoint{ 1.5, 1.5 };
	std::vector<double> yVector{ 3, 4.5, 6, 7.5, 9 };
	vectorPointer xVectorPointer = std::make_unique<std::vector<double>>(xVector);
	vectorPointer trueYVectorPointer = std::make_unique<std::vector<double>>(yVector);

	Bounds<2> minBounds{ 1, 1 };
	Bounds<2> maxBounds{ 3, 3 };
	model linmodel = modelOfLine;
	ErrorModel errormodel = chi2;
	SimplexFigure<3> simplexFigure{ minBounds, maxBounds };
	
	void SetUp()  
	{
		simplexFigure.setModels(linmodel, errormodel);
		simplexFigure.setMotherCharacteristic(trueYVectorPointer);
		simplexFigure.setArgumentsToCalculatingData(xVectorPointer);
		simplexFigure.calculateErrors();
	}
};
TEST_F(TestingSimpleOperationOnSimplexFigure, testingAddingPointIntoSimplex) 
{
	SimplexPoint<2> pointToAdd{ 1.5,1.5 };
	simplexFigure.addPoint(pointToAdd);
	
	EXPECT_EQ(pointToAdd, simplexFigure[0]);

}
TEST_F(TestingSimpleOperationOnSimplexFigure, TestingReflection)
{
	SetUp();
	SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
	SimplexPoint<2> trueReflectedPoint{};
	EXPECT_EQ(reflectedPoint, trueReflectedPoint);

};
TEST_F(TestingSimpleOperationOnSimplexFigure, TestingExpansion)
{
	SetUp();
	SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
	simplexFigure.addPoint(reflectedPoint);
	SimplexPoint<2> expanedPoint = simplexFigure.expand();
	SimplexPoint<2> trueExpanedPoint{};
	EXPECT_EQ(expanedPoint, trueExpanedPoint);
};

TEST_F(TestingSimpleOperationOnSimplexFigure, TestingContraction)
{
	SetUp();
	SimplexPoint<2> reflectedPoint = simplexFigure.reflect();
	simplexFigure.addPoint(reflectedPoint);
	SimplexPoint<2> contractedPoint = simplexFigure.contract();
	SimplexPoint<2> trueContractedPoint{};
	EXPECT_EQ(contractedPoint, trueContractedPoint);
};

TEST_F(TestingSimpleOperationOnSimplexFigure, TestingShrinking)
{
	SetUp();
	std::array<SimplexPoint<2>, 2> shrikendPoints = simplexFigure.shrink();
	std::array<SimplexPoint<2>, 2> trueShrinkedPoint{};
	for (int i = 0; i < 2;i++)
		EXPECT_EQ(shrikendPoints[i], trueShrinkedPoint[i]);
};
}
		

