#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
private:
      sf::Sprite m_sprite;
      sf::Texture m_texture;

      sf::Vector2f m_position;

      float m_accel, m_deccel;
public:
      Player(std::string pathToSprite, float acceleration, float decceleration);
      ~Player();

      void SetPosition(float x, float y);
      void SetPosition(sf::Vector2f newPos);
      void Update();
};
