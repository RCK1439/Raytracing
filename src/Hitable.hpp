#pragma once

#include "Types.hpp"

namespace rt
{
    class Hitable
    {
    public: 
        virtual bool Hit(const Ray& ray) const = 0;
    };
} // namespace rt
