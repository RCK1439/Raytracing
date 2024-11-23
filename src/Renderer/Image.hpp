#pragma once

#include "Error.hpp"

#include <glm/vec4.hpp>

#include <expected>
#include <string_view>

namespace rt
{ 
    class Image
    {
    public:
        Image() = default;
        Image(uint32_t width, uint32_t height); 
        ~Image();

        void Resize(uint32_t width, uint32_t height);

        uint32_t GetColor(uint32_t x, uint32_t y) const;
        inline uint32_t GetWidth() const { return m_Width; }
        inline uint32_t GetHeight() const { return m_Height; } 
        inline uint32_t GetChannels() const { return m_Channels; }

        void SetColorHex(uint32_t x, uint32_t y, uint32_t color);
        void SetColorRGBA(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        void SetColor(uint32_t x, uint32_t y, const glm::vec4& color);

        std::expected<void, RendererError> Save(std::string_view filepath) const;

    private:
        uint32_t* m_Data = nullptr;
        uint32_t  m_Width = 0;
        uint32_t  m_Height = 0;
        uint32_t  m_Channels = 0;
    };
}
