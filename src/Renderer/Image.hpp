#pragma once

#include "RendererError.hpp"

#include "Core/Buffer.hpp"
#include "Core/Types.hpp"

#include <filesystem>
#include <glm/vec4.hpp>

namespace RTIAW {

class Image final
{
public:
    constexpr Image() = default;
    constexpr Image(u32 width, u32 height) :
        m_Data(width * height), m_Width(width), m_Height(height) {}

    inline constexpr u32 GetColor(u32 x, u32 y) const { return m_Data[x + y * m_Width]; }
    inline constexpr u32 GetWidth() const { return m_Width; }
    inline constexpr u32 GetHeight() const { return m_Height; }

    constexpr void SetColorHex(u32 x, u32 y, u32 color)
    {
        m_Data[x + y * m_Width] = color;
    }

    constexpr void SetColorRGBA(u32 x, u32 y, u8 r, u8 g, u8 b, u8 a)
    {
        const u32 color = (a << 24) | (b << 16) | (g << 8) | (r << 0);
        SetColorHex(x, y, color);
    }

    constexpr void SetColor(u32 x, u32 y, const glm::vec4& color)
    {
        const u8 r = static_cast<u8>(color.r * 255.0f);
        const u8 g = static_cast<u8>(color.g * 255.0f);
        const u8 b = static_cast<u8>(color.b * 255.0f);
        const u8 a = static_cast<u8>(color.a * 255.0f);
        SetColorRGBA(x, y, r, g, b, a); 
    }

    constexpr void Resize(u32 width, u32 height)
    {
        m_Data.Resize(width * height);
        m_Width = width;
        m_Height = height;
    }

    Result<void, RendererError> Save(std::filesystem::path path) const;

private:
    Buffer<u32> m_Data{};
    u32         m_Width{};
    u32         m_Height{};
};

}
