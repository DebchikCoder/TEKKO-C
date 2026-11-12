#pragma once
#include <raylib.h>

class BackGround
{
private:
    Texture2D m_texture;
    bool isMovable;
    float m_deltaX, m_deltaY;
    Vector2 m_position;
public:
    BackGround(Texture2D texture);
    void Scroll(float paralaxFactor);
    void Draw();
    void Draw(float scale);
    void Draw(float scaleX, float scaleY);
    ~BackGround();
};

