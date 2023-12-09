#pragma once
#include <string>
#include <stdexcept>
namespace NumericStorm
{
namespace Fitting
{

class MotherCharacteristicNoSettedExeption :public std::exception {
	public:
		MotherCharacteristicNoSettedExeption()
			:m_message("Mother characterisitc is no setted! \n Please do it using setMotherCharacteristic function and pass shared pointer to vector of mother characteristic") {};
		const char* what() const noexcept override  {return m_message.c_str();}

	private:
	std::string m_message;
};
}
}