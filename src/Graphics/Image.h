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
    unsigned int width_;
    unsigned int height_;

public:
    Image(std::string path);
    Image();
    void load_tga(std::string path);
    unsigned char* get_full_image();
    Color get_pixel(unsigned int x, unsigned int y);
    unsigned int get_width() const;
    unsigned int get_height() const;

    ~Image();
};


class Image{
public:
    Image(unsigned int width, unsigned int height);

    unsigned int get_width() const;
    unsigned int get_height() const;
    Color get_color(unsigned int pos_x, unsigned int pos_y) const;
    unsigned int get_image_id() const; 
    //Sprite get_sprite(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    //Sprite get_sprite(unsigned int x, unsigned int y, unsigned int size);

    void set_width(unsigned int width);
    void set_height(unsigned int height);
    void set_color(unsigned int pos_x, unsigned int pos_y, Color* color);
    void set_image_id(unsigned int buffer_id);

    char* image_to_byte_rgb()  const; /*in OpenGL GL_RGB  GL_UNSIGNED_BYTE*/
    char* image_to_byte_rgba() const; /*in OpenGL GL_RGBA GL_UNSIGNED_BYTE*/
    /*maybe later some greyscale*/

    ~Image();
private:
    Color* pixels_;
    unsigned int width_;
    unsigned int height_;

    /*used for openGL when graphics get loaded into image buffer*/
    unsigned int id_;
};

#endif