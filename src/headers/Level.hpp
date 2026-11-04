#pragma once
#include "thirdParty/tileson.hpp"
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

      void LoadMap(std::string path);

      Vector2 playerStartPosition;

      Texture2D m_Tiles;
      
public:
      Level(std::string path);
      Vector2 GetPlayerStartPosition();
      void Draw();
      ~Level() = default;
};
