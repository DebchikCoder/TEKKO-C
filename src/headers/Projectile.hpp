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
      Projectile(Vector2 startPos, Vector2 directionVector, std::string spriteName, float speed, float lifeTime, Vector2 BBpos, Vector2 BBsize);
      void Update(float dt) override;
      void Draw() override;
      void CheckCollision(std::vector<Rectangle> recs) override;
};