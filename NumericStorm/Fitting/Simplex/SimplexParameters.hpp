#pragma once
#include "../MethodParameters.hpp"
namespace NumericStorm 
{
namespace Fitting 
{
class WrongLengthOfParametersException : public std::exception
{
public:
    WrongLengthOfParametersException( int newSize)
        : m_message("The size of new method parameters should have 4 elements") 
    {}

    const char* what() const noexcept override { return m_message.c_str(); }

private:
    std::string m_message;
};

    
class SimplexFigureParameters : public MethodParameters<double> {
public:
    SimplexFigureParameters(std::vector<double> parameters)
        : MethodParameters<double>(parameters) {}
    
    template<class... Args>
    SimplexFigureParameters(Args... args)
        : MethodParameters<double>(static_cast<double>(args)...) {}

    void setParameters(std::vector<double> newParameters) 
    {
    if (newParameters.size() != this->m_methodParameters.size())
        throw WrongLengthOfParametersException(newParameters.size());
    this->m_methodParameters = newParameters;
    }

       
    inline double getAlpha() const { return this->m_methodParameters[0]; }
    inline double getBeta() const { return this->m_methodParameters[1]; }
    inline double getGamma() const { return this->m_methodParameters[2]; }
    inline double getDelta() const { return this->m_methodParameters[3]; }
    };


}
}