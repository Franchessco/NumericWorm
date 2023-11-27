#pragma once

#include <numeric>
#include <vector>


#include "../Bounds.hpp"

namespace NumericStorm
{
namespace Fitting {

template < size_t s_p, typename T_p = double, typename T_d = double>
class SimplexPoint :public Parameters<s_p, T_p>
{
public:
    template<class ... Args>
    SimplexPoint<s_p, T_p, T_d>(Args ...args)
        :Parameters<s_p, T_p>(args...), m_error(0), m_model(nullptr), m_errorModel(nullptr) {};

    SimplexPoint<s_p, T_p, T_d>(std::array<T_p, s_p> parameters)
        :Parameters<T_p, s_p>(parameters), m_error(0), m_model(nullptr), m_errorModel(nullptr) {};


    //template <typename T_d=double>
    std::vector<T_d> calculateData(std::vector<T_d> arguments)
    {return m_model(arguments, this->m_parameters);}

    double calculateError(const std::vector<double>& mother, const std::vector<double>& child) 
    { return m_errorModel(mother, child); }

    using DataModel = std::vector<T_d>(*)(std::vector<T_d>& args, Parameters<s_p, T_p>param);
    using ErrorModel = double(*)(const std::vector<T_d>& mother, const std::vector<T_d>& child);
private:
    double m_error;
    DataModel m_model;
    ErrorModel m_errorModel;

    public:
        inline void setDataModel(DataModel modelToSet) { m_model = modelToSet; }
        inline void setErrorModel(ErrorModel modelToSet) { m_errorModel = modelToSet; }
        inline double getError() { return m_error; }

        void setToBounds(const Bounds<s_p, T_p> minBounds, const Bounds<s_p, T_p> maxBounds)
        {
            setToMinBounds(minBounds);
            setToMaxBounds(maxBounds);
        }

        auto operator <=> (const SimplexPoint<s_p, T_p, T_d>& other) const 
            {return m_error <=> other.m_error;}
    private:
        void setToMinBounds(const Bounds<s_p, T_p> minBounds)
        {
            for (int i = 0; i < s_p; i++)
                if (this->m_parameters[i] < minBounds[i])
                    this->m_parameters[i] = minBounds[i];
        }
        void setToMaxBounds(const Bounds<s_p, T_p> maxBounds)
        {
            for (int i = 0; i < s_p; i++)
                if (this->m_parameters[i] > maxBounds[i])
                    this->m_parameters[i] = maxBounds[i];
        }
    };
    }
}