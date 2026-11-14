#include "headers/Game.hpp"
#include <raymath.h>

Game::Game() : m_player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12), NUMtoUNIT(18)), lvl("assets/Levels/Test/level.json")
{
      m_player.SetPosition(lvl.GetPlayerStartPosition().x - (48/2), lvl.GetPlayerStartPosition().y - (78/2));
      m_cam = {0};
}

void Game::Start()
{
      // lvl.RegesterObject(std::make_unique<IObject>(Vector2{40, -20}, "assets/Test.png", 40, 40, 80, 80));
}

void Game::Update()
{
      for(auto& obj : lvl.getObjects())
      {
            obj->CheckCollision(lvl.GetCollisions());
            obj->Update(GetFrameTime());
      }
      m_player.Update(m_cam, lvl.GetCollisions());

      if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
            lvl.RegesterObject(m_player.Shoot(m_cam, NUMtoUNIT(10.0f)));
      }

      lvl.AcceptObjects();
      lvl.RemoveDeadObjects();

      m_cam.target = (Vector2){m_player.GetPosition().x, m_player.GetPosition().y};
      m_cam.offset = (Vector2){800/2, 600/2};
      m_cam.rotation = 0.0f;
      m_cam.zoom = 2.0f;

      BeginDrawing();
            ClearBackground(BLUE);
            lvl.DrawBG(2.5f, 2.8f);
            BeginMode2D(m_cam);
                  lvl.Draw();
                  for(auto& obj : lvl.getObjects())
                  {
                        obj->Draw();
                  }
                  m_player.Draw();
            EndMode2D();
            m_player.DrawUI();
      EndDrawing();
}
