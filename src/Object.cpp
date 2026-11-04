#include "headers/Object.hpp"

IObject::IObject(Vector2 position, std::string TexturePath, float BBx, float BBy, float BBw, float BBh)
{
      m_position = position;
      m_hitBox = (Rectangle){BBx, BBy, BBw, BBh};
      m_texture = LoadTexture(TexturePath.c_str());
}

void IObject::Update(float dt)
{
      DrawText("add behaviour!", 0, 10, 5, RED);
}

void IObject::Draw()
{
      DrawTexture(m_texture, static_cast<int>(m_position.x), static_cast<int>(m_position.y), WHITE);
}

Vector2 IObject::getPosition()
{
      return m_position;
}

Texture2D IObject::getTexture()
{
      return m_texture;
}

Rectangle IObject::getHitBox()
{
      return m_hitBox;
}

IObject::~IObject()
{
      m_position = {0.0f, 0.0f};
      UnloadTexture(m_texture);
      m_hitBox = (Rectangle){0, 0, 0, 0};
}
