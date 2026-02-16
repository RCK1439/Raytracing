#pragma once

#include "Core/Types.hpp"

#include <ostream>
#include <string>
#include <sstream>

namespace rt {

enum class RendererErrorType : u8
{
    FAILED_TO_SAVE_IMAGE,
};

struct RendererError
{
public:
    RendererErrorType Type{};
    std::string       ImagePath{};

public:
    constexpr RendererError(RendererErrorType type, std::string_view path) :
        Type(type), ImagePath(path) {};
};

std::ostream& operator<<(std::ostream& stream, const RendererError& err);

}

template<>
struct std::formatter<rt::RendererError>
{
    constexpr auto parse(std::format_parse_context& ctx) const
    {
        return ctx.begin();
    }

    auto format(const rt::RendererError& err, std::format_context& ctx) const
    {
        std::stringstream stream;
        stream << err;

        return std::format_to(ctx.out(), "{}", stream.str());
    }
};