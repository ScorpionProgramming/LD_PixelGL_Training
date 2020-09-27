
#ifndef VECTOR_2F
#define VECTOR_2F

class Vector2f
{
private:
    /* data */
public:
    float X;
    float Y;

    Vector2f(/* args */);
    Vector2f(float x, float y);
    ~Vector2f();

    Vector2f operator+(Vector2f& other) const;
    Vector2f operator=(Vector2f other);
    Vector2f operator*(float product);
};

#endif