#pragma once
#include <hgesprite.h>
#include "LevelObjects.h"
#include <vector>

using namespace std;


class TileMap
{
	
	HTEXTURE tex;
	const char* file;
	hgeSprite* tile;
	int iTileXCount;
	int iTileYCount;
	float fTileWidth;
	float fTileHeight;
	float fTileShift;
	int* data;
	int xPos,yPos;
	float fImageWidth;
	float fImageHeight;
	float rectX,rectY;
	int iHeight1;
	int iHeight2;
	int iHeight3;
	int iHeight4;
	int iExtraSpace;
	int iGiveExtraSpace;
	int iCollidable;
	int iDestructable;

protected:
	void SetXY(int index);
	void SetHeight(int index);


public:
	TileMap(void);
	std::vector<LevelObjects> Objects;
	void CreateLevel(); //if you want to push LevelObjects object into link list
	void Move(float speed,float dir);//To move the World
	void Read(const char *text);
	void SetPos(int x,int y);
	void setTileShift(float shift);
	void SetTileImage(HTEXTURE tex);
	void Render();
	void Release();
	

	~TileMap(void);
};


