#include "pch.h"


namespace TestingSimplexFigure 
{
using namespace NumericStorm::Fitting;

struct CreatingSimplexFigure: public testing::Test 
{
	Bounds<3> minBounds{1, 1, 1};
	Bounds<3> maxBounds{ 5,5,5 };
};
TEST_F(CreatingSimplexFigure, CreatingSimplexFigure)
{
	SimplexFigure<4> simplexfigure(minBounds, maxBounds);

	bool b1 = simplexfigure[0] == minBounds+0.5;
	bool b2 = simplexfigure[3] == maxBounds-0.5;
	EXPECT_TRUE(b1);
	EXPECT_TRUE(b2);
}

}