#include "Color.h"
#include "Image.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
private:
    /* data */
    u_char* pixel_on_screen;
    uint width_;
    uint height_;

    //check if x and y are in boundry
    void check_x(uint& x);
    void check_y(uint& y);

public:
    Graphics(uint width, uint height);
    Graphics(uint width, uint height, Color c);

    u_char* get_pixels_on_screen() const;
    void draw_pixel(uint x, uint y, Color c);
    void draw_pixel(uint x, uint y, u_char r, u_char g, u_char b, u_char a);
    void draw_line(int x1, int y1, int x2, int y2, Color c);
    void draw_quad(uint x, uint y, uint width, uint height, Color c);
    void draw_quad_filled(uint x, uint y, uint width, uint height, Color c);
    void draw_image(uint x, uint y, uint width, uint height, Image& img);
    
    ~Graphics();
};

#endif