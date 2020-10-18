#include "Color.h"

Color::Color(){
    this->r_ = 0x00;
    this->g_ = 0x00;
    this->b_ = 0x00;
    this->a_ = 0xff;
}

Color::Color(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a){
    this->r_ = r;
    this->g_ = g;
    this->b_ = b;
    this->a_ = a;
}

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a){
    this->r_ = (unsigned char)r;
    this->g_ = (unsigned char)g;
    this->b_ = (unsigned char)b;
    this->a_ = (unsigned char)a;
}

unsigned char Color::get_r() const {
    return this->r_;
}

unsigned char Color::get_g() const{
    return this->g_;
}

unsigned char Color::get_b() const{
    return this->b_;
}

unsigned char Color::get_a() const{
    return this->a_;
}

void Color::set_r(unsigned char r){
    r_ = r;
}

void Color::set_g(unsigned char g){
    g_ = g;
}

void Color::set_b(unsigned char b){
    b_ = b;
}

void Color::set_a(unsigned char a){
    a_ = a;
}

void Color::operator=(const Color& color){
    r_ = color.get_r();
    g_ = color.get_g();
    b_ = color.get_b();
    a_ = color.get_a();
}


Color::~Color(){
}