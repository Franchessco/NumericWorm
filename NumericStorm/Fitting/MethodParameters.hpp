#pragma once

#include <vector>
namespace NumericStorm 
{
namespace Fitting 
{
template<typename T = double>
class MethodParameters {
public:
    MethodParameters(std::vector<T> methodParameters)
        : m_methodParameters(methodParameters) {}        
    template<class... Args>
    MethodParameters(Args... args)
        : m_methodParameters{ static_cast<T>(args)... } {}

    protected:
        std::vector<T> m_methodParameters;
    };

}
}

