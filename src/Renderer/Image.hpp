#pragma once

#include "Types.hpp"

#include "Error.hpp"

#include <filesystem>
#include <glm/vec4.hpp>

#include <vector>

namespace rt {

class Image final
{
public:
    using MutIter = std::vector<u32>::iterator;
    using ConstIter = std::vector<u32>::const_iterator;

    using RevMutIter = std::vector<u32>::reverse_iterator;
    using RevConstIter = std::vector<u32>::const_reverse_iterator;

public:
    constexpr Image() = default;
    constexpr Image(u32 width, u32 height) :
        m_Data(width * height), m_Width(width), m_Height(height) {}

    inline constexpr u32 GetColor(u32 x, u32 y) const { return m_Data.at(x + y * m_Width); }
    inline constexpr u32 GetWidth() const { return m_Width; }
    inline constexpr u32 GetHeight() const { return m_Height; }

    inline constexpr MutIter begin() { return m_Data.begin(); }
    inline constexpr MutIter end() { return m_Data.end(); }
    inline constexpr ConstIter begin() const { return m_Data.begin(); }
    inline constexpr ConstIter end() const { return m_Data.end(); }

    inline constexpr RevMutIter rbegin() { return m_Data.rbegin(); }
    inline constexpr RevMutIter rend() { return m_Data.rend(); }
    inline constexpr RevConstIter rbegin() const { return m_Data.rbegin(); }
    inline constexpr RevConstIter rend() const { return m_Data.rend(); }

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
        m_Data.resize(width * height);
        m_Width = width;
        m_Height = height;
    }

    Result<void, RendererError> Save(std::filesystem::path path) const;

private:
    std::vector<u32> m_Data{};
    u32              m_Width{};
    u32              m_Height{};
};

}
