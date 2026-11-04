#pragma once

#include <raylib.h>
#include <vector>
#include <memory>
#include "Object.hpp"
#include "Player.hpp"

class Game
{
private:
      //FIXME!: надо перенести в Level класс
      std::vector<std::unique_ptr<IObject>> objects;
      Player m_player;
public:
      Game();
      void Start();
      void Update();
      ~Game() = default;
};