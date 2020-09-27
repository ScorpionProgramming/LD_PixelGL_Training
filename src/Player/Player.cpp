#include "Player.h"

Player::Player()
{
    this->m_pos = Vector2f(0.0f, 0.0f);
    this->m_dir = Vector2f(0.0f, 0.0f);
}

Player::Player(Vector2f& pos, Vector2f& dir){
    this->m_pos = pos;
    this->m_dir = dir;
}

Vector2f Player::getPos() const{
    return m_pos;
}

Vector2f Player::getDir() const{
    return m_dir;
}

void Player::setPos(Vector2f& pos){
    m_pos = pos;
}

void Player::setDir(Vector2f& dir){
    m_dir = dir;
}

Player::~Player(){
    
}
