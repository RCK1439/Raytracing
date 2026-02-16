#include "Image.hpp"

#include <fpng.hpp>

#include <cassert>

namespace RTIAW {

static void ImgCpyFlipped(const Buffer<u32>& src, Buffer<u32>& dest, u32 width, u32 height);

Result<void, RendererError> Image::Save(const std::filesystem::path& path) const
{
    fpng::fpng_init();

    Buffer<u32> flipped(m_Width * m_Height);
    ImgCpyFlipped(m_Data, flipped, m_Width, m_Height);

    const std::string fileName = path.string();
    if (!fpng::fpng_encode_image_to_file(fileName.c_str(), flipped.GetRaw(), m_Width, m_Height, 4))
        return Err(RendererError(RendererErrorType::FAILED_TO_SAVE_IMAGE, path));

    return {};
}

static void ImgCpyFlipped(const Buffer<u32>& src, Buffer<u32>& dest, u32 width, u32 height)
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
