#ifndef _ENEMY_H_
#define _ENEMY_H_
#pragma once

#include "player.h"
#include <hge.h>
#include <hgeanim.h>
#include <hgeVector.h>
#include <vector>
#include "Timer.h"
#include "dialog.h"

enum eENEMY
{
	HUMAN=0,
	ALIEN1,
	ALIEN2,
	ALIEN3
};


enum eARTIFICIAL_INTELLIGENCE
{
	ATTACK,
	CHASE,
	STRATEGY,
	ADJUSTLEFT,
	ADJUSTRIGHT,
	RETREAT
};

class Enemy: public Player
{
	eENEMY eID;
	ePLAYER_STANCE eFACING; // right or left
	ePLAYER_STANCE eCURRENTSTANCE; // running, firing etc
	Timer FireBullet;
	clock_t FireRate;
	bool bStanceChangeCapability; 
	Timer StanceTimer;
	hgeSprite *Speaker;
	Timer ShowSpeaker;
	bool bShowSpeakerFlag;
	bool bFireFlag;
protected:
	void SetAnimation( ePLAYER_STANCE  );
public:
	 bool grenadeFlag;
	 bool meleeFlag;
	Timer Melee,UseGrenade;
	hgeAnimation *anim;
	hgeSprite* healthbar;
	float fAdjVal;
	eARTIFICIAL_INTELLIGENCE eAI_STATE, ePREVIOUS_AI_STATE;
    
	eVOICE_TYPE eENEMY_VOICE;
	Timer SpeakTimer;
	bool bSpeakFlag;

	Enemy(eENEMY id,ePLAYER_STANCE eface,ePLAYER_STANCE eStance,hgeVector vPos,hgeVector vDir);
	virtual ~Enemy();
	bool Init(HGE*,HTEXTURE,HTEXTURE);	
	void Release();
	void Update(float fTime);
	void updatehealthbar(float dt);
	void renderhealthbar();
	void Render();
	virtual void Die();
	void SetFacing(ePLAYER_STANCE);
	ePLAYER_STANCE GetFacing() const;
	eENEMY GetId() const;
	ePLAYER_STANCE GetStance() const { return eCURRENTSTANCE; }
	void ChangeStance(ePLAYER_STANCE eSTANCE);
	void Setflip(bool x,bool y,bool h=false);
	float GetWidth() const ;
	float GetHeight() const;
	void Move(float);
	void Speak(eDIALOG_CONTEXT dia, std::vector <InfoDialog> &EnemyDialogsList);
	float GetUpFace()    const  { return vPosition.y;      }
	float GetDownFace()  const  { return vPosition.y+140;  }
	float GetLeftFace()  const  { return vPosition.x;	   }
	float GetRightFace() const  { return vPosition.x+120;  }
	bool IsPlaying()const { return anim->IsPlaying(); }
	void RestoreAiState() {   eAI_STATE = ePREVIOUS_AI_STATE;   }
	hgeAnimation* GetAnim() {  return anim;  }
	eARTIFICIAL_INTELLIGENCE GetAiState() const  { return eAI_STATE; }
	void Enemy::PlayDeathSound(std::vector <InfoDialog> &EnemyDialogsList);
	bool Fire()
	{/*
		if(FireBullet.TimerEnd()) 
		{
			bFireFlag = true;
			return true;
		}*/
		if(bFireFlag) 
		{
			bFireFlag = false;
			FireBullet.setstart();
			return true;
		}

		return false;
	}
	int GetHealth()
	{
		return Player::GetHealth();
	}

	void SetAiState(eARTIFICIAL_INTELLIGENCE A)  
	{ 
		if( A == ADJUSTLEFT || A == ADJUSTRIGHT ) 
		{ 
			SetAnimation(eCURRENTSTANCE);
			anim->Stop();
		}
		
	  ePREVIOUS_AI_STATE = eAI_STATE;   
	  eAI_STATE = A;    
	}

	virtual void LowerHealth(int h) 
	{  
		Player::LowerHealth(h);
		if( GetHealth()<= 0 )
			Die();
	}

	bool CanChangeStance() 
	{
		if( bStanceChangeCapability ) 
		{
			if(StanceTimer.TimerEnd())
			{
				return true;
			}
		}
		return false;
	}	

	bool ThrowGrenade()
	{
		if( UseGrenade.TimerEnd() )
		{
			return true;
		}
	  return false;	
	}
	
	
};

#endif