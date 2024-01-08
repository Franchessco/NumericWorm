#pragma once

#include <algorithm>

#include "SimplexPoint.hpp"
#include "NoSettedModelExeption.hpp"
#include "SimplexParameters.hpp"
#include "../ArgumentsToCalculatingCharacteristicNoSettedExeption.hpp"
#include"../MotherCharacteristicNoSettedExeption.hpp"

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

    using model = std::vector<double>(*)(vectorPointer args, Parameters<s_b> param);
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
        SimplexPointType centroid{m_points[0]};
            for (int i = 1; i <= s_b; i++)
                centroid += m_points[i];
            centroid /= s_p;
            m_centroid = centroid;
            return centroid;
        };

    SimplexPointType mycomparator(const SimplexPointType& a, const SimplexPointType& b) const
    {
        if (a.getError() > b.getError())
            return a;
        else //if (a.getError() < b.getError())
            return b;
        //else
        //    return -1;
    }
    void sort(bool reverseMinToMax = false)
    {
        IsDataAndErrorModelSetted();
        calculateErrors();

        std::sort(m_points.begin(), m_points.end());
        if (reverseMinToMax)
            std::reverse(m_points.begin(), m_points.end());
        }
    void setModels(model dataModel, ErrorModel errorModel) 
    {
        setDataModel(dataModel); setErrorModel(errorModel); 
        m_dataModelSet = true; m_errorModelSet = true;
    }
    //TODO set dataModel and setErrorModel should be private!
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
    void setMotherCharacteristic(vectorPointer motherCharacterisitcPtr) 
        {m_motherCharacteristicPtr = motherCharacterisitcPtr;}
    void setArgumentsToCalculatingData(vectorPointer argumentsToCalculatingModel) 
        {m_argumentsToCalculatingCharacteristic = argumentsToCalculatingModel;}
    
    void calculateErrors()
    {
        IsArgumentsSetted();
        IsMotherCharateristicSetted();

        //TODO needed copy/move mother chaIsArgumentsSetted()racteristic, becase of performance and jumping on the memory
        for (auto& item:m_points)
        { 
            std::vector<T_d> characteristicByMyPoint = item.calculateData(m_argumentsToCalculatingCharacteristic);
            item.calculateError(m_motherCharacteristicPtr,characteristicByMyPoint);
        }
    }
    void addPoint(SimplexPointType pointToAdd) 
    {m_proposalPoint = pointToAdd;}

    SimplexPointType reflect() 
    { 
        SimplexPointType reflectedPoint{m_centroid};
        double alpha = m_simplexParameters.getAlpha();
        reflectedPoint += (m_centroid - m_points[0])* alpha;
        
        return reflectedPoint;
    };
    SimplexPointType expand() 
    { 
        SimplexPointType expandedPoint{ m_centroid };
        double gamma = m_simplexParameters.getGamma();
        expandedPoint += (m_proposalPoint - m_centroid) * gamma;

        return expandedPoint;
    };
    SimplexPointType contract()
    { 
        SimplexPointType pointToContraction = decidePointToContraction();
        SimplexPointType contractedPoint{ m_centroid };

        double beta = m_simplexParameters.getBeta();
        contractedPoint += (pointToContraction - m_centroid)*beta;

        return contractedPoint;
    };
    std::vector<SimplexPointType> shrink() 
    { 
        auto bestPoint = m_points[s_b];
        std::vector<SimplexPointType> shrinkedPoints;
        for (int i = 0; i < s_b; i++)
            shrinkedPoints.push_back(bestPoint);
        double delta = m_simplexParameters.getDelta();
        
        for (int i = 0; i < s_b ; i++)
        {
            auto p = (m_points[i] - bestPoint) * delta;
            shrinkedPoints[i] += p;
        }
            /*bestPoint + (m_points[i] - bestPoint)*delta;*/

        return shrinkedPoints;
    };
    void setSimplexParameters(SimplexFigureParameters newFigureParameters) { m_simplexParameters = newFigureParameters; }

    SimplexPointType decidePointToContraction()
    {
        if (m_proposalPoint < m_points[s_p-1])
            return m_proposalPoint;
        return m_points[s_p-1];
    }

    void doOperation(SimplexPointType expandedPoint, SimplexPointType contractedPoint) 
    {
        

        if (expantionDecision(expandedPoint))
            {m_points[0] = expandedPoint;return;}
        else if (contractionDecision())
            {m_points[0] = contractedPoint;return;}
        else
        {
            //TODO later on we need to change this code to be more readable, probably we want to use zip() funciton 
            std::vector<SimplexPointType> shrinkedPoints = shrink();
            for (int i = 0; i < s_b; i++)
                m_points[i] = shrinkedPoints[i];
        }
    }
private:
    std::array<SimplexPointType, s_p> m_points;
    SimplexPointType m_proposalPoint;
    SimplexPointType m_centroid;
    vectorPointer m_motherCharacteristicPtr;
    vectorPointer m_argumentsToCalculatingCharacteristic;
    bool m_dataModelSet;
    SimplexFigureParameters m_simplexParameters;
    bool m_errorModelSet;

    void IsDataAndErrorModelSetted()
    {
    if (m_dataModelSet == false || m_errorModelSet == false)
        throw NoSettedModelExeption(m_dataModelSet, m_errorModelSet);
    }
    void IsArgumentsSetted() 
    {
        if (m_argumentsToCalculatingCharacteristic == nullptr)
            throw ArgumentsToCalculatingCharacteristicNoSettedExeption();
    }
    void IsMotherCharateristicSetted() 
    {
        if (m_motherCharacteristicPtr == nullptr)
            throw MotherCharacteristicNoSettedExeption();
    }

    bool expantionDecision(SimplexPointType expandedPoint) 
    {
        bool firstCondition = (expandedPoint < m_proposalPoint) && (m_proposalPoint < m_points[s_p -1]);
        bool secondCondition = (expandedPoint<m_points[s_p-2]) && (m_proposalPoint < m_points[s_p-1]);
        return firstCondition || secondCondition;
    }
    bool contractionDecision()
    {
        if (m_proposalPoint >= m_points[s_p-2])
            return true;
        else
            return false;
    }
};

}
}