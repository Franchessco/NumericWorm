#pragma once
#include <string>
#include <stdexcept>
namespace NumericStorm 
{
namespace Fitting 
{

class ArgumentsToCalculatingCharacteristicNoSettedExeption :public std::exception{
public:
	ArgumentsToCalculatingCharacteristicNoSettedExeption() 
		:m_message("Arguments to caclucating characteristic is no setted! \n Please do it using setArgumentsToCalculatingData() function and pass shared pointer to vector of arguments") {};
	const char* what() const noexcept override 
		{return m_message.c_str();}
private:
	std::string m_message;
};
}
}