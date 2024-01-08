#include "Application.hpp"
#include <iostream>
void setX(std::vector<double>& vec, double min, int steps, double step);



int main()
{
	using namespace NumericStorm::Fitting;
	std::vector<double>v1(5);
	setX(v1, 0, 5, 1);
	//TODO add Data class 
	//		it should overload << operator -> reading data from file 	
					//   mu,   sigma, A, c
	Parameters<4> trueParameters{4.5, 1.5,  5, 2};

	Bounds<4> minBounds{1,1,1,1};
	Bounds<4> maxBounds{ 8,8,8,8 };
	for (auto x : v1)
		std::cout << x;
		

	//inicjalizacja UI
	
	//SimpleSimplex solver{};
	//solver.setModel(GaussianModel);
	//solver.fit();
	//std::cout << solver << std::endl;

	return 0;
}

void setX(std::vector<double>& vec, double min, int steps, double step)
{
	for (size_t i = 0; i < steps; i++)
		vec[i] += min + step * i;
};

