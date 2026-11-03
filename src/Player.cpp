#include "headers/Player.hpp"
#include <iostream>

Player::Player(std::string pathToSprite, float acceleration, float decceleration, float MaxSpeed)
{
      m_texture = LoadTexture(pathToSprite.c_str());
      m_accel = acceleration;
      m_deccel = decceleration;
      m_targetSpeed = MaxSpeed;
      m_position = {0, 50};
}

Player::~Player()
{
      m_position = {0, 0};
      m_accel = 0;
      m_deccel = 0;
      UnloadTexture(m_texture);
}

void Player::Update()
{
      bool isLeft, isRight;
      isLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
      isRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

      int input = static_cast<int>(isRight) - static_cast<int>(isLeft);
      float target = input * m_targetSpeed;
      float step = input != 0 ? m_accel : m_deccel;

      m_velocity.x = Util::Math::MoveTowards(m_velocity.x, target, step * GetFrameTime());

      m_position.x += m_velocity.x * GetFrameTime();

      std::cout << m_velocity.x << "\n";
      
      DrawTexture(m_texture, static_cast<int>(m_position.x), static_cast<int>(m_position.y), WHITE);
}
