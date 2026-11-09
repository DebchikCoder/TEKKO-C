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
      Rectangle newRec = (Rectangle){static_cast<float>(rect.x), static_cast<float>(rect.y), static_cast<float>(rect.width), static_cast<float>(rect.height)};
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
                              //loading collisions
                              auto tileLayer = tileObj.getTile();
                              auto col = tileLayer->getObjectgroup();
                              for(auto colObj : col.getObjects())
                              {
                                    Rectangle rect;
                                    Vector2 xyRect = tsonVecToRayLib(tileObj.getPosition());
                                    Vector2 whRect = tsonVecToRayLib(colObj.getSize());
                                    rect = (Rectangle){xyRect.x, xyRect.y, whRect.x, whRect.y};
                                    m_collisionBoxes.push_back(rect);
                              }
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
      TraceLog(LOG_INFO, TextFormat("collision Recs: %d", m_collisionBoxes.size()));
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
      spawnedObjects.push_back(std::move(object));
}

void Level::RemoveDeadObjects()
{
      std::erase_if(objects, [](const std::unique_ptr<IObject>& o){return o->isDead();});
}

void Level::AcceptObjects()
{
      for(auto& o : spawnedObjects)
      {
            objects.push_back(std::move(o));
      }
      spawnedObjects.clear();
}

void Level::DrawDebugRects()
{
      for(auto obj : m_collisionBoxes)
      {
            DrawRectangleLinesEx(obj, 3, PURPLE);
      }
}

std::vector<std::unique_ptr<IObject>> &Level::getObjects()
{
    return objects;
}

std::vector<Rectangle> &Level::GetCollisions()
{
      return m_collisionBoxes;
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
