#include "headers/Game.hpp"
#include <raymath.h>

Game::Game() : m_player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12)), lvl("assets/Levels/Test/level.json")
{
      m_player.SetPosition(lvl.GetPlayerStartPosition());
      m_cam = {0};
}

void Game::Start()
{
      projPos = m_player.GetPosition();
      lvl.RegesterObject(std::make_unique<IObject>(Vector2{40, 40}, "assets/Test.png", 40, 40, 80, 80));
}

void Game::Update()
{
      Vector2 projVec;
      Vector2 mousePos;
      Vector2 scrMousePos;
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
            mousePos = GetMousePosition();
            scrMousePos = GetScreenToWorld2D(mousePos, m_cam);

            Vector2 Dir = Vector2Subtract(scrMousePos, m_player.GetPosition());

            Vector2 nDir = Vector2Normalize(Dir);

            float speed = 30.0f;
            projVec = Vector2Scale(nDir, speed);
      }

      projPos.x += projVec.x * GetFrameTime();
      projPos.y += projVec.y * GetFrameTime();

      for(auto& obj : lvl.getObjects())
      {
            obj->Update(GetFrameTime());
      }
      m_player.Update();

      lvl.RemoveDeadObjects();

      m_cam.target = (Vector2){m_player.GetPosition().x, m_player.GetPosition().y};
      m_cam.offset = (Vector2){800/2, 600/2};
      m_cam.rotation = 0.0f;
      m_cam.zoom = 2.0f;

      BeginDrawing();
            ClearBackground(BLUE);
            BeginMode2D(m_cam);
                  lvl.Draw();
                  DrawCircle(projPos.x, projPos.y, 10, RED);
                  for(auto& obj : lvl.getObjects())
                  {
                        obj->Draw();
                  }
                  m_player.Draw();
            EndMode2D();
            DrawText(TextFormat("player vel: X: %f, Y: %f", m_player.GetVelocity().x, m_player.GetVelocity().y), 0, 30, 25, BLACK);
            DrawText(TextFormat("player pos: X: %f, Y: %f", m_player.GetPosition().x, m_player.GetPosition().y), 0, 50, 25, BLACK);
            DrawText(TextFormat("mouse pos: X: %f, Y: %f", mousePos.x, mousePos.y), 0, 70, 25, BLACK);
      EndDrawing();
}
