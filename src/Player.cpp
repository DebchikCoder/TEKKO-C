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

void Player::SetPosition(float x, float y)
{
      m_position.x = x;
      m_position.y = y;
}

void Player::SetPosition(Vector2 newPos)
{
      m_position = newPos;
}

bool Player::CheckCollision(Rectangle &rec)
{
    if(CheckCollisionRecs(m_collider, rec))
    {
      return true;
    }
    return false;
}

Vector2 Player::GetPosition()
{
      return m_position;
}

Vector2 Player::GetVelocity()
{
    return m_velocity;
}

std::unique_ptr<Projectile> Player::Shoot(Camera2D &cam, float speed)
{
      Vector2 mouseScrPos = GetScreenToWorld2D(GetMousePosition(), cam);
      Vector2 projDir = Vector2Normalize(Vector2Subtract(mouseScrPos, m_position));
      Vector2 projVector = Vector2Scale(projDir, speed);

      std::unique_ptr<Projectile> Bullet = std::make_unique<Projectile>(m_position, projVector, "assets/Bullet.png", speed, 4, (Vector2){16, 16});

      return Bullet;
}

void Player::Update(Camera2D& cam, std::vector<Rectangle> collisionRecs)
{
      //move player Left or Right
      bool isLeft, isRight;
      isLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
      isRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

      int input = static_cast<int>(isRight) - static_cast<int>(isLeft);
      float target = input * m_targetSpeed;
      float step = input != 0 ? m_accel : m_deccel;

      m_velocity.x = Util::Math::MoveTowards(m_velocity.x, target, step * GetFrameTime());

      m_position.x += m_velocity.x * GetFrameTime();

      //Move Up or Down
      if(IsKeyDown(KEY_DOWN))
      {
            m_velocity.y += 8000 * GetFrameTime();
      }

      if(IsKeyDown(KEY_UP))
      {
            m_velocity.y -= 8000 * GetFrameTime();
      }

      //Check Collision X
      m_collider = (Rectangle){m_position.x, m_position.y, 32, 62};

      for(auto r : collisionRecs)
      {
            if(CheckCollision(r))
            {
                  m_position.x -= m_velocity.x * GetFrameTime();
                  m_velocity.x = 0;
            }
      }

      //Check Collision y
      m_position.y += m_velocity.y * GetFrameTime();
      m_collider = (Rectangle){m_position.x, m_position.y, 32, 62};

      for(auto r : collisionRecs)
      {
            if(CheckCollision(r))
            {
                  m_position.y -= m_velocity.y * GetFrameTime();
            }
      }

      m_velocity.y = 0;

      // std::cout << m_velocity.x << "\n";
}

void Player::Draw()
{
      DrawTextureV(m_texture, m_position, WHITE);
}
