#pragma once

#include "SimplexPoint.hpp"
#include <algorithm>


namespace NumericStorm 
{
namespace Fitting 
{
    template<size_t s_p, typename T_p = double, typename T_d = double,size_t s_b = s_p-1>
    class SimplexFigure
    {
    public:
        using SimplexPointType = SimplexPoint<s_b, T_p, T_d>;
        using BoundsType = Bounds<s_b, T_p>;
        SimplexFigure(BoundsType minBounds, BoundsType maxBounds)
        {
            SimplexPointType step = (maxBounds - minBounds)/s_b;
            for (int i = 0; i <= s_b; i++)
                m_points[i] = minBounds + step * i;

            m_centroid = calculateCentroid();
        }
        std::array<SimplexPointType, s_p> getPoints() { return m_points; }

        SimplexPointType& operator[](int index)
        {
            if (index >= s_p) { return m_points[0]; }
            return m_points[index];
        }

        inline SimplexPointType getCentroid() {return m_centroid;}
        SimplexPointType calculateCentroid() 
        {
            SimplexPointType centroid;
            for (int i = 0; i <= s_b; i++)
                centroid += m_points[i];
            centroid /= s_p;
            return centroid;
        };
        void sort(bool reverseMinToMax = false)
        {
            std::sort(m_points.begin(), m_points.end());
            if (reverseMinToMax)
                std::reverse(m_points.begin(), m_points.end());
        }
    private:
        std::array<SimplexPointType, s_p> m_points;
        SimplexPointType m_centroid;
    
    };

}
}