#include "pch.h"
#include "NumericStorm.hpp"

namespace TestingData {

using namespace NumericStorm;

struct TestData :public testing::Test
{


};


struct CreatingData:public testing::Test
{

	using const_vector = const std::vector<double>;
	using vector_shared = std::shared_ptr< std::vector<double>>;
	using const_shared_vector = std::shared_ptr<const_vector>;

	const_vector v{1,2,3,4,5,6};
	const_vector v2{7,8,9};

	const_shared_vector pv_1 = std::make_shared<const_vector>(v);
	const_shared_vector pv_2 = std::make_shared<const_vector>(v2);

	//vector_shared pv_2 = std::make_shared<std::vector<double>>();

};
TEST(CreatingData, CreatingBasedOnArray)
{
	std::vector<double> t1{ 1,2,3,4,5,6 };
	std::vector<double> t2{ 7,8,9 };

	//Data<double> d1(t1,t2);
	//
	//auto& data_x = d1.getX();
	//auto& data_y = d1.getY();
	//EXPECT_EQ(data_x, t1);
	//EXPECT_EQ(data_y, t2);
};
TEST(CreatingData, CreatingBasedOnArgs) {};

//TEST_F(TestData, GetData) {};
//TEST_F(TestData, Constdata) {};
//TEST_F(TestData, IteratingThroughData) {};

}

