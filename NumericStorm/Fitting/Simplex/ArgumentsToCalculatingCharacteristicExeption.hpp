#pragma once
#include <stdexcept>
#include <string>
#include <memory>
namespace NumericStorm
{
namespace Fitting
{
class ArgumentsToCalculatingCharacteristicExeption : public std::exception {
public:
	ArgumentsToCalculatingCharacteristicExeption()
		:m_message("Set arguments to calculating characteristics1") {};
	const char* what() const noexcept override { return m_message.c_str(); }
private:
	std::string m_message;
};


}
}