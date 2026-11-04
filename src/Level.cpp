#include "headers/Level.hpp"

Vector2 Level::tsonVecToRayLib(tson::Vector2f vec)
{
      Vector2 newVec = (Vector2){vec.x, vec.y};
      return newVec;
}

Vector2 Level::tsonVecToRayLib(tson::Vector2i vec)
{
      Vector2 newVec = (Vector2){static_cast<float>(vec.x), static_cast<float>(vec.y)};
      return newVec;
}

Rectangle Level::tsonRectToRayLib(tson::Rect rect)
{
      Rectangle newRec = (Rectangle){rect.x, rect.y, rect.width, rect.height};
      return newRec;
}

void Level::LoadMap(std::string path)
{
      tson::Tileson t;
      std::unique_ptr<tson::Map> map = t.parse(path);
      if(map->getStatus() == tson::ParseStatus::OK)
      {
            tson::Tileset* tileset = map->getTileset("Test_set");
            fs::path imgPath = fs::path(path).parent_path() / tileset->getImagePath();

            std::string imgPathStr = imgPath.string();

            m_Tiles = LoadTexture(imgPathStr.c_str());

            for(auto& l : map->getLayers())
            {
                  if(l.getType() == tson::LayerType::TileLayer)
                  {
                        TileLayer layer;

                        layer.name = l.getName();
                        layer.alpha = (uint8_t)(l.getOpacity() * 255.0f);
                        layer.isVisible = l.isVisible();

                        for(auto[gPos, tileObj] : l.getTileObjects())
                        {
                              layer.tiles.push_back((Tile){tsonVecToRayLib(tileObj.getPosition()), tsonRectToRayLib(tileObj.getDrawingRect())});
                        }

                        tileLayers.push_back(std::move(layer));
                  }

                  if(l.getType() == tson::LayerType::ObjectGroup)
                  {
                        tson::Object* player = l.firstObj("PlayerStart");
                        playerStartPosition = tsonVecToRayLib(player->getPosition());
                  }
            }
      }
      else
      {
            if(map->getStatus() == tson::ParseStatus::FileNotFound)
            {
                  std::cout << "ERROR" << " " << "File not found!" << "\n";
            }

            if(map->getStatus() == tson::ParseStatus::ParseError)
            {
                  std::cout << "ERROR" << " " << "Error in parsing code" << "\n";
            }

            if(map->getStatus() == tson::ParseStatus::MissingData)
            {
                  std::cout << "ERROR" << " " << "File data is missing" << "\n";
            }
      }
}

Level::Level(std::string path)
{
      LoadMap(path);
}

Vector2 Level::GetPlayerStartPosition()
{
      return playerStartPosition;
}

void Level::Draw()
{
      for(auto l : tileLayers)
      {
            for(auto tile : l.tiles)
            {
                  DrawTextureRec(m_Tiles, tile.drawRect, tile.position, WHITE);
            }
      }
}
