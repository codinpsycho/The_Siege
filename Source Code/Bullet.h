#ifndef _BULLET__H_
#define _BULLET__H_

enum eBULLETID { 
				 ASSAULTRIFLE_BULLET,         // MASER CHIEF FIRES
				 SEMIAUTO_BULLET,
				 SHOTGUN_BULLET,
				 ROCKETLAUNCHER_BULLET,
				 ENEMYBULLET_TYPE1, // HUMAN SOLDIER FIRES
				 ENEMYBULLET_TYPE2, // ALIEN OF TYPE 1 FIRES
				 ENEMYBULLET_TYPE3, // ALIEN OF TYPE 2 FIRES
				 ENEMYBULLET_TYPE4  // ALIEN OF TYPE 3 FIRES
			   }; 

/*
#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>

class Bullet
{
	hgeSprite *spr;
	eBULLETID eID;
	bool bDead;
public:
	hgeVector vPosition;
	hgeVector vDirection;
	hgeVector vSpeed;
	Bullet(eBULLETID id, hgeVector v,hgeVector dir);
	~Bullet(void){delete spr;}
	 void Render();
	 void Move(float);	
	 bool Init(HGE*,HTEXTURE);
	 void Release();
	float GetHeight();
	float GetWidth();
	eBULLETID GetId();
	bool IsDead();
	void Die() { bDead = true; }
	float GetUpFace()    { return vPosition.y; }
	float GetDownFace()  { return (vPosition.y + spr->GetHeight()); }
	float GetLeftFace()  { return vPosition.x; }
	float GetRightFace() { return (vPosition.x + spr->GetWidth());  }
};

#endif

*/

#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgeparticle.h>
#include <hgerect.h>

class Bullet
{
	hgeSprite *spr;
	hgeSprite *PartSprite;
	//hgeRect *rect;
	eBULLETID eID;
	bool bDead;
public:
	hgeParticleSystem *part;
	hgeVector vPosition;
	hgeVector vDirection;
	hgeVector vSpeed;
	Bullet(eBULLETID id, hgeVector v,hgeVector dir);
	~Bullet(void);
	void Render();
	void Move(float);	
	bool Init(HGE*,HTEXTURE);
	void Release();
	float GetHeight();
	float GetWidth();
	eBULLETID GetId();
	bool IsDead();
	void Die() { bDead = true; }
	bool checkBound();
	float GetUpFace();    
	float GetDownFace();  
	float GetLeftFace();  
	float GetRightFace(); 

};

#endif

