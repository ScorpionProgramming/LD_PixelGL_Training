#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h> 

#include "Color.h"

#ifndef IMAGE_H
#define IMAGE_H


class Image
{
typedef struct {
    short int index;
    short int length;
    char entry_size;
}COLOR_MAP_SPECIFICATION;

typedef struct{
    short int x_origin;
    short int y_origin;
    short int width;
    short int height;
    char pixel_depth;
    char descriptor; 
}IMAGE_SPECIFICATION;

typedef struct{
    char id_length;
    char color_map_type;
    char image_type;
    COLOR_MAP_SPECIFICATION color_map_specification;
    IMAGE_SPECIFICATION image_specification;
}TGA_HEAD;

typedef struct{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
}COLOR_RGBA;

private:
    /* data */
    unsigned char* pixel_data_;
    uint width_;
    uint height_;

public:
    Image(std::string path);
    Image();
    void load_tga(std::string path);
    unsigned char* get_full_image();
    Color get_pixel(uint x, uint y);
    uint get_width() const;
    uint get_height() const;

    ~Image();
};



#endif