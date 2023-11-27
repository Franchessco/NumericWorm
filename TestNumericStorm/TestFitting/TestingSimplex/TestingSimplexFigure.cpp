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
}

