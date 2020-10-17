#include "Graphics.h"

Graphics::Graphics(uint width, uint height){
    this->width_    = width;
    this->height_   = height;

    uint array_size = (width * height); 
    pixel_on_screen = new u_char[array_size * 4];
    uint i;
    for (i = 0; i < array_size; i++){
        pixel_on_screen[i * 4 + 0] = 0x00;
        pixel_on_screen[i * 4 + 1] = 0x00;
        pixel_on_screen[i * 4 + 2] = 0x00;
        pixel_on_screen[i * 4 + 3] = 0xff;
    }
}

Graphics::Graphics(uint width, uint height, Color c){
    this->width_    = width;
    this->height_   = height;

    uint array_size = (width * height); 
    pixel_on_screen = new u_char[array_size * 4];
    uint i;
    for (i = 0; i < array_size; i++){
        pixel_on_screen[i * 4 + 0] = c.get_r();
        pixel_on_screen[i * 4 + 1] = c.get_g();
        pixel_on_screen[i * 4 + 2] = c.get_b();
        pixel_on_screen[i * 4 + 3] = c.get_b();
    }
}

u_char* Graphics::get_pixels_on_screen() const{
    return this->pixel_on_screen;
}

void Graphics::draw_pixel(uint x, uint y, Color c){
    // if(x < width_ && y < height_){
        uint coord = (x + (y * width_));
        pixel_on_screen[coord * 4 + 0] = c.get_r();
        pixel_on_screen[coord * 4 + 1] = c.get_g();
        pixel_on_screen[coord * 4 + 2] = c.get_b();
        pixel_on_screen[coord * 4 + 3] = c.get_a();
    // }
}

void Graphics::draw_pixel(uint x, uint y, u_char r, u_char g, u_char b, u_char a){
    uint coord = (x + (y * width_));
    pixel_on_screen[coord * 4 + 0] = r;
    pixel_on_screen[coord * 4 + 1] = g;
    pixel_on_screen[coord * 4 + 2] = b;
    pixel_on_screen[coord * 4 + 3] = a;
}


void Graphics::draw_line(int x1, int y1, int x2, int y2, Color c){
    // c1 = b1 - a1;
    // c2 = b2 - a2; 

    // float length = sqrt(c1 * c1 + c2 * c2);

    // float cn1 = ((float)c1 / length);
    // float cn2 = ((float)c2 / length);

    // float drawV1 = a1;
    // float drawV2 = a2;

    // while((int)drawV1 != b1 || (int)drawV2 != b2){
    //     g.draw_pixel(drawV1, drawV2, red);
    //     drawV1 += cn1;
    //     drawV2 += cn2;
    // }

    
    //vector
    int cx = x2 - x1;
    int cy = y2 - y1; 

    float length = sqrt(cx * cx + cy * cy);
    // std::cout << "Length: " << length << std::endl;


    float c_norm_x = ((float)cx / length);
    float c_norm_y = ((float)cy / length);

    // std::cout << c_norm_x << ", " << c_norm_y << std::endl; 

    float draw_vec_x = x1;
    float draw_vec_y = y1;

    while((int)draw_vec_x != x2 || (int)draw_vec_y != y2){
        draw_pixel(draw_vec_x, draw_vec_y, c);
        // std::cout << "DRAW: " << draw_vec_x << ", " << draw_vec_y << std::endl; 
        draw_vec_x += c_norm_x;
        draw_vec_y += c_norm_y;
    }
    draw_pixel(x2, y2, c); 
    
    /* swap - perinio */
    // if(x1 >= x2){
    //     int tmp;
    //     tmp = x1; 
    //     x1 = x2; 
    //     x2 = tmp;

    //     tmp = y1; 
    //     y1 = y2; 
    //     y2 = tmp;
    // }

    // float delta_x = (x2 - x1);
    // float delta_y = (y2 - y1);

    // float x = x1; 
    // float y = y1; 
    // if(delta_x == 0){
    //     while(y != y2){
    //         this->draw_pixel((int)x, (int)y, c);
    //         if(y < y2){
    //             y++;
    //         }else if(y > y2) {
    //             y--;
    //         }
    //     }
    // }else if(delta_y == 0){
    //     while(x != x2){
    //         x++;
    //         this->draw_pixel((int)x, (int)y, c);
    //     }
    // }else{
    //     while(x != x2 && y != y2){
    //         float m = ((float)delta_y / (float)delta_x);
    //         if(m < 1){
    //             x += 1;
    //             y += m;
    //         }else if(m > 1){
    //             y += 1;
    //             x += 1/m;
    //         }else if(m == 1){
    //             y++;
    //             x++;
    //         }
    //         this->draw_pixel((int)x, (int)y, c);
    //     }
    // }
}

void Graphics::draw_quad(uint x, uint y, uint width, uint height, Color c){
    draw_line(x , y, x + width, y, c);
    draw_line(x + width, y, x + width, y + height, c);
    draw_line(x + width, y + height, x, y + height, c);
    draw_line(x, y + height, x, y, c);
}

void Graphics::draw_quad_filled(uint x, uint y, uint width, uint height, Color c){
    for(uint i = 0; i < height; i++){
        draw_line(x, y + i, x + width, y + i, c);
    }
}

void Graphics::draw_image(uint x, uint y, uint width, uint height, Image& img){
    /* every vertical line */
    for(int u = 0; u < img.get_width(); u++){
        for(int v = 0; v < img.get_height(); v++){
            if(img.get_pixel(u, v).get_a() != 0)
                this->draw_pixel(x+u, y+v, img.get_pixel(u, v));
        }
    }
}

Graphics::~Graphics(){
    delete pixel_on_screen;
}