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

    void Image::SetColorFloat(u32 x, u32 y, f32 r, f32 g, f32 b, f32 a)
    {
        const u8 ur = u8(r * 254.99999f);
        const u8 ug = u8(g * 254.99999f);
        const u8 ub = u8(b * 254.99999f);
        const u8 ua = u8(a * 254.99999f);

        SetColorRGBA(x, y, ur, ug, ub, ua); 
    }

    void Image::Save(std::string_view filepath) const
    {
        fpng::fpng_init();

        if (fpng::fpng_encode_image_to_file(filepath.data(), m_Data, m_Width, m_Height, 4))
        {
            std::cout << "Successfully saved image: " << filepath << std::endl;
        }
        else std::cout << "Failed to save image: " << filepath << std::endl;
    }
} // namespace rt
