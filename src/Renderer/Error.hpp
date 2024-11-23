#pragma once

#include "Error/BaseError.hpp"

namespace rt
{
    class RendererError final : public BaseError
    {
    public:
        enum class Type
        {
            FAILED_TO_SAVE_IMAGE,
        };

    public:
        RendererError(Type type, std::string_view detail) :
            m_Type(type), m_Detail(detail) {}

        std::string What() const override;

    private:
        Type m_Type;
        std::string m_Detail;
    };
}
