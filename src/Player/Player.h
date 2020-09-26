class Player
{
private:
    float m_pos_X;
    float m_pos_y;
    float m_look;
public:
    Player();
    Player(float posX, float posY, unsigned int look);

    float getPosX() const;
    float getPosY() const;
    float getLook() const;
    void setPosX(float& x);
    void setPosY(float& y);
    void setLook(float& look);

    ~Player();
};

Player::Player()
{
    this->m_pos_X = 0.0f;
    this->m_pos_y = 0.0f;
    this->m_look  = 0.0f;
}

Player::Player(float posX, float posY, unsigned int look){
    this->m_pos_X = posX;
    this->m_pos_y = posY;
    this->m_look  = look;
}

float Player::getPosX() const{
    return this->m_pos_X;
}

float Player::getPosY() const{
    return this->m_pos_y;
}

float Player::getLook() const{
    return this->m_look;
}

void Player::setPosX(float& x){
    this->m_pos_X = x;
}

void Player::setPosY(float& y){
    this->m_pos_y = y;
}

void Player::setLook(float& look){
    this->m_look = look;
}

Player::~Player(){

}
