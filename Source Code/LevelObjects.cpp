/* GAME MEACHANICS PRESENTATION ----> THE SIEGE
FOR EDUCATIONL PURPOSE ONLY
GAME PROGRAMMERS ----> ISHKARAN SINGH (AsS^Ss!n)
SHANKER SHARMA (KING SEAN)
COTACT---->
ISHKARAN SINGH : ishkaran.fearme@gmail.com
ishkaran.singh@hotmail.com
SHANKER SHARMA : igamer_1990@yahoo.com

GAME MECHANICS : gamemechanics.studio@gmail.com

THIS IS GAME MECHANICS FIRST GAME AND WE ARE STILL IN LEARNING PROCESS
JUST TRYING TO PROVE OUR INTENSE PASSION AND ZEAL TOWARDS GAME PROGRAMMING AND CREATING
QUALITY AND CREATIVE GAMES.
*/



#include "LevelObjects.h"

LevelObjects::LevelObjects(void)
{
	collidable = false;
	destructable = false;
	Health = 100;
	dead = true;
	bDamageFlag=false;
}

LevelObjects::~LevelObjects(void)
{

}

LevelObjects::LevelObjects(int _id,HTEXTURE img,float _x,float _y,float w,float h,float wx,float wy,int coll,int destruct)
{
	if (coll)
	{
		collidable = true;
	}
	else
		collidable = false;

	if (destruct)
	{
		destructable = true;
	}
	else
		destructable = false;
	fWidth = w;
	fHeight = h;
	Spr = new hgeSprite(img,_x,_y,w,h);
	LeftFace = _x;
	RightFace = _x + fWidth;
	UpFace = _y;
	DownFace = _y + fHeight;
	fWorldX = wx;
	fWorldY = wy;
	Health = 100;
	id = _id;
	dead = false;
	bDamageFlag=false;
}

LevelObjects::LevelObjects(int _id,HTEXTURE img,float _x,float _y,float w,float h,float wx,float wy)
{

	id = _id;
	collidable = true;
	destructable = false;
	fWidth = w;
	fHeight = h;
	Spr = new hgeSprite(img,_x,_y,w,h);
	LeftFace = _x;
	RightFace = _x + fWidth;
	UpFace = _y;
	DownFace = _y + fHeight;
	fWorldX = wx;
	fWorldY = wy;
	Health = 100;
	dead = false;
	bDamageFlag=false;
}

void LevelObjects::Render()
{
	Spr->Render(fWorldX,fWorldY);
}

void LevelObjects::ShiftPosX(float x,float dir)
{
	fWorldX += x*dir;
}

void LevelObjects::ShiftPosY(float y,float dir)
{
	fWorldY += y*dir;
}

int LevelObjects::GetHealth()
{
	return Health;
}

void LevelObjects::DecreaseHealth(int x)
{	
	 Health -= x;
	 if( Health <= 0 ) 
	 { 
		 Health=0;
		 dead = true;
	 }
}

bool LevelObjects::IsDead()
{
	if (Health <= 0)
	{
		dead = true;
		return true;
	}
	return dead;

}
void LevelObjects::SetDead()
{
	dead = true;
}

void LevelObjects::SetAlive()
{
	dead = false;
}

void LevelObjects::SetCollidable(bool flag)
{
	collidable = flag;
}

void LevelObjects::SetDestructible(bool flag)
{
	destructable = flag;
}

void LevelObjects::SetImage(HTEXTURE tex)
{
	delete Spr;
	Spr = new hgeSprite(tex,0,0,fWidth,fHeight);
	
}

float LevelObjects::GetUpFace()
{
  return fWorldY;
}


float LevelObjects::GetDownFace()
{
  return fWorldY+fHeight;	
}

float LevelObjects::GetLeftFace()
{
	return fWorldX;
}

float LevelObjects::GetRightFace()
{
	return fWorldX+fWidth;
}

////////////////////////////////////////////

Bonus::Bonus(eBONUS_ID id, hgeVector pos)
{
	spr = 0;
	vPosition = pos;
	bDead=false;
	bHorFlip=false;
	eID=id;	
}

Bonus::~Bonus()
{
  delete spr;
}

void Bonus::Render()
{
   if(bHorFlip)	spr->SetFlip(bHorFlip,false);	
   spr->Render(vPosition.x,vPosition.y);
}

void Bonus::Init(HTEXTURE hTex)
{
	switch(eID)
	{
	 case AMMO_ASSAULTRIFLE: spr = new hgeSprite(hTex,0,0,59,24); 	  break;
	 case AMMO_SIDEARM:		 spr = new hgeSprite(hTex,62,0,24,21);    break;
	 case AMMO_SHOTGUN:  	 spr = new hgeSprite(hTex,91,0,73,23);    break;
	 case AMMO_LAUNCHER:     spr = new hgeSprite(hTex,166,0,84,26);   break;
	 case AMMO_GRENADE:		 spr = new hgeSprite(hTex,0,30,13,13);    break;
 	 case MEDIKIT:			 spr = new hgeSprite(hTex,200,40,31,21);  break;
	}
}

void Bonus::Release()
{
   delete spr;
}

void Bonus::Die()		  { bDead = true; }
bool Bonus::IsDead()	  { return bDead; }
eBONUS_ID Bonus::GetId()  { return  eID;  }  
float Bonus::GetUpFace()   {return vPosition.y; }
float Bonus::GetDownFace() {return ( vPosition.y+spr->GetHeight() ); }
float Bonus::GetRightFace(){return ( vPosition.x+spr->GetWidth() ); }
float Bonus::GetLeftFace() {return vPosition.x; }
 void Bonus::SetHzFlip(bool hz) { bHorFlip=hz; }