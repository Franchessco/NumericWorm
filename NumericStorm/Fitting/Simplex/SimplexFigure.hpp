#pragma once

#include "SimplexPoint.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
    template<size_t s_p, typename T_p = double,size_t s_b = s_p-1>
    class SimplexFigure
    {
    public:
        SimplexFigure(Bounds<s_b, T_p> minBounds, Bounds<s_b, T_p> maxBounds)
        {
            
            Parameters<s_p - 1, T_p> factors = (maxBounds - minBounds) / s_p;
            
            for (size_t i = 0; i <= s_p-1; ++i)
                m_points[i] = minBounds+factors/2 + factors * i;
            
        }
        std::array<SimplexPoint<s_p, T_p>, s_p> getPoints() { return m_points; }
        SimplexPoint<s_p-1,T_p>& operator[](int index)
        {
            if (index >= s_p) { return m_points[0]; }
            return m_points[index];
        }
    private:
        std::array<SimplexPoint<s_p-1, T_p>, s_p> m_points;

    };

}
}