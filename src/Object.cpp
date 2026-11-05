#include "headers/Object.hpp"

IObject::IObject(Vector2 position, std::string TexturePath, float BBx, float BBy, float BBw, float BBh)
{
      m_position = position;
      m_hitBox = (Rectangle){BBx, BBy, BBw, BBh};
      m_texture = LoadTexture(TexturePath.c_str());
}

void IObject::Update(float dt)
{
      DrawText("add behaviour!", 0, 10, 25, RED);
}

void IObject::Draw()
{
      DrawTexture(m_texture, static_cast<int>(m_position.x), static_cast<int>(m_position.y), WHITE);
}

void IObject::SetID(int id)
{
      m_id = id;
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

int IObject::getID()
{
    return m_id;
}

IObject::~IObject()
{
      m_position = {0.0f, 0.0f};
      UnloadTexture(m_texture);
      m_hitBox = (Rectangle){0, 0, 0, 0};
}
