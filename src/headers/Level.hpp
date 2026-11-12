#pragma once
#include "thirdParty/tileson.hpp"
#include "BackGround.hpp"
#include "Object.hpp"
#include <raylib.h>

class Level
{
private:
      struct Tile
      {
            Vector2 position;
            Rectangle drawRect;
      };

      struct TileLayer
      {
            std::string name;
            float paralaxFactor;
            uint8_t alpha;
            bool isVisible;
            std::vector<Tile> tiles;
      };

      Vector2 tsonVecToRayLib(tson::Vector2f vec);
      Vector2 tsonVecToRayLib(tson::Vector2i vec);
      Rectangle tsonRectToRayLib(tson::Rect rect);

      std::vector<TileLayer> tileLayers;
      std::vector<std::unique_ptr<IObject>> objects;
      std::vector<std::unique_ptr<IObject>> spawnedObjects; //сначало объекты спавнятся там, нужен для предотврощения утечек памяти
      std::vector<Rectangle> m_collisionBoxes;
      std::vector<BackGround*> m_BGs;

      void LoadMap(std::string path);

      Vector2 playerStartPosition;

      Texture2D m_Tiles;

      int totalObjects;
      
public:
      Level(std::string path);
      Vector2 GetPlayerStartPosition();
      void RegesterObject(std::unique_ptr<IObject> object);
      void RemoveDeadObjects();
      void AcceptObjects();
      void DrawDebugRects();
      void DrawBG();
      void DrawBG(float scaleFactor);
      void DrawBG(float scaleX, float scaleY);
      std::vector<std::unique_ptr<IObject>>& getObjects();
      std::vector<Rectangle>& GetCollisions();
      void Draw();
      ~Level() = default;
};
