#include "headers/Projectile.hpp"

Projectile::Projectile(Vector2 startPos, Vector2 directionVector, std::string spriteName, float speed, float lifeTime,Vector2 BBsize) :
IObject(startPos, spriteName, m_position.x, m_position.y, BBsize.x, BBsize.y)
{
      m_position = startPos;
      m_Dir = directionVector;
      m_speed = speed;
      m_LifeTime = lifeTime;
}

void Projectile::Update(float dt)
{
      //проверяем умерла ли пуля
      if(m_LifeTime <= 0)
            Destroy();
      m_position.x += m_Dir.x * dt;
      m_position.y += m_Dir.y * dt;

      m_LifeTime -= 1 * dt;
}

void Projectile::CheckCollision(Rectangle &rec)
{
      if(CheckCollisionRecs(m_hitBox, rec))
      {
            Destroy();
      }
}

void Projectile::Draw()
{
      DrawTextureV(m_texture, m_position, WHITE);
}
