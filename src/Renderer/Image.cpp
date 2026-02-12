#include "Image.hpp"
#include "Renderer/Error.hpp"

#include <fpng.hpp>

#include <cassert>

namespace rt {

static void ImgCpyFlipped(const u32* const src, u32* const dest, u32 width, u32 height);

Result<void, RendererError> Image::Save(std::filesystem::path path) const
{
    fpng::fpng_init();

    u32* const flipped = new u32[m_Width * m_Height];
    ImgCpyFlipped(m_Data.data(), flipped, m_Width, m_Height);

    const std::string fileName = path.string();
    if (!fpng::fpng_encode_image_to_file(fileName.c_str(), flipped, m_Width, m_Height, 4))
        return Err(RendererError(RendererError::Type::FAILED_TO_SAVE_IMAGE, fileName));

    delete[] flipped;
    return {};
}

static void ImgCpyFlipped(const u32* const src, u32* const dest, u32 width, u32 height)
{
    u32 i{};
    for (u32 y = height - 1; y >= 1; y--)
        for (u32 x{}; x < width; x++)
            dest[i++] = src[x + y * width];

    // This copies the last horizontal line.
    for (u32 x{}; x < width; x++)
        dest[i++] = src[x];
}

}
