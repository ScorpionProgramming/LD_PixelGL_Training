
#ifndef PLAYER
#define PLAYER
#include "../Math/Math.h"

class Player
{
private:
    Vector2f m_pos;
    Vector2f m_dir;
public:
    Player();
    Player(Vector2f* pos, Vector2f* dir);

    Vector2f getPos() const;
    Vector2f getDir() const;

    void setPos(Vector2f& pos);
    void setDir(Vector2f& dir);

    ~Player();
};

#endif