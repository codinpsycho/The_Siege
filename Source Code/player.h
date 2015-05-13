#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

enum ePLAYER_STANCE {
						IDLE,	
						LOOKUP,	
						RUNNING,
						JUMPING,	
						THROW_GRENADE,
						MELEE,
						DUCK,
						FACERIGHT,
						FACELEFT,
						LOWMOVE,
						DEAD,
						MOVE_BACK,
					};


// Abstract Base Class ---- Player 
#include <hgeVector.h>

class Player
{
  private:
	      int iHealth;
		  int MAX;
	      bool bDead;
  protected:
		 float fSpeed;
  public:
	      enum { MIN=0 };	
	  hgeVector vPosition;
	  hgeVector vDirection;

	  Player(float s = 0.6f, const int i=100 ):MAX(i)
	  {
		   iHealth = 100;
			fSpeed = s;
			 bDead = false;
	     vPosition.x = vPosition.y = 200.0f;
		vDirection.x = vDirection.y = 0.0f;
	  }

		virtual ~Player() = 0 {}
		virtual void SetMaxHealth(int i){  MAX = i;											   } 
		virtual void RaiseHealth(int h) {  iHealth += h; if( iHealth > MAX )  iHealth = MAX;   }
		virtual void LowerHealth(int h) {  iHealth -= h; if( iHealth <= MIN ) {iHealth = MIN; bDead = true; } }
		virtual void SetHealth(int h)   {  iHealth = h;										   }
		virtual  int GetHealth() const	{  return iHealth;									   }	
		virtual bool IsDead() const		{  return bDead;									   }
		virtual void Die()				{  bDead = true; iHealth = 0;						   } 	   
		virtual void SetSpeed(float s)  {  fSpeed = s;										   }
		virtual float GetSpeed() const  {  return fSpeed;									   }
		virtual void ResetHealth()		{  iHealth = MAX;									   }	
		virtual void SetDead(bool dd)	{  bDead = dd;										   }
};


#endif