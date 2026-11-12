#include "headers/BackGround.hpp"

BackGround::BackGround(Texture2D texture)
{
    m_texture = texture;
    m_position = {0.0, 0.0};
}

void BackGround::Scroll(float paralaxFactor)
{
    TraceLog(LOG_WARNING, "IT'S UNIMPLEMENTED FUNCTION YAY :)");
}

void BackGround::Draw()
{
    DrawTextureV(m_texture, m_position, WHITE);
}

void BackGround::Draw(float scale)
{
    DrawTextureEx(m_texture, m_position, 0.0f, scale, WHITE);
}

void BackGround::Draw(float scaleX, float scaleY)
{
    Rectangle source = {0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height};
    Rectangle dest = {0.0f, 0.0f, (float)m_texture.width * scaleX, (float)m_texture.height * scaleY};

    DrawTexturePro(m_texture, source, dest, (Vector2){0.0, 0.0}, 0.0, WHITE);
}

BackGround::~BackGround()
{
    UnloadTexture(m_texture);
}
