#pragma once

#include "Types.hpp"

#include <glm/vec4.hpp>
#include <string_view>

namespace rt
{
    class Image
    {
    public:
        Image() = default;
        Image(u32 width, u32 height);
        ~Image();

        u32 GetColor(u32 x, u32 y) const;
        inline u32 GetWidth() const { return m_Width; }
        inline u32 GetHeight() const { return m_Height; }
        inline u32 GetChannels() const { return m_Channels; }

        void SetColorHex(u32 x, u32 y, u32 color);
        void SetColorRGBA(u32 x, u32 y, u8 r, u8 g, u8 b, u8 a = 0xFF);
        void SetColor(u32 x, u32 y, const glm::vec4& color);

        void Save(std::string_view filepath) const;

    private:
        u32* m_Data = nullptr;
        u32 m_Width = 0;
        u32 m_Height = 0;
        u32 m_Channels = 0;
    };
} // namespace rt
