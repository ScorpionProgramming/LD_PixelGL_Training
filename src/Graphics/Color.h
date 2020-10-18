#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    Color(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);
    Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

    unsigned char get_r() const;
    unsigned char get_g() const;
    unsigned char get_b() const;
    unsigned char get_a() const;

    void set_r(unsigned char r);
    void set_g(unsigned char g);
    void set_b(unsigned char b);
    void set_a(unsigned char a);

    void operator=(const Color& color);

    ~Color();

private:
    /* data */
    unsigned char r_;
    unsigned char g_;
    unsigned char b_;
    unsigned char a_;
};

#endif