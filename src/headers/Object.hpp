#pragma once

#include <raylib.h>
#include <string>

class IObject
{
protected:
      Vector2 m_position;
      Texture2D m_texture;

      Rectangle m_hitBox;
public:
      IObject(Vector2 position, std::string TexturePath, float BBx, float BBy, float BBw, float BBh);
      virtual void Update(float dt);
      virtual void Draw();
      Vector2 getPosition();
      Texture2D getTexture();
      Rectangle getHitBox();
      virtual ~IObject();
};