#pragma once

#include "Core/Types.hpp"

#include <filesystem>
#include <ostream>
#include <sstream>

namespace RTIAW {

enum class RendererErrorType : u8
{
    FAILED_TO_SAVE_IMAGE,
};

struct RendererError
{
public:
    std::filesystem::path OutputPath{};
    RendererErrorType     Type{};

public:
    constexpr RendererError(RendererErrorType type, std::filesystem::path path) :
        OutputPath(path), Type(type) {};
};

std::ostream& operator<<(std::ostream& stream, const RendererError& err);

}

template<>
struct std::formatter<RTIAW::RendererError>
{
    constexpr auto parse(std::format_parse_context& ctx) const
    {
        return ctx.begin();
    }

    auto format(const RTIAW::RendererError& err, std::format_context& ctx) const
    {
        std::stringstream stream;
        stream << err;

        return std::format_to(ctx.out(), "{}", stream.str());
    }
};