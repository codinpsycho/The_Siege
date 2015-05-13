#pragma once
#include <hge.h>
#include "hgevector.h"
extern HGE *Engine;

class sprite
{
	hgeVector cordinates;
	hgeVector velocity;
	hgeVector dir;
	hgeQuad quad;
	float fHeight;
	float fWidth;
public:
	sprite(void);
	sprite( float x, float y, float width, float height );
	//void LoadTexture ( char * );
	void LoadTexture ( HTEXTURE );
	void Render(float x, float y);
	float retLeftFace();
	float retDownFace();
	float retUpFace();
	float retRightFace();
	void setX(float x);
	void setY(float y);
	void update();
	void moveX(float dt);
	void moveY(float dt);
	void scaleX(float sx);
	void scaleY(float sy);
	void setSpeedX(float s);
	void setSpeedY(float s);
	void tileX(float tx);
	void tileY(float ty);
	void flipX();
	void flipY();
	void CurrentVertices (float &x , float &y, float &width, float &height);
	void RotateClockwise ();
	void RotateCounterClockwise ();
	void setDirX(int d);
	void setDirY(int d);
	void scrollY(float speed,float dir);
	int setColorVertex(int a,int r,int g,int b,int vertex);
	int setColor(int a,int r,int g,int b);
	void scrollX(float speed,float dir);
	void makeBlacWhite(int shade);
	hgeVector getPosition();
	hgeVector getDir();
	hgeVector getVelocity();
	void  setDir(hgeVector v);
	void setVelocity(hgeVector v);
	void setCordinates(hgeVector v);
	void setWidth(float width);
	void setHeight(float height);
	void SetZ(float z);
	
	~sprite(void);
};
