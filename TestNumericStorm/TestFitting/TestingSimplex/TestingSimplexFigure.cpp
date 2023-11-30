#include "pch.h"


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
		size_t s = (*x).size();
		std::vector<double> y; y.resize(s);
		for (size_t i = 0; i < s; ++i)
			y[i] = arguments[0] * (*x)[i] + arguments[1];
		return y;
	}

	double chi2(const vectorPointer mother, const std::vector<double>& child)
	{
		size_t s = child.size();
		std::vector <double> v; v.resize(s);

		for (size_t i = 0; i < s; i++)
			v[i] = std::pow(((*mother)[i] - child[i]), 2);
		double error = std::accumulate(v.begin(), v.end(), 0.0);
		return error;
	};

	using model = std::vector<double>(*)(vectorPointer args, Parameters<2> param);
	using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);
	
	struct TestignSettingAndExecutingModel: public testing::Test 
	{
		//std::vector<double> xVector{1,2,3,4,5};
		//std::vector<double> yVector{ 1,2,3,4,5 };
	
		Bounds<2> minBounds{1,1};
		Bounds<2> maxBounds{2,2};
		model linmodel = modelOfLine;
		ErrorModel errormodel = chi2;;

		SimplexFigure<3> simplexFigure{ minBounds,maxBounds };
		//vectorPointer xVectorShared = std::make_unique<std::vector<double>>(xVector);
		//vectorPointer yVectorShared = std::make_unique<std::vector<double>>(yVector);
	};

TEST_F(TestignSettingAndExecutingModel, TestThrowErrorTwoModelsNotSetted) 
{
	try 
	{simplexFigure.sort();}
	catch (const std::exception& e) 
	{
		std::string messege = static_cast<std::string>(e.what());
		EXPECT_STREQ("Data and Error no setted model", e.what());
	}
}
TEST_F(TestignSettingAndExecutingModel, TestThrowErrorModelsNotSetted)
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

TEST_F(TestignSettingAndExecutingModel, TestThrowErrorDataModelsNotSetted)
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

}
		//TODO add test for all possible error messages 

