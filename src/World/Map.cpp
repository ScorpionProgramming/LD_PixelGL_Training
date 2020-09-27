#include "Map.h"

Map::Map(unsigned int width, unsigned int height, char* map)
{
    m_map = new char[width*height];
    
    this->m_width = width;
    this->m_height = height;
    this->m_map = map;
}

Map::~Map()
{
    delete this->m_map;
}

char* Map::getName() const{
    return this->m_map;
}

void Map::setName(char* name){
    this->name = name;
}

unsigned int Map::getHeight() const{
    return this->m_height;
}

void Map::setHeight(unsigned int height){
    this->m_height = height; 
}

unsigned int Map::getWidth() const{
    return this->m_width;
}

void Map::setWidth(unsigned int width){
    this->m_width = width;
}

char Map::getCell(unsigned int x_Pos, unsigned int y_Pos) const{
    return m_map[x_Pos + (y_Pos * this->m_width)];
}