#ifndef _LEVEL_OBJECTS_H_
#define _LEVEL_OBJECTS_H_

#pragma once
#include "hgeVector.h"
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgefont.h>


//Structure for Score up
struct ScoreUp 
{
	char *score;
	hgeFont* font_score;
	hgeVector position;
	bool show;
	float fade;
};


// types of particles used
enum eParticles { 
				  BLACK_SMOKE, BROWN_SMOKE, GREY_SMOKE, HIT_EFFECT, HIT_BLOOD, HIT_FIRE, HIT_FIRE_GREEN, HIT_FIRE_BLUE,HIT_FIRE_RED, 
				  JUMP_DUST, LAUNCHER_TRAIL, GUN_SPARK, BLAST,GRENADE_BLAST, BLAST_DEBRIS, LAUNCHER_SPARK, FEATHER_RED, FEATHER_BLUE, FEATHER_GREEN, FEATHER_PURPLE
				};
//When Scoring will be done
enum eScores {
				HUMAN_KILL,BIRD_KILL,BOX_MELEES,ENEMY_MELEES,ALIEN1_KILLS,ALIEN2_KILLS,ALIEN3_KILLS,BULLETS_WASTED,BULLET1_SUSTAINED,BULLET2_SUSTAINED,BULLET3_SUSTAINED,BULLET4_SUSTAINED,
			 }; 

/////////////////////////

//Structure for Leaves
struct Leaf
{
	hgeSprite *spr;
	hgeVector pos;
	hgeVector vel;
	hgeVector dir;
	float scale;
	float rotate;
	int id;
};
//Struct for Clouds
struct Cloud
{
	hgeSprite *spr;
	hgeVector pos;
	float fSpeedX;
	float scale;
	int id;
};
//Struct for bonus

enum eBONUS_ID{ AMMO_ASSAULTRIFLE, AMMO_SIDEARM, AMMO_SHOTGUN, AMMO_LAUNCHER, MEDIKIT, AMMO_GRENADE, BONUS_NOTHING };

class Bonus
{
	bool bDead;
	eBONUS_ID eID;	
	hgeSprite *spr;
  public:
    bool bHorFlip;
	hgeVector vPosition;
	
	Bonus( eBONUS_ID id, hgeVector pos );
	~Bonus();
	void SetHzFlip(bool);
	void Init(HTEXTURE);
	void Release();
	void Render();
	void Die();
	bool IsDead();
	eBONUS_ID GetId();
	float GetUpFace();	
	float GetDownFace();
	float GetRightFace();
	float GetLeftFace();
};

//Struct for Birds
enum eBirds { RED, BY, GREEN, PURPLE, BLUE};
struct Bird
{
	hgeAnimation *anim;
	hgeAnimation* falling;
	
	hgeVector Velocity;
	hgeVector Position;
	eBirds eId;
	int Direction;
	int iHealth;
	void die() { iHealth = 0; }
	bool IsDead()
	{
		if(iHealth <= 0)
			return false;
		else
			return true;
	}
	float GetLeftFace()
	{
		return Position.x;
	}

	float GetRightFace()
	{
		return Position.x + anim->GetHeight();
	}

	float GetUpFace()
	{
		return Position.y;
	}

	float GetDownFace()
	{
		return Position.y + anim->GetHeight();
	}



};
extern HGE *Engine;

class LevelObjects
{
	HTEXTURE Texture;
	int id;
	float fWidth,fHeight;
	bool collidable;
	bool destructable;
	bool dead;
	float fShiftX;
	float fShiftY;
	int Health;
	float rightFace;
	float downFace; 
public:
	float fWorldX,fWorldY;
	hgeSprite *Spr;
	float LeftFace,RightFace,UpFace,DownFace;
	bool bDamageFlag;
	LevelObjects(void);
	LevelObjects(int _id,HTEXTURE img,float _x,float _y,float w,float h,float wx,float wy);
	LevelObjects(int _id,HTEXTURE img,float _x,float _y,float w,float h,float wx,float wy,int coll,int destruct);
	~LevelObjects(void);
	void SetId(int i) { id = i; }
	void Update();
	void Render();
	void ShiftPosX(float x,float dir);
	void ShiftPosY(float y,float dir);
	int GetHealth();
	void DecreaseHealth(int x);
	bool IsDead();
	void SetDead();
	void SetAlive();
	void SetCollidable(bool flag);
	void SetDestructible(bool flag);
	void SetImage(HTEXTURE tex);
	float GetUpFace();	
	float GetDownFace();
	float GetRightFace();
	float GetLeftFace();
	void SetHealth(int h) {Health=h;}
	inline int GetId()const {  return id;} 
	inline bool IsCollidable() { return collidable; }
	inline bool IsDestructable() { return destructable; }
	void Die() {dead = true; Health = 0; }
	inline void Release() {   delete Spr; Spr = 0;  }
};
#endif