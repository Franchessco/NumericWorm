#pragma once
#include "../SimplexFigure.hpp"
#include <fstream>
namespace NumericStorm 
{
namespace Fitting 
{

template<size_t s_p,typename T_p = double,typename T_d=double,size_t s_b=s_p-1>
class SimpleSimplex 
{
	using BoundsType = Bounds<s_b, T_p>;
	using SimplexFigureType = SimplexFigure<s_p, T_p, T_d, s_b>;
	using SimplexPointType = SimplexPoint<s_b, T_p, T_d>;

	using vectorPointer = std::shared_ptr<std::vector<T_d>>;

	using model = std::vector<double>(*)(vectorPointer args, Parameters<s_b> param);
	using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>&child);

public:
	SimpleSimplex(BoundsType minBounds,BoundsType maxBounds) 
		:simplexFigure(minBounds,maxBounds){};
	~SimpleSimplex() {};

	void setUp(vectorPointer motherCharacteristic, vectorPointer argumentsToCalculatingData, 
				model dataModel, ErrorModel errorModel,SimplexFigureParameters simplexParameters) 
	{
		simplexFigure.setMotherCharacteristic(motherCharacteristic);
		simplexFigure.setArgumentsToCalculatingData(argumentsToCalculatingData);
		simplexFigure.setModels(dataModel, errorModel);
		simplexFigure.setSimplexParameters(simplexParameters);
		simplexFigure.calculateErrors();
		simplexFigure.sort(true);
	}

	SimplexPointType fit(double maxError, unsigned int maxIterations)
	{
		double bestError = simplexFigure[s_p - 1].getError(); //TODO add dedicated method to getting the worst and best point
		unsigned int iterations = 0;
		///*SimplexPointType fittedParameters{};*/

		while (checkTerminationconditions(bestError, maxError, iterations, maxIterations)) 
		{
			simplexFigure.sort(true);
			simplexFigure.calculateCentroid();
			SimplexPointType reflectedPoint = simplexFigure.reflect();
			simplexFigure.addPoint(reflectedPoint);
			SimplexPointType expandedPoint = simplexFigure.expand();
			SimplexPointType contractedPoint = simplexFigure.contract();

			BoundsType minBounds = simplexFigure.getMinBoudns();
			BoundsType maxBounds = simplexFigure.getMaxBoudns();

			reflectedPoint.setToBounds(minBounds,maxBounds);
			expandedPoint.setToBounds(minBounds,maxBounds);
			contractedPoint.setToBounds(minBounds,maxBounds);
			simplexFigure.doOperation(expandedPoint,contractedPoint);
			simplexFigure.sort(true);
			bestError = simplexFigure[s_b].getError();
			
			//for (auto& item : simplexFigure.getPoints())
			//{
			//	std::cout << item.getError() << " ";
			//}

			//std::string vrtx = simplexFigure.present();
			//saveTextToFile(vrtx);

			iterations++;
		}
		SimplexPointType fittedParameters = simplexFigure[s_p - 1];
		return fittedParameters;
	}
private:
	SimplexFigureType simplexFigure;
	bool checkTerminationconditions(double bestError,double maxError, unsigned int iterations,unsigned int maxIterations)
	{
		bool firsCond = bestError < maxError;
		bool secondCond = iterations > maxIterations;
		return  !(firsCond or secondCond);
	}


	void saveTextToFile(const std::string& text) {
		// Create an output file stream
		std::ofstream outputFile("E:/STUDIA/Fizyka/3_SEMESTR/C++/Projekt/NumericWorm/NumericStorm/Fitting/Simplex/SimpleSimplex/Parameters.txt", std::ios::app);

		if (outputFile.is_open()) {
			outputFile << text<<std::endl;
			outputFile.close();
		}

	}
};

}
}