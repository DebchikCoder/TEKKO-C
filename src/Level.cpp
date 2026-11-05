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
      std::unique_ptr<tson::Map> map = t.parse(path); //parsing map
      if(map->getStatus() == tson::ParseStatus::OK)
      {
            //loading TileSet image
            tson::Tileset* tileset = map->getTileset("Test_set");
            fs::path imgPath = fs::path(path).parent_path() / tileset->getImagePath();

            std::string imgPathStr = imgPath.string();

            m_Tiles = LoadTexture(imgPathStr.c_str());

            //get layer data
            for(auto& l : map->getLayers())
            {
                  if(l.getType() == tson::LayerType::TileLayer)
                  {
                        TileLayer layer;

                        layer.name = l.getName();
                        layer.alpha = (uint8_t)(l.getOpacity() * 255.0f);
                        layer.isVisible = l.isVisible();

                        //loading Tiles
                        for(auto[gPos, tileObj] : l.getTileObjects())
                        {
                              layer.tiles.push_back((Tile){tsonVecToRayLib(tileObj.getPosition()), tsonRectToRayLib(tileObj.getDrawingRect())});
                        }

                        tileLayers.push_back(std::move(layer));
                  }

                  //loading Objects
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
                  std::cout << "ERROR" << " " << "File is missing" << "\n";
            }
      }
}

Level::Level(std::string path)
{
      LoadMap(path);
      totalObjects = 0;
}

Vector2 Level::GetPlayerStartPosition()
{
      return playerStartPosition;
}

void Level::RegesterObject(std::unique_ptr<IObject> object)
{
      objects.push_back(std::move(object));
}

void Level::RemoveDeadObjects()
{
      std::erase_if(objects, [](const std::unique_ptr<IObject>& o){return o->isDead();});
}

std::vector<std::unique_ptr<IObject>> &Level::getObjects()
{
    return objects;
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
