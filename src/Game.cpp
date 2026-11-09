#include "headers/Game.hpp"
#include <raymath.h>

Game::Game() : m_player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12)), lvl("assets/Levels/Test/level.json")
{
      m_player.SetPosition(lvl.GetPlayerStartPosition().x - (48/2), lvl.GetPlayerStartPosition().y - (78/2));
      m_cam = {0};
}

void Game::Start()
{
      lvl.RegesterObject(std::make_unique<IObject>(Vector2{40, 40}, "assets/Test.png", 40, 40, 80, 80));
}

void Game::Update()
{
      for(auto& obj : lvl.getObjects())
      {
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
            BeginMode2D(m_cam);
                  lvl.Draw();
                  for(auto& obj : lvl.getObjects())
                  {
                        obj->Draw();
                  }
                  m_player.Draw();
                  lvl.DrawDebugRects();
            EndMode2D();
            DrawText(TextFormat("player vel: X: %f, Y: %f", m_player.GetVelocity().x, m_player.GetVelocity().y), 0, 30, 25, BLACK);
            DrawText(TextFormat("player pos: X: %f, Y: %f", m_player.GetPosition().x, m_player.GetPosition().y), 0, 50, 25, BLACK);
            DrawText(TextFormat("FPS: %d", GetFPS()), 0, 90, 25, BLACK);
      EndDrawing();
}
