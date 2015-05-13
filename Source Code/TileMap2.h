#ifndef _TILE_MAP_2_H_
#define _TILE_MAP_2_H_

#include <hgesprite.h>

enum IDFIRST
{
  TREE_DESTROYED,
  TREE,
  CAR,
  ROCKS,
  GRAVELS,
  SMALLGRASS,
  BUSH,
  BUSHES,
  MEDIUM_GRASS,
  LARGE_GRASS,
  SMALL_BUSHES,
  NIGHT_GRASS_SMALL,
  NIGHT_GRASS_MEDIUM,	
  No_Obj_Picked,
  H_SPACE_5_PIX,
  H_SPACE_10_PIX,
  H_SPACE_100_PIX,
  H_SPACE_500_PIX,
  H_SPACE_1000_PIX,
};

class ObjectLevel
{
public:
	hgeSprite* Sprite; 
	float x,y,w,h;
	IDFIRST ObjId;	
	ObjectLevel()  { Sprite = 0;			  }
	~ObjectLevel() { delete Sprite;	Sprite=0; }
	void Render()  { Sprite->Render(x,y);	  }
	void Release() { delete Sprite; Sprite=0; }
	float GetRightFace() { return x+Sprite->GetWidth(); }
};

void LoadObjects(std::vector<ObjectLevel*> &List,IDFIRST Objects[] ,const int SIZEOBJ, const float GROUND, HTEXTURE );

#endif