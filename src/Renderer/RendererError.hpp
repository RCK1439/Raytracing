#pragma once

#include "Core/Types.hpp"

#include <filesystem>
#include <ostream>
#include <sstream>
#include <variant>

namespace RTIAW {

enum class RendererErrorType : u8
{
    FAILED_TO_SAVE_IMAGE,
};

struct RendererError
{
public:
    constexpr RendererError(RendererErrorType type, const std::filesystem::path& path) :
        Args(path), Type(type) {};

private:
    std::variant<std::filesystem::path> Args{};
    RendererErrorType                   Type{};
    
    friend std::ostream& operator<<(std::ostream& stream, const RendererError& err);
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