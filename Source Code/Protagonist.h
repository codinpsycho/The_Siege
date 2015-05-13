/*
#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_
#pragma once

#include "player.h"
#include "Weapon.h"
#include <hge.h>
#include <hgeanim.h>
#include <hgeVector.h>
#include "Timer.h"


class Protagonist :	public Player
{
		       int iGrenades; 
	ePLAYER_STANCE eCURRENTSTANCE;
	ePLAYER_STANCE eFACING;
	      eWEAPONS eCURRENTWEAPON;
          HTEXTURE Texture[2];
		  hgeAnimation *MainAnimation;
		  hgeAnimation *SpriteSheet[2];
protected:
		  void SetAnimation( ePLAYER_STANCE  );
		  void Play();
		  void Update();
public:
	Weapon PrimaryWeapon;       // primary weapon
	Weapon SecondaryWeapon;	   // secondary weapon	
	hgeVector vLength;

	Protagonist( );
	virtual ~Protagonist( );
	void Render() const;
	void SelectPrimaryWeapon( );
	void SelectSecondaryWeapon( );
	bool Init( HGE *hge);
	void Update( HGE *,float ftime );
	void ChangeStance(ePLAYER_STANCE eSTANCE);
	void Setcolor(DWORD Col,int i=-1) {  MainAnimation->SetColor(Col,i); } 
	virtual void Die();
	void SetFacing( ePLAYER_STANCE eFACE,bool );
	void Release(HGE*);
	void ChangeWeapon(eWEAPONS weapon);  //////// Temporary Method suppose to be removed
	void SetZdepth(float Z,int i=-1);
	bool SwapWeapon(WeaponObject*, HGE*);
	void Move(float);

	ePLAYER_STANCE GetFacing() const;
	float GetHeight() const;
	ePLAYER_STANCE GetStance() const;
	int GetFrame() {return MainAnimation->GetFrame(); }
	eWEAPONS GetWeapon() const  { return eCURRENTWEAPON;   }
	float GetUpFace()    const  { return vPosition.y;      }
	float GetDownFace()  const  { return vPosition.y+140;  }
	float GetLeftFace()  const  { return vPosition.x;	   }
	float GetRightFace() const  { return vPosition.x+120;  }
	int CurFrame() { return MainAnimation->GetFrame();}
	bool IsPlaying() { return MainAnimation->IsPlaying();  }
	bool FireWeapon();

};


#endif
*/

#ifndef _PROTAGONIST_H_
#define _PROTAGONIST_H_
#pragma once

#include "player.h"
#include "Weapon.h"
#include <hge.h>
#include <hgeanim.h>
#include <hgeVector.h>
#include "Timer.h"

enum CONDITION{ 
	ON_THE_GROUND, 
	IN_THE_AIR, 
	ON_THE_OBJECT 
};

class Protagonist :	public Player
{
	int iGrenades; 
	ePLAYER_STANCE eCURRENTSTANCE;
	ePLAYER_STANCE eFACING;
	eWEAPONS eCURRENTWEAPON;
	HTEXTURE Texture[2];
	hgeAnimation *SpriteSheet[2];
protected:
	void SetAnimation( ePLAYER_STANCE  );
	void Play();
	void Update();
public:
	hgeAnimation *MainAnimation;
	Weapon* pCurrentWeapon;
	Weapon AssaultRifle;       
	Weapon SideArm;			
	Weapon ShotGun;
	Weapon RocketLauncher;
	hgeVector vLength;

	Protagonist( );
	virtual ~Protagonist( );
	void Render() const;
	void SelectAssaultRifle( );
	void SelectSideArm( );
	void SelectShotGun( );
	void SelectRocketLauncher( );

	bool Init( HGE *hge);
	void Update( HGE *,float ftime );
	void ChangeStance(ePLAYER_STANCE eSTANCE);
	void Setcolor(DWORD Col,int i=-1) {  MainAnimation->SetColor(Col,i); } 
	virtual void Die();
	void SetFacing( ePLAYER_STANCE eFACE,bool );
	void Release(HGE*);
	void ChangeWeapon(eWEAPONS weapon);  //////// Temporary Method suppose to be removed
	void SetZdepth(float Z,int i=-1);
	bool SwapWeapon(WeaponObject*, HGE*);
	void Move(float);
	virtual void LowerHealth(int h);


	void LowerGrenades()
	{
		iGrenades-=1;
		if( iGrenades <= 0 )
			iGrenades = 0;
	}
	bool ThrowGrenade()	
	{
		if( iGrenades > 0 ) return true;
	  return false;	
	}	

	ePLAYER_STANCE GetFacing() const;
	float GetHeight() const;
	ePLAYER_STANCE GetStance() const;
	int GetFrame() {return MainAnimation->GetFrame(); }
	eWEAPONS GetWeapon() const  { return eCURRENTWEAPON;   }
	float GetUpFace()    const  { return vPosition.y;      }
	float GetDownFace()  const  { return vPosition.y+140;  }
	float GetLeftFace()  const  { return vPosition.x;	   }
	float GetRightFace() const  { return vPosition.x+120;  }
	int CurFrame() { return MainAnimation->GetFrame();}
	bool IsPlaying() { return MainAnimation->IsPlaying();  }
	bool FireWeapon();
	eWEAPONS GetWeaponId();
	int GetWeaponAmmo();
	Weapon& GetCurrentWeapon() {  return *pCurrentWeapon;	}
	void RaiseGrenade(int ig)
	{
		iGrenades += ig;
		if (iGrenades >= 6)
		{
			iGrenades = 6;
		}
	}
	int GetGrenade()
	{
		return iGrenades;
	}
};


#endif