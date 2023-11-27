#pragma once

#include "SIMPLEXFIGURE.HPP"

namespace NumericStorm 
{
namespace Fitting 
{
class NoSettedModelExeption :public std::exception {

public:
	NoSettedModelExeption(bool dataModel,bool errorModel) 
		{createMessage(dataModel, errorModel);};
	~NoSettedModelExeption() {};
	const char* what() const noexcept override { return m_message.c_str(); }
private:
	std::string m_message;
	void createMessage(bool dataModel, bool errorModel)
	{

		std::string d = dataModel ?  "" : "Data ";
		std::string a = (dataModel && errorModel) ? "": "and ";
		std::string e = errorModel ? "" :"Error ";
		m_message += d + a + e + "no setted model";
		
	}
};
}
}