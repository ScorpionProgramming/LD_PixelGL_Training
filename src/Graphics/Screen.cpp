#include "Screen.h"

Screen::Screen(unsigned int& width, unsigned int& height)
{
    this->m_height  = height;
    this->m_width   = width;
}

Screen::~Screen()
{
}

void Screen::setWidth(unsigned int& width){
    this->m_width = width;
}

void Screen::setHeight(unsigned int& height){
    this->m_height = height;
}

unsigned int Screen::getWidth() const{
    return this->m_width;
}

unsigned int Screen::getHeight() const{
    return this->m_height;
}