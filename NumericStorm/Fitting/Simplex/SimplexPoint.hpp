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
        :Parameters<s_p,T_p>(parameters), m_error(0), m_model(nullptr),  m_errorModel(nullptr) {};
    SimplexPoint<s_p, T_p, T_d>(const SimplexPoint<s_p, T_p, T_d>& other)
    :Parameters<s_p, T_p>(other.getParameters())
    {
        m_error = *&other.m_error;
        m_model = *&other.m_model;
        m_errorModel = *&other.m_errorModel;
    }

    //template <typename T_d=double>

    using vectorPointer = std::shared_ptr<std::vector<T_d>>;

    using model = std::vector<T_d>(*)(vectorPointer args, Parameters<s_p, T_p>param);
    using ErrorModel = double(*)(vectorPointer mother, const std::vector<T_d>& child);
    
private:
    double m_error;
    model m_model;
    ErrorModel m_errorModel;

public:
    std::vector<T_d> calculateData( vectorPointer arguments)
    {return m_model(arguments, this->m_parameters);}

    void calculateError(vectorPointer mother, const std::vector<double>& child) 
    {
        double error = m_errorModel(mother, child);
        this->m_error = error;
    }
    inline void setDataModel(model modelToSet) { m_model = modelToSet; }
    inline void setErrorModel(ErrorModel modelToSet) { m_errorModel = modelToSet; }
    inline double getError()const 
        { 
            return m_error; 
        }

    void setToBounds(const Bounds<s_p, T_p> minBounds, const Bounds<s_p, T_p> maxBounds)
        {
            setToMinBounds(minBounds);
            setToMaxBounds(maxBounds);
        }

    auto operator <=> (const SimplexPoint<s_p, T_p, T_d>& other) const 
            {return m_error <=> other.m_error;}
    SimplexPoint<s_p, T_p, T_d>& operator = (Parameters<s_p, T_p>& other ) 
    {
        if (this == other) return *this;

        for (size_t i = 0; i < s_p; i++)
            *this -> m_parameters[i] += other[i];
        //TODO make this more clear -> write getters for this function pointer
        setDataModel(other.m_model);
        setErrorModel(other.m_errorModel);
        return *this;
    }
    ErrorModel getErrorModel()const  { return m_errorModel; }
    model getDataModel()const { return m_model; }
    SimplexPoint<s_p,T_p,T_d>& operator = (const SimplexPoint<s_p,T_p,T_d>& other) 
    {
        if (this == &other)
            return *this;
        this->m_parameters = other.getParameters();
        m_error = other.getError();
        this -> m_model = other.getDataModel();
        this -> m_errorModel = other.getErrorModel();
        return *this;
    }
private:
    void setToMinBounds(const Bounds<s_p, T_p> minBounds)
        {
            for (size_t i = 0; i < s_p; i++)
                if (this->m_parameters[i] < minBounds[i])
                    this->m_parameters[i] = minBounds[i];
        }
    void setToMaxBounds(const Bounds<s_p, T_p> maxBounds)
        {
            for (size_t i = 0; i < s_p; i++)
                if (this->m_parameters[i] > maxBounds[i])
                    this->m_parameters[i] = maxBounds[i];
        }
    };
    }
}