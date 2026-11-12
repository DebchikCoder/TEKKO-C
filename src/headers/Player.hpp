#pragma once

#include <string>
#include <raylib.h>
#include <raymath.h>
#include <memory>
#include "Object.hpp"
#include "utils/Math.hpp"
#include "Projectile.hpp"
#include <vector>

constexpr float NUMtoUNIT(float n)
{
    return n * 16.0f;
}

class Player
{
private:
      Texture2D m_texture;
      Vector2 m_position;
      Vector2 m_velocity;

      int8_t jumpCount;

      Rectangle m_collider;
      bool isGrounded;

      float m_accel, m_deccel, m_targetSpeed, m_gravity;
public:
      Player(std::string pathToSprite, float acceleration, float decceleration, float MaxSpeed, float gravity);
      ~Player();

      void SetPosition(float x, float y);
      void SetPosition(Vector2 newPos);
      void DrawCollisionRect();
      bool CheckCollision(Rectangle& rec);
      Vector2 GetPosition();
      Vector2 GetVelocity();
      std::unique_ptr<Projectile> Shoot(Camera2D& cam, float speed);
      void Update(Camera2D& cam, std::vector<Rectangle> collisionRecs);
      void Draw();
};
