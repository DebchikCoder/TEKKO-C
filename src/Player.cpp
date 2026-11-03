#include "headers/Player.hpp"

Player::Player(std::string pathToSprite, float acceleration, float decceleration) : m_sprite(m_texture)
{
      m_texture.loadFromFile(pathToSprite);
      m_accel = acceleration;
      m_deccel = decceleration;
}

Player::~Player()
{
      m_position = sf::Vector2f(0, 0);
      m_accel = 0;
      m_deccel = 0;
      //i think its kinda dangerous
      delete &m_texture;
      delete &m_sprite;
}
