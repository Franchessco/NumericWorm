#include "Application.hpp"
#include <iostream>
#include "NumericStorm.hpp"



using namespace NumericStorm::Fitting;
using const_vector = const std::vector<double>;
using vector_shared = std::shared_ptr< std::vector<double>>;
using const_shared_vector = std::shared_ptr<const_vector>;
using vectorPointer = std::shared_ptr < std::vector < double >>;

using model = std::vector<double>(*)(vectorPointer args, Parameters<4> param);
using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);
using SimplexPointType = SimplexPoint<4, double, double>;

void setX(std::vector<double>& vec, double min, int steps, double step)
{
	for (size_t i = 0; i < steps; i++)
		vec[i] += min + step * i;
};
class FittedAndMethodParameters {
public:
	FittedAndMethodParameters(SimplexPointType simplexParameters, SimplexFigureParameters methodParameters)
		: fittedParameters(simplexParameters), methodParameters(methodParameters) {}
	~FittedAndMethodParameters() {}

	SimplexPointType fittedParameters;
	SimplexFigureParameters methodParameters;

	std::string present() {
		std::string toReturn;
		toReturn += fittedParameters.presentParameters();

		// Convert double values to string before concatenating
		toReturn += "alpha: " + std::to_string(methodParameters.getAlpha());
		toReturn += "beta: " + std::to_string(methodParameters.getBeta());
		toReturn += "gamma: " + std::to_string(methodParameters.getGamma());
		toReturn += "delta: " + std::to_string(methodParameters.getDelta());

		return toReturn;
	}

	// Add less-than operator for sorting
	bool operator<(const FittedAndMethodParameters& other) const {
		
		return fittedParameters < other.fittedParameters; // Adjust as needed
	}
};




	double chi2(const vectorPointer mother, const std::vector<double>&child)
	{
		size_t s = child.size();
		std::vector <double> v; v.resize(s);

		for (size_t i = 0; i < s; i++)
		{
			auto y = (*mother)[i] - child[i];
			v[i] = std::pow(y, 2);
		}
		double error = std::accumulate(v.begin(), v.end(), 0.0);
		return error;
	};
	double myFantasticFunction(double x, Parameters<4> param){
		return param[0] * pow(x, 0) + param[1] * pow(x, 1) + param[2] * pow(x, 2) + param[3] * pow(x, 3);
	};
	std::vector <double> MyModel(vectorPointer x, Parameters<4> param){
		std::vector<double> output;
		output.resize(x->size());
		for (size_t i = 0; i < x->size(); i++)
			output[i] = myFantasticFunction(x->at(i), param);
		return output;
	};
int main()
{

	
	Bounds<4> minBounds{ 0,2,3,4};
	Bounds<4> maxBounds{ 3,3,3,4 };
	SimpleSimplex<5> simpleSimplexFitter(minBounds, maxBounds);

	// arguments to calculating data
	std::vector<double> myInputData;
	myInputData.resize(20);

	double currectX = 0.1; double step = 0.1;
	for (size_t i = 0; i < 20; i++)
	{
		myInputData[i] = currectX;
		currectX += step;
	}
	vectorPointer myInpuntData_ptr = std::make_shared<std::vector<double>>(myInputData);

	Parameters<4> trueParameters{ 1,2,3,4 };
	std::vector<double> trueData = MyModel(myInpuntData_ptr, trueParameters);
	vectorPointer trueData_ptr = std::make_shared<std::vector<double>>(trueData);
	model myModel = MyModel;
	// alpha 0<0.1<1
	// beta 0<0,1<1
	// gamma 1<0.1<2 
	// delta 0<0,1<1
	std::vector<FittedAndMethodParameters> allFittedPoints;
	//allFittedPoints.resize(9*9*9*9);
	//int iterations = 0;
	//for (double alpha = 0.1; alpha < 1.0; alpha += 0.1) {
	//	for (double beta = 0.1; beta < 1.0; beta += 0.1) {
	//		for (double gamma = 1.0; gamma < 2.0; gamma += 0.1) {
	//			for (double delta = 0.1; delta < 1.0; delta += 0.1) {

					SimplexFigureParameters mySimplexParameters{ 1,0.5 , 2, 0.5};
					simpleSimplexFitter.setUp(trueData_ptr, myInpuntData_ptr, myModel, chi2, mySimplexParameters);
					auto fittedParameters = simpleSimplexFitter.fit(0.0001, 100);
					auto someParameter = FittedAndMethodParameters(fittedParameters, mySimplexParameters);

					allFittedPoints.push_back(someParameter);
					//iterations++;

					//std::cout << "iterations: " << iterations << std::endl
					//	<< "alpha: " << alpha << std::endl
					//	<< "beta: " << beta << std::endl
					//	<< "gamma: " << gamma << std::endl
					//	<< "delta: " << delta << std::endl
					//	<< std::endl;
	//			}
	//		}
	//	}
	//}
					std::cout << fittedParameters.presentParameters() << "chi2:" << std::to_string(fittedParameters.getError()) << std::endl;
	//std::sort(allFittedPoints.begin(),allFittedPoints.end());
	//std::reverse(allFittedPoints.begin(), allFittedPoints.end());
	//for (int i = 0; i < 10; i++)
	//{
	//	std::cout << allFittedPoints[0].present() << std::endl;
	//}
	return 0;
}
