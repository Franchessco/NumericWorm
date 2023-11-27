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

	using DataModel = std::vector<double>(*)(const vectorPointer args, Parameters<2>param);
	using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);
	struct TestignSettingAndExecutingModel: public testing::Test 
	{
		Bounds<2> minBounds{1,1};
		Bounds<2> maxBounds{2,2};

		SimplexFigure<3> simplexFigure{ minBounds,maxBounds };

	};

TEST_F(TestignSettingAndExecutingModel, TestThrowError) {

	try 
	{simplexFigure.sort();}
	catch (const std::exception& e) {
		std::string messege = static_cast<std::string>(e.what());
		EXPECT_STREQ("Data and Error no setted model", e.what());
		//TODO add test for all possible error messages 
	}
}
}

