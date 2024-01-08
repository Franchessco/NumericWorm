#include "pch.h"
//using namespace NumericStorm::Fitting;
//namespace TestingFitting 
//{
//
//using const_vector = const std::vector<double>;
//using vector_shared = std::shared_ptr< std::vector<double>>;
//using const_shared_vector = std::shared_ptr<const_vector>;
//using vectorPointer = std::shared_ptr < std::vector < double >> ;
//
//using model = std::vector<double>(*)(vectorPointer args, Parameters<4> param);
//using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);
//using SimplexPointType = SimplexPoint<4,double,double>;
//
//double chi2(const vectorPointer mother, const std::vector<double>& child)
//{
//	size_t s = child.size();
//	std::vector <double> v; v.resize(s);
//
//	for (size_t i = 0; i < s; i++)
//	{
//		auto y = (*mother)[i] - child[i];
//		v[i] = std::pow(y, 2);
//	}
//	double error = std::accumulate(v.begin(), v.end(), 0.0);
//	return error;
//};
//double myFantasticFunction(double x,Parameters<4> param) 
//{
//	return param[0]*pow(x,0 ) + param[1]*pow(x, 1) + param[2]*pow(x, 2) + param[3]*pow(x, 3);
//}
//std::vector <double> MyModel(vectorPointer x, Parameters<4> param) 
//{
//	std::vector<double> output;
//	output.resize(x->size());
//	for (size_t i = 0; i < x->size(); i++)
//		output[i] = myFantasticFunction(x->at(i), param);
//	return output;
//}
//TEST(TestFitFunction, FitFunction) 
//{
//	Bounds<4> minBounds{ -5,-5,-5,-5 };
//	Bounds<4> maxBounds{ 20,20,20,20 };
//	SimpleSimplex<5> simpleSimplexFitter(minBounds,maxBounds);
//
//	// arguments to calculating data
//	std::vector<double> myInputData;
//	myInputData.resize(200);
//
//	double currectX = -10; double step = 0.5;
//	for (size_t i = 0; i < 200; i++)
//	{
//		myInputData[i] = currectX;
//		currectX += step;
//	}
//	vectorPointer myInpuntData_ptr = std::make_shared<std::vector<double>>(myInputData);
//
//	Parameters<4> trueParameters{1,2,3,4};
//	std::vector<double> trueData = MyModel(myInpuntData_ptr, trueParameters);
//	vectorPointer trueData_ptr = std::make_shared<std::vector<double>>(trueData);
//	model myModel = MyModel;
//	SimplexFigureParameters mySimplexParameters{1,0.5,2,0.5};
//	simpleSimplexFitter.setUp(trueData_ptr, myInpuntData_ptr, myModel, chi2, mySimplexParameters);
//
//	auto fittedParameters = simpleSimplexFitter.fit(0.1, 10000);
//	for (size_t i = 0; i < 4; ++i) {
//		EXPECT_NEAR(fittedParameters[i], trueParameters[i], 0.1);
//	}
//}
//}