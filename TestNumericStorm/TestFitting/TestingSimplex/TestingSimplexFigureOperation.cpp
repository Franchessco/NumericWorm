#include "pch.h"
using namespace NumericStorm::Fitting;

namespace TestingOperationOnSimplexFigure {

struct SimplexFigureOperation :public testing::Test
{
	Bounds<2> minBounds{ 1,1 };
	Bounds<2> maxBounds{ 3,3 };
	SimplexPoint<2> trueCentroid{ 2,2 };

	SimplexFigure<3> simplexFigure = SimplexFigure<3>(minBounds, maxBounds);
};
TEST_F(SimplexFigureOperation, calculatingCentroid)
{
	SimplexPoint<2> centroid = simplexFigure.getCentroid();
	for (int i = 0; i < 2; i++)
		EXPECT_EQ(centroid[i], trueCentroid[i]);
};
TEST_F(SimplexFigureOperation, sortingPoints)
{
	simplexFigure.sort();

};
TEST_F(SimplexFigureOperation, reflectionWorstPoint)
{
};
TEST_F(SimplexFigureOperation, expantionWorstPoint)
{
};
TEST_F(SimplexFigureOperation, contractionWorstPoint)
{
};
TEST_F(SimplexFigureOperation, shrinkingPoints)
{
};
}
