
class Vector2d
{
private:
    /* data */
public:
    float X;
    float Y;

    Vector2d(/* args */);
    Vector2d(float x, float y);
    ~Vector2d();

    Vector2d operator+(Vector2d& other) const;
    void operator=(Vector2d& other);
    Vector2d operator*(float product);
};

Vector2d::Vector2d(){
    this->X = 0; 
    this->Y = 0;
}

Vector2d::~Vector2d(){
}

Vector2d Vector2d::operator+(Vector2d& other) const{
    return Vector2d(this->X+other.X, this->Y + other.Y);
}

void Vector2d::operator=(Vector2d& other){
    this->X = other.X;
    this->Y = other.Y;
}

Vector2d Vector2d::operator*(float product){
   return Vector2d(this->X * product, this->Y = this->Y * product);
}