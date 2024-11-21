/**
 * Ruan C. Keet (2023)
 * Image.cpp
*/

#include "Image.hpp"

#include <fpng.h>

#include <assert.h>
#include <iostream>

namespace rt
{
    Image::Image(u32 width, u32 height) :
        m_Width(width), m_Height(height), m_Channels(0)
    {
        m_Data = new u32[width * height];
    }

    Image::~Image()
    {
        delete[] m_Data;
    }

    void Image::Resize(u32 width, u32 height)
    {
        delete[] m_Data;
        
        m_Data = new u32[width * height];

        m_Width  = width;
        m_Height = height;
    }

    u32 Image::GetColor(u32 x, u32 y) const
    {
        assert(x < m_Width && y < m_Height);
        
        return m_Data[x + y * m_Width];
    }

    void Image::SetColorHex(u32 x, u32 y, u32 color)
    {
        assert(x < m_Width && y < m_Height);

        m_Data[x + y * m_Width] = color;
    }

    void Image::SetColorRGBA(u32 x, u32 y, u8 r, u8 g, u8 b, u8 a)
    {
        const u32 color = (a << 24) | (b << 16) | (g << 8) | (r << 0);

        SetColorHex(x, y, color);
    }

    void Image::SetColor(u32 x, u32 y, const glm::vec4& color)
    {
        const u8 r = static_cast<u8>(color.r * 254.99999f);
        const u8 g = static_cast<u8>(color.g * 254.99999f);
        const u8 b = static_cast<u8>(color.b * 254.99999f);
        const u8 a = static_cast<u8>(color.a * 254.99999f);

        SetColorRGBA(x, y, r, g, b, a); 
    }

    /**
     * \brief Copies a vertically flipped version of the image to the destination
     * memory.
     * 
     * \param src       The data to copy.
     * \param dest      The memory to copy to.
     * \param width     The width of the image.
     * \param height    The height of the image.
    */
    static void ImgCpyFlipped(const u32* const src, u32* const dest, u32 width, u32 height)
    {
        u32 i = 0;
        for (u32 y = height - 1; y >= 1; y--)
            for (u32 x = 0; x < width; x++)
                dest[i++] = src[x + y * width];

        // This copies the last horizontal line.
        for (u32 x = 0; x < width; x++)
            dest[i++] = src[x];
    }

    void Image::Save(std::string_view filepath) const
    {
        fpng::fpng_init();

        u32* const flipped = new u32[m_Width * m_Height];
        ImgCpyFlipped(m_Data, flipped, m_Width, m_Height);

        if (fpng::fpng_encode_image_to_file(filepath.data(), flipped, m_Width, m_Height, 4))
        {
            std::cout << "Successfully saved image: " << filepath << std::endl;
        }
        else std::cout << "Failed to save image: " << filepath << std::endl;

        delete[] flipped;
    }
}
