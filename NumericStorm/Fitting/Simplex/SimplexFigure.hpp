#pragma once

#include <algorithm>

#include "SimplexPoint.hpp"
#include "NoSettedModelExeption.hpp"

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
    using vectorPointer = std::shared_ptr<std::vector<T_d>>;

    using model = std::vector<double>(*)(vectorPointer args, Parameters<2> param);
    using ErrorModel = double(*)(const vectorPointer mother, const std::vector<double>& child);

    SimplexFigure(BoundsType minBounds, BoundsType maxBounds)
        {
            SimplexPointType step = (maxBounds - minBounds)/s_b;
            for (int i = 0; i <= s_b; i++)
                m_points[i] = minBounds + step * i;

            m_centroid = calculateCentroid();
            m_motherCharacteristicPtr = nullptr;
            m_dataModelSet = false;
            m_errorModelSet = false;

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
        if (m_dataModelSet == false || m_errorModelSet == false)
            throw NoSettedModelExeption(m_dataModelSet,m_errorModelSet);
        
        std::sort(m_points.begin(), m_points.end());
        if (reverseMinToMax)
            std::reverse(m_points.begin(), m_points.end());
        }

    void setMotherCharacteristic(vectorPointer motherCharacterisitcPtr) 
        {m_motherCharacteristicPtr = motherCharacterisitcPtr;}
    void setArgumentsToCalculatingData(vectorPointer argumentsToCalculatingModel) 
        {m_argumentsToCalculatingCharacteristic = argumentsToCalculatingModel;}
    void setModels(model dataModel, ErrorModel errorModel) 
    {
        setDataModel(dataModel); setErrorModel(errorModel); 
        m_dataModelSet = true; m_errorModelSet = true;
    }
    void setDataModel(model modelToSet) 
    {
        for(int i=0; i <s_p;i++)
            m_points[i].setDataModel(modelToSet);
        m_dataModelSet = true;
    }
    void setErrorModel(ErrorModel modelToSet) 
    {
        for (int i = 0; i < s_p; i++)
            m_points[i].setErrorModel(modelToSet);
        m_errorModelSet = true;
    }
private:
    std::array<SimplexPointType, s_p> m_points;
    SimplexPointType m_centroid;
    vectorPointer m_motherCharacteristicPtr;
    vectorPointer m_argumentsToCalculatingCharacteristic;
    bool m_dataModelSet;
    bool m_errorModelSet;

    };

}
}