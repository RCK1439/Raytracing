/**
 * Ruan C. Keet (2023)
 * Image.hpp
*/

#pragma once

#include "Types.hpp"

#include <glm/vec4.hpp>

#include <string_view>

namespace rt
{
    /**
     * This class represents the image the program is writing to.
     * It has easy to use functionality for saving and modifying.
    */
    class Image
    {
    public:
        /**
         * Constructs a new image.
        */
        Image() = default;

        /**
         * Constructs a new image with the specified dimensions.
         * 
         * \param width     The width of the image.
         * \param height    The height of the image.
        */
        Image(u32 width, u32 height);

        /**
         * Frees any resources used by the image and destroys the image.
        */
        ~Image();

        /**
         * Resizes the image to the specified dimensions.
         * 
         * \param width     The new width of the image.
         * \param height    The new height of the image.
        */
        void Resize(u32 width, u32 height);

        /**
         * Gets the color at the specified pixel coordinates.
         * 
         * \param x The x-coordinate.
         * \param y The y-coordinate.
         * 
         * \return The color at the pixel coordinates.
        */
        u32 GetColor(u32 x, u32 y) const;

        /**
         * Gets the width of the image.
         * 
         * \return The width of the image.
        */
        inline u32 GetWidth() const { return m_Width; }

        /**
         * Gets the height of the image.
         * 
         * \return The height of the image.
        */
        inline u32 GetHeight() const { return m_Height; }

        /**
         * Gets the number of channels of the image.
         * 
         * \return The number of channels.
        */
        inline u32 GetChannels() const { return m_Channels; }

        /**
         * Sets the color of the pixel at the specified coordinates
         * with a hexadecimal color value.
         * 
         * \param x     The x-coordinate.
         * \param y     The y-coordinate.
         * \param color The color to set the pixel to.
        */
        void SetColorHex(u32 x, u32 y, u32 color);

        /**
         * Sets the color of the pixel at the specified coordinates
         * with individual red, green, blue and alpha values.
         * 
         * \param x The x-coordinate.
         * \param y The y-coordinate.
         * \param r The red value.
         * \param g The green value.
         * \param b The blue value.
         * \param a The alpha value.
        */
        void SetColorRGBA(u32 x, u32 y, u8 r, u8 g, u8 b, u8 a = 0xFF);

        /**
         * Sets the color of the pixel at the specified coordinates
         * with a vector containing floating point color values.
         * 
         * \param x     The x-coordinate.
         * \param y     The y-coordinate.
         * \param color The color to set the pixel to.
        */
        void SetColor(u32 x, u32 y, const glm::vec4& color);

        /**
         * Saves the image to the specified output path.
         * 
         * \param filepath  The directory to save the image to.
        */
        void Save(std::string_view filepath) const;

    private:
        u32* m_Data = nullptr;
        u32 m_Width = 0;
        u32 m_Height = 0;
        u32 m_Channels = 0;
    };
} // namespace rt
