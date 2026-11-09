#pragma once

#include <raylib.h>
#include <vector>
#include <memory>
#include "Object.hpp"
#include "Player.hpp"
#include "Level.hpp"

class Game
{
private:
      Player m_player;
      Level lvl;

      Camera2D m_cam;
public:
      Game();
      void Start();
      void Update();
      ~Game() = default;
};