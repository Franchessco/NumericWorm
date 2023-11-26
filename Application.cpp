#include "Application.hpp"
void setX(std::vector<double>& vec, double min, int steps, double step);


std::vector<double> GaussianModel(const std::vector<double>& x, NumericStorm::Fitting::Parameters<4> param);
int main()
{
	using namespace NumericStorm::Fitting;
	std::vector<double>v1(200);
	setX(v1, 0, 200, 0.1);
	
					//   mu,   sigma, A, c
	Bounds<4> trueBounds{4.5, 1.5,  5, 2};

	Bounds<4> minBounds{1,1,1,1};
	Bounds<4> maxBounds{ 8,8,8,8 };

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

std::vector<double> GaussianModel(const std::vector<double> x, NumericStorm::Fitting::Parameters<4> param) 
{
	size_t size = x.size();
	std::vector<double> result(size);
	for (int i = 0; i < size; i++)
	{
		double new_x = pow( ( (x[i] - param[0]) / param[1]),2);
		result[i] = param[2] * exp(new_x) + param[3];
	}

	return result;
}