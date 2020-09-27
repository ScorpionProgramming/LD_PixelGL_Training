#include "Math.h"

Vector2f::Vector2f(){
    this->X = 0; 
    this->Y = 0;
}

Vector2f::Vector2f(float x, float y){
    this->X = x; 
    this->Y = y;
}

Vector2f::~Vector2f(){
}

Vector2f Vector2f::operator+(Vector2f& other) const{
    return Vector2f(this->X+other.X, this->Y + other.Y);
}

Vector2f Vector2f::operator=(Vector2f other){
    this->X = other.X;
    this->Y = other.Y;
    return *this;
}

Vector2f Vector2f::operator*(float product){
   return Vector2f(this->X * product, this->Y = this->Y * product);
}