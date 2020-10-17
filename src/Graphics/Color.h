#ifndef COLOR_H
#define COLOR_H


typedef unsigned char u_char;
typedef unsigned int uint;

class Color
{
private:
    /* data */
    u_char r;
    u_char g;
    u_char b;
    u_char a;
public:
    Color();
    Color(u_char& r, u_char& g, u_char& b, u_char& a);
    Color(uint r, uint g, uint b, uint a);

    u_char get_r() const;
    u_char get_g() const;
    u_char get_b() const;
    u_char get_a() const;

    ~Color();
};

#endif