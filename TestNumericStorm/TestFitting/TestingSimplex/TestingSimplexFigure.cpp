#include "pch.h"


namespace TestingSimplexFigure
{
	using namespace NumericStorm::Fitting;

struct CreatingSimplexFigure : public testing::Test
{
	Bounds<3> minBounds{ 1, 1, 1 };
	Bounds<3> maxBounds{ 5,5,5 };
	
};
TEST_F(CreatingSimplexFigure, CreatingSimplexFigure)
{
	SimplexFigure<4> simplexfigure( minBounds, maxBounds );

	EXPECT_EQ(simplexfigure[0],minBounds);
	EXPECT_EQ(simplexfigure[3],maxBounds);
}
struct SimplexOperation :public testing::Test 
{
	Bounds<2> minBounds{ 1,1 };
	Bounds<2> maxBounds{ 3,3 };
	SimplexPoint<2> trueCentroid{ 2,2 };

	SimplexFigure<3> simplexfigure = SimplexFigure<3>(minBounds, maxBounds);
};
TEST_F(SimplexOperation, calculatingCentroid) 
{
	SimplexPoint<2> centroid = simplexfigure.getCentroid();
	for (int i = 0; i <2;i++)
		EXPECT_EQ(centroid[i], trueCentroid[i]);

};
}