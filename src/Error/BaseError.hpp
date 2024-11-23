#pragma once

#include <string>

class BaseError
{
public:
    virtual ~BaseError() = default;

    virtual std::string What() const = 0;
};
