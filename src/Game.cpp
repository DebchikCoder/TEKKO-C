#include "headers/Game.hpp"

Game::Game() : m_player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12))
{
}

void Game::Start()
{
      objects.push_back(std::make_unique<IObject>(Vector2{40, 40}, "assets/Test.png", 40, 40, 80, 80));
}

void Game::Update()
{
      BeginDrawing();
            ClearBackground(BLUE);
            for(auto& obj : objects)
            {
                  obj->Update(GetFrameTime());
                  obj->Draw();
            }
            m_player.Update();
      EndDrawing();
}
