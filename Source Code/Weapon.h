#ifndef _WEAPON_H_ 
#define _WEAPON_H_
#pragma once

#include <hge.h>
#include <hgesprite.h>
#include "Player.h"
#include "Timer.h"

enum eWEAPONS {
	ASSAULTRIFLE,	
	SEMIAUTO,
	SHOTGUN,
	ROCKETLAUNCHER,
	GRENADE,							 	 	
	SNIPER,
	LAUNCHER_GRENADE,
};

enum eWEAPONTYPE{ PRIMARY,SECONDARY };

class Weapon
{
protected:
	eWEAPONS eID;      // identity 
	int iAmmo;		   // total bullets
	int MaxBullets;
	eWEAPONTYPE eWEAPONCLASS; 
	Timer FireBullet;
	clock_t RateOfFire; 
	bool bFireFlag;
	HEFFECT hWeaponEmpty;
public:
			
	enum { 
		   ASSAULTRIFLE_LIMIT = 160, SEMIAUTO_LIMIT = 210, 
		   SHOTGUN_LIMIT = 60, ROCKETLAUNCHER_LIMIT = 6  
		 };
	 Weapon(eWEAPONS id,eWEAPONTYPE ewClass);
	 ~Weapon(){}
     int GetAmmo() const					{ return iAmmo;		   }
	 eWEAPONTYPE GetWeaponClass() const     { return eWEAPONCLASS; }
	 eWEAPONS GetWeaponID() const 			{ return eID;          }
	 void SetAmmo(int am)					{ iAmmo = am;		   }
	 void SetWeaponClass(eWEAPONTYPE wep)	{ eWEAPONCLASS = wep;  }	
	 void SetWeaponID(eWEAPONS id);
	 void ResetFireRates();
	 int RaiseAmmo(int am);
	 bool Fire() ;
	 bool IsFull() { return (iAmmo == MaxBullets)? true: false;     }
	 bool IsEmpty() { return (iAmmo <= 0) ? true:false; }
	 void SetFiringRate(clock_t p) { RateOfFire=p; FireBullet.setEndTime(RateOfFire); }
};

///////////////////////  WeaponObject //////////////////

class WeaponObject: public Weapon
{  
	float fSpeedX;	       // speed at which the weapon moves in the environment
	bool bDead;
    float height;
	float width;
    public:	
	hgeVector vDirection;  // direction of weapon
	hgeVector vPosition;   // position of weapon in the atmosphere
	hgeSprite *sprite;     // this is the image of the weapon
	HTEXTURE hTexture;
	
	WeaponObject(eWEAPONS id,eWEAPONTYPE wClass,float speed, hgeVector& pos, hgeVector& dir);
	WeaponObject( const WeaponObject& );
   ~WeaponObject();
    void Init(HGE* Engine,HTEXTURE hTex);
	void Render();
	void Move(float);
	float GetUpFace()    { return vPosition.y; }
	float GetDownFace()  { return vPosition.y + height; } 
	float GetRightFace() { return vPosition.x + width;  }
	float GetLeftFace()  { return vPosition.x; }	
	HTEXTURE GetTexture() { return hTexture; }
	void Release(); 
	WeaponObject& operator = (const Weapon&);
	WeaponObject& operator = (const WeaponObject& );
	void ReInit(HGE*);
	void SwapWeapon(Weapon&);
	bool IsDead() { return bDead; }
	void Die() { this->bDead = true; }
};



class Grenade
{
	bool bDead;
	float height;
	float width;
	hgeSprite *sprite;     // this is the image of the weapon
	Timer Launch;
	eWEAPONS eId; 
	float fScale,fVscale;
public:	
	
	float fRotate;
	hgeVector vSpeed;	   // speed at which the weapon moves in the environment
	hgeVector vDirection;  // direction of weapon
	hgeVector vPosition;   // position of weapon in the atmosphere
	bool bounceFlag;
	
	Grenade(const hgeVector &pos , const hgeVector &dir, eWEAPONS id = GRENADE );
    ~Grenade();
	void Init(HTEXTURE hTex);
	void Release();
	void Render();
	void Move(float dt);
	bool Explode() const;
	eWEAPONS GetId() {return eId; }

};


#endif