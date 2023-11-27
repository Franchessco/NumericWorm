#pragma once

#include "SimplexPoint.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
    template<size_t s_p, typename T_p = double, typename T_d = double,size_t s_b = s_p-1>
    class SimplexFigure
    {
    public:
        using SimplexPoint = SimplexPoint<s_b, T_p, T_d>;
        SimplexFigure(Bounds<s_b, T_p> minBounds, Bounds<s_b, T_p> maxBounds)
        {
            SimplexPoint step = (maxBounds - minBounds)/s_b;
            for (int i = 0; i <= s_b; i++)
                m_points[i] = minBounds + step * i;

            m_centroid = calculateCentroid();
        }
        std::array<SimplexPoint, s_p> getPoints() { return m_points; }

        SimplexPoint& operator[](int index)
        {
            if (index >= s_p) { return m_points[0]; }
            return m_points[index];
        }

        SimplexPoint getCentroid() 
        {
            if (m_centroid != nullptr)
                m_centroid = calculateCentroid();
            return m_centroid;
            
        }
    private:
        std::array<SimplexPoint, s_p> m_points;
        SimplexPoint m_centroid;
    private:
        SimplexPoint calculateCentroid() 
        {
            SimplexPoint centroid;
            return centroid;
        };


    };

}
}