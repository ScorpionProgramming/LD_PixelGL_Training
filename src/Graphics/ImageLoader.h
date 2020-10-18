#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "Image.h"

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

class ImageLoader
{
private:
    /* data */
public:
    ImageLoader(/* args */);
    ~ImageLoader();
    static void load_ppm(char* path, Image& img);
    static void load_tga(char* path, Image& img);
};

#endif