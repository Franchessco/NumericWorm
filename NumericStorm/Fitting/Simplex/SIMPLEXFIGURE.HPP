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

    using DataModel = std::vector<T_d>(*)(std::vector<T_d>& args, Parameters<s_p, T_p>param);
    using ErrorModel = double(*)(const vectorPointer mother, const std::vector<T_d>& child);


    SimplexFigure(BoundsType minBounds, BoundsType maxBounds)
        {
            SimplexPointType step = (maxBounds - minBounds)/s_b;
            for (int i = 0; i <= s_b; i++)
                m_points[i] = minBounds + step * i;

            m_centroid = calculateCentroid();
            m_motherCharacteristicPtr = nullptr;
            dataModelSet = false;
            errorModelSet = false;

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
        if (dataModelSet == false || errorModelSet == false)
            throw NoSettedModelExeption(dataModelSet,errorModelSet);
        
        std::sort(m_points.begin(), m_points.end());
        if (reverseMinToMax)
            std::reverse(m_points.begin(), m_points.end());
        }

    void setMotherCharacteristic(vectorPointer motherCharacterisitcPtr) 
        {m_motherCharacteristicPtr = motherCharacterisitcPtr;}
    void setArgumentsToCalculatingData(vectorPointer argumentsToCalculatingModel) 
        {m_argumentsToCalculatingCharacteristic = argumentsToCalculatingModel;}
    void setModels(DataModel dataModel, ErrorModel errorModel) 
    {
        setDataModel(dataModel); setErrorModel(errorModel); 
        dataModelSet = true; errorModelSet = true;
    }
private:
    void setDataModel(DataModel modelToSet) 
    {
        for(int i=0; i <s_p;i++)
            m_points[i].setDataModel(modelToSet);
    }
    void setErrorModel(ErrorModel modelToSet) 
    {
        for (int i = 0; i < s_p; i++)
            m_points[i].setErrorModel(modelToSet);
    }
    std::array<SimplexPointType, s_p> m_points;
    SimplexPointType m_centroid;
    vectorPointer m_motherCharacteristicPtr;
    vectorPointer m_argumentsToCalculatingCharacteristic;
    bool dataModelSet;
    bool errorModelSet;

    };

}
}