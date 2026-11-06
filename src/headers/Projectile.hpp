#pragma once
#include <raylib.h>
#include "Object.hpp"

class Projectile : public IObject
{
private:
      float m_speed;
      float m_LifeTime;
      Vector2 m_Dir;
public:
      Projectile(Vector2 startPos, Vector2 directionVector, std::string spriteName, float speed, float lifeTime,Vector2 BBsize);
      void Update(float dt) override;
      void CheckCollision(Rectangle& rec);
      void Draw() override;
};