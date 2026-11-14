#include "headers/Player.hpp"
#include <iostream>

Player::Player(std::string pathToSprite, float acceleration, float decceleration, float MaxSpeed, float gravity)
{
      m_texture = LoadTexture(pathToSprite.c_str());
      m_accel = acceleration;
      m_deccel = decceleration;
      m_gravity = gravity;
      m_targetSpeed = MaxSpeed;
      m_position = {0, 50};
      m_velocity = {0, 0};
      isGrounded = false;
      m_jumpCount = 1;
      currentSlot = 0;
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
      std::unique_ptr<Projectile> Bullet;

      if(m_weaponSlots[currentSlot].weapon == 0)
      {
            Bullet = std::make_unique<Projectile>(m_position, projVector, "assets/Bullet.png", speed, 3, (Vector2){m_position.x, m_position.y}, (Vector2){16, 16});
      }

      if(m_weaponSlots[currentSlot].weapon == 1)
      {
            Bullet = std::make_unique<Projectile>(m_position, projVector, "assets/Electro.png", speed, 3, (Vector2){m_position.x, m_position.y}, (Vector2){16, 16});
      }

      return Bullet;
}

void Player::Update(Camera2D& cam, std::vector<Rectangle> collisionRecs)
{
      //move player Left or Right
      bool isLeft, isRight;
      isGrounded = false;
      isLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
      isRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

      int input = static_cast<int>(isRight) - static_cast<int>(isLeft);
      float target = input * m_targetSpeed;
      float step = input != 0 ? m_accel : m_deccel;

      m_velocity.x = Util::Math::MoveTowards(m_velocity.x, target, step * GetFrameTime());
      m_velocity.y += m_gravity * GetFrameTime();

      m_position.x += m_velocity.x * GetFrameTime();

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
                  isGrounded = true;
                  m_velocity.y = 0;
                  m_jumpCount = 1;
            }
      }

      if(IsKeyPressed(KEY_SPACE) && isGrounded || IsKeyPressed(KEY_SPACE) && m_jumpCount > 0)
      {
            m_velocity.y = NUMtoUNIT(-10);
            if(!isGrounded)
            {
                  m_jumpCount -= 1;
                  m_velocity.y = NUMtoUNIT(-10);
            }
      }

      //change slot 

      if(IsKeyPressed(KEY_ONE))
      {
            currentSlot = 0;
      }

      if(IsKeyPressed(KEY_TWO))
      {
            currentSlot = 1;
      }

      //change weapon
      if(IsKeyPressed(KEY_Q))
      {
            m_weaponSlots[currentSlot].weapon -= 1;
      }

      if(IsKeyPressed(KEY_E))
      {
            m_weaponSlots[currentSlot].weapon += 1;
      }

      //limit weapon selection
      if(m_weaponSlots[currentSlot].weapon > 1)
      {
            m_weaponSlots[currentSlot].weapon = 0;
      }
      if(m_weaponSlots[currentSlot].weapon < 0)
      {
            m_weaponSlots[currentSlot].weapon = 1;
      }

      // std::cout << m_velocity.x << "\n";
}

void Player::Draw()
{
      DrawTextureV(m_texture, m_position, WHITE);
}

void Player::DrawUI()
{
      DrawText(TextFormat("SLOT 1: %s", m_weaponSlots[0].weapon == 0 ? "FIRE" : "ELECTRICITY"), 0, 10, 25, BLUE);
      DrawText(TextFormat("SLOT 2: %s", m_weaponSlots[1].weapon == 0 ? "FIRE" : "ELECTRICITY"), 0, 40, 25, BLUE);
}
