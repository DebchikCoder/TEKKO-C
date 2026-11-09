#pragma once

#include <string>
#include <raylib.h>
#include <raymath.h>
#include <memory>
#include "Object.hpp"
#include "utils/Math.hpp"
#include "Projectile.hpp"

#define NUMtoUNIT(n) n * 16.0f // 16.0f is one tile size. Its needed for conversion

class Player
{
private:
      Texture2D m_texture;
      Vector2 m_position;
      Vector2 m_velocity;

      Rectangle m_collider;

      float m_accel, m_deccel, m_targetSpeed;
public:
      Player(std::string pathToSprite, float acceleration, float decceleration, float MaxSpeed);
      ~Player();

      void SetPosition(float x, float y);
      void SetPosition(Vector2 newPos);
      void DrawCollisionRect();
      bool CheckCollision(Rectangle& rec);
      Vector2 GetPosition();
      Vector2 GetVelocity();
      std::unique_ptr<Projectile> Shoot(Camera2D& cam, float speed);
      void Update(Camera2D& cam);
      void Draw();
};
