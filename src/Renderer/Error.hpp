#pragma once

#include "Types.hpp"

#include "Error/BaseError.hpp"

namespace rt {

class RendererError final : public BaseError
{
public:
    enum class Type : u8
    {
        FAILED_TO_SAVE_IMAGE,
    };

public:
    RendererError(Type type, std::string_view detail) :
        m_Detail(detail), m_Type(type) {}

    std::string What() const override;

private:
    std::string m_Detail{};
    Type        m_Type{};
};

}
