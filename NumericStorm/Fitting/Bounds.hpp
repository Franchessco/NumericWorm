#pragma once
#include "Parameters.hpp"

namespace NumericStorm
{
    namespace Fitting
    {
        template<size_t s_p, typename T_p = double>
        class Bounds : public Parameters<s_p, T_p> {
        public:
            template<class ... Args>
            Bounds(Args... args)
                :Parameters<s_p, T_p>(args...) {}

            Bounds(std::array<T_p, s_p> parameters)
                :Parameters<s_p, T_p>(parameters) {}

        };
    }
}