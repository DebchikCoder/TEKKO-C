#include "headers/Game.hpp"

Game::Game() : m_player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12)), lvl("assets/Levels/Test/level.json")
{
      m_player.SetPosition(lvl.GetPlayerStartPosition());
      m_cam = {0};
}

void Game::Start()
{
      objects.push_back(std::make_unique<IObject>(Vector2{40, 40}, "assets/Test.png", 40, 40, 80, 80));

}

void Game::Update()
{
      for(auto& obj : objects)
      {
            obj->Update(GetFrameTime());
            m_player.Update();
      }

      m_cam.target = (Vector2){m_player.GetPosition().x, m_player.GetPosition().y};
      m_cam.offset = (Vector2){800/2, 600/2};
      m_cam.rotation = 0.0f;
      m_cam.zoom = 2.0f;

      BeginDrawing();
            ClearBackground(BLUE);
            BeginMode2D(m_cam);
                  lvl.Draw();
                  for(auto& obj : objects)
                  {
                        obj->Draw();
                        m_player.Draw();
                  }
            EndMode2D();
      EndDrawing();
}
