#pragma once
#include "thirdParty/tileson.hpp"
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
            int8_t alpha;
            bool isVisible;
            std::vector<Tile> tiles;
      };

      Vector2 tsonVecToRayLib(tson::Vector2f vec);
      Vector2 tsonVecToRayLib(tson::Vector2i vec);
      Rectangle tsonRectToRayLib(tson::Rect rect);

      std::vector<TileLayer> tileLayers;
      std::vector<std::unique_ptr<IObject>> objects;

      void LoadMap(std::string path);

      Vector2 playerStartPosition;

      Texture2D m_Tiles;

      int totalObjects;
      
public:
      Level(std::string path);
      Vector2 GetPlayerStartPosition();
      void RegesterObject(std::unique_ptr<IObject> object);
      void DeleteObject(int id);
      std::vector<std::unique_ptr<IObject>>& getObjects();
      void Draw();
      ~Level() = default;
};
