#include "Image.hpp"

#define WIDTH  400
#define HEIGHT 400

int main()
{
    rt::Image image(WIDTH, HEIGHT);

    for (u32 y = 0; y < HEIGHT; y++)
    {
        for (u32 x = 0; x < WIDTH; x++)
        {
            f32 r = (f32)x / (f32)WIDTH;
            f32 g = (f32)y / (f32)HEIGHT;
            f32 b = 0.2f;

            image.SetColorFloat(x, y, r, g, b); 
        }
    }

    image.Save("out/test.png");

    return 0;
}