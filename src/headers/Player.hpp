#pragma once

#include <string>
#include <raylib.h>
#include "utils/Math.hpp"

#define NUMtoSPEED(n) n/10.0f

class Player
{
private:
      Texture2D m_texture;
      Vector2 m_position;
      Vector2 m_velocity;

      float m_accel, m_deccel, m_targetSpeed;
public:
      Player(std::string pathToSprite, float acceleration, float decceleration, float MaxSpeed);
      ~Player();

      void SetPosition(float x, float y);
      void SetPosition(Vector2 newPos);
      void Update();
};
