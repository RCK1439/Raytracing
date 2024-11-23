#include "Image.hpp"
#include "Renderer/Error.hpp"

#include <fpng.h>

#include <cassert>
#include <print>

namespace rt
{
    static void ImgCpyFlipped(const uint32_t* const src, uint32_t* const dest, uint32_t width, uint32_t height);

    Image::Image(uint32_t width, uint32_t height) :
        m_Width(width), m_Height(height), m_Channels(0)
    {
        m_Data = new uint32_t[width * height];
    }

    Image::~Image()
    {
        delete[] m_Data;
    }

    void Image::Resize(uint32_t width, uint32_t height)
    {
        delete[] m_Data;
        
        m_Data = new uint32_t[width * height];

        m_Width  = width;
        m_Height = height;
    }

    uint32_t Image::GetColor(uint32_t x, uint32_t y) const
    {
        assert(x < m_Width && y < m_Height);
        
        return m_Data[x + y * m_Width];
    }

    void Image::SetColorHex(uint32_t x, uint32_t y, uint32_t color)
    {
        assert(x < m_Width && y < m_Height);

        m_Data[x + y * m_Width] = color;
    }

    void Image::SetColorRGBA(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        const uint32_t color = (a << 24) | (b << 16) | (g << 8) | (r << 0);

        SetColorHex(x, y, color);
    }

    void Image::SetColor(uint32_t x, uint32_t y, const glm::vec4& color)
    {
        const uint8_t r = static_cast<uint8_t>(color.r * 254.99999f);
        const uint8_t g = static_cast<uint8_t>(color.g * 254.99999f);
        const uint8_t b = static_cast<uint8_t>(color.b * 254.99999f);
        const uint8_t a = static_cast<uint8_t>(color.a * 254.99999f);

        SetColorRGBA(x, y, r, g, b, a); 
    }

    std::expected<void, RendererError> Image::Save(std::string_view filepath) const
    {
        fpng::fpng_init();

        uint32_t* const flipped = new uint32_t[m_Width * m_Height];
        ImgCpyFlipped(m_Data, flipped, m_Width, m_Height);

        if (!fpng::fpng_encode_image_to_file(filepath.data(), flipped, m_Width, m_Height, 4))
        {
            return std::unexpected(RendererError(RendererError::Type::FAILED_TO_SAVE_IMAGE, filepath));
        }

        delete[] flipped;
        return {};
    }

    static void ImgCpyFlipped(const uint32_t* const src, uint32_t* const dest, uint32_t width, uint32_t height)
    {
        uint32_t i = 0;
        for (uint32_t y = height - 1; y >= 1; y--)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                dest[i++] = src[x + y * width];
            }
        }

        // This copies the last horizontal line.
        for (uint32_t x = 0; x < width; x++)
        {
            dest[i++] = src[x];
        }
    }
}
