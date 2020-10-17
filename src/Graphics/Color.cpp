#include "Color.h"

Color::Color(){
    this->r = 0x00;
    this->g = 0x00;
    this->b = 0x00;
    this->a = 0xff;
}

Color::Color(u_char& r, u_char& g, u_char& b, u_char& a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(uint r, uint g, uint b, uint a){
    this->r = (u_char)r;
    this->g = (u_char)g;
    this->b = (u_char)b;
    this->a = (u_char)a;
}

u_char Color::get_r() const {
    return this->r;
}

u_char Color::get_g() const{
    return this->g;
}

u_char Color::get_b() const{
    return this->b;
}

u_char Color::get_a() const{
    return this->a;
}

Color::~Color(){
}