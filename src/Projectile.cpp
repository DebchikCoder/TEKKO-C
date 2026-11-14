#include "headers/Projectile.hpp"

Projectile::Projectile(Vector2 startPos, Vector2 directionVector, std::string spriteName, float speed, float lifeTime, Vector2 BBpos, Vector2 BBsize) :
IObject(startPos, spriteName, BBpos.x, BBpos.y, BBsize.x, BBsize.y)
{
      m_position = startPos;
      m_Dir = directionVector;
      m_speed = speed;
      m_LifeTime = lifeTime;

      TraceLog(LOG_INFO, "BB size: %f, %f, %f, %f", m_hitBox.x, m_hitBox.y, m_hitBox.width, m_hitBox.height);
}

void Projectile::Update(float dt)
{
      //проверяем умерла ли пуля
      if(m_LifeTime <= 0)
            Destroy();
      m_position.x += m_Dir.x * dt;
      m_position.y += m_Dir.y * dt;

      m_hitBox.x = m_position.x;
      m_hitBox.y = m_position.y;

      m_LifeTime -= 1 * dt;
}

void Projectile::Draw()
{
      DrawTextureV(m_texture, m_position, WHITE);
}

void Projectile::CheckCollision(std::vector<Rectangle> recs)
{
      for(auto col : recs)
      {
            if(CheckCollisionRecs(m_hitBox, col))
            {
                  Destroy();
            }
      }
}
