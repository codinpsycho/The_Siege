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


#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include <hge.h>
HTEXTURE EnemySpeaks(const Enemy*,eDIALOG_CONTEXT);

extern HGE* Engine;

Enemy::Enemy(eENEMY id,ePLAYER_STANCE eface,ePLAYER_STANCE eStance,hgeVector vPos,hgeVector vDir): Player(120.0f)
{
	eID = id;
	eFACING = eface;
	vPosition = vPos;
	vDirection = vDir;
	eCURRENTSTANCE = eStance;
	anim = 0;
	fSpeed = 120.0f;
	FireBullet.setstart();
	fAdjVal = 0.0;

	//////////////////////////////////////////
	switch(rand()%3)
	{
	case 0: eAI_STATE = STRATEGY; break;
	case 1: eAI_STATE = CHASE;    break;
	case 2: eAI_STATE = ATTACK;   break;
	}
	//////////////////////////////////////////
	switch(rand()%4)
	{
	case 0: eENEMY_VOICE = VOICE_TYPE_1; break;
	case 1: eENEMY_VOICE = VOICE_TYPE_2; break;
	case 2: eENEMY_VOICE = VOICE_TYPE_3; break;  
	case 3: eENEMY_VOICE = VOICE_TYPE_4; break;  
	}
	///////////////////////////////////////////

	grenadeFlag = meleeFlag = false;
	bStanceChangeCapability =  true;
    ePREVIOUS_AI_STATE = eAI_STATE; 
				 bSpeakFlag = false;
	StanceTimer.setEndTime(1600);
	      Melee.setEndTime(800 );
	 UseGrenade.setEndTime(3500);
	 SpeakTimer.setEndTime(3500);
	 Speaker = NULL;
	 ShowSpeaker.setEndTime(500 );
	 bShowSpeakerFlag=false;
	 bFireFlag = true;
	 
	 if(eID == HUMAN)
		 UseGrenade.setEndTime(4500);
}

Enemy::~Enemy()
{
  Release();
}

void Enemy::Move(float dt)
{
	if(!Player::IsDead() && eCURRENTSTANCE == RUNNING )
	{
		vPosition.x += (dt*fSpeed)*vDirection.x;
		vPosition.y += (dt*fSpeed)*vDirection.y;
	}
}

float Enemy::GetWidth() const  {  return anim->GetWidth(); }

float Enemy::GetHeight() const {  return anim->GetHeight();	}

ePLAYER_STANCE Enemy::GetFacing() const  { return eFACING;  }

eENEMY Enemy::GetId() const  {	return eID;  }

void Enemy::Release()   
{  	
	delete anim;  
	anim=0; 
		delete Speaker; 
		Speaker=0; 
}

void Enemy::Setflip(bool x,bool y,bool h)  {   anim->SetFlip(x,y,h);  }

void Enemy::Render()    
{  	
	anim->Render(vPosition.x, vPosition.y);  

///////////////////////////////For Health bar of different enemies
	if (this->GetHealth() >0)
	{
		switch (this->GetId())
		{
		case HUMAN: Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 23, GetLeftFace() + 89, this->GetUpFace()+ 23,0xff1f1f1f);
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 23, GetLeftFace() + 39, this->GetUpFace()+ 28,0xff1f1f1f);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 89, this->GetUpFace()+ 28, GetLeftFace() + 89, this->GetUpFace()+ 23,0xff1f1f1f);
		
			for (int i = 0; i < this->GetHealth()*.5; i++)
				Engine->Gfx_RenderLine(this->GetLeftFace() + 40 + i, this->GetUpFace()+ 23, this->GetLeftFace()+ 40 +i, this->GetUpFace() + 28,0xffff0000);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 29, GetLeftFace() + 89, this->GetUpFace()+ 29,0xff1f1f1f);
			break;

		case ALIEN1 :
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 50, GetLeftFace() + 89, this->GetUpFace()+ 50,0xff1f1f1f);
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 50, GetLeftFace() + 39, this->GetUpFace()+ 55,0xff1f1f1f);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 89, this->GetUpFace()+ 55, GetLeftFace() + 89, this->GetUpFace()+ 50,0xff1f1f1f);

			for (int i = 0; i < this->GetHealth()*.4 ;i++)
				Engine->Gfx_RenderLine(this->GetLeftFace() + 40 + i, this->GetUpFace()+ 50, this->GetLeftFace()+ 40 +i, this->GetUpFace() + 55,0xff00c9de);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 56, GetLeftFace() + 89, this->GetUpFace()+ 56,0xff1f1f1f);
			break;

		case ALIEN2 :
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 13, GetLeftFace() + 89, this->GetUpFace()+ 23,0xff1f1f1f);
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 13, GetLeftFace() + 39, this->GetUpFace()+ 18,0xff1f1f1f);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 89, this->GetUpFace()+ 18, GetLeftFace() + 89, this->GetUpFace()+ 13,0xff1f1f1f);

			for (int i = 0; i < this->GetHealth()*.4; i++)
				Engine->Gfx_RenderLine(this->GetLeftFace() + 40 + i, this->GetUpFace()+ 13, this->GetLeftFace()+ 40 +i, this->GetUpFace() + 18,0xff00c9de);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 19, GetLeftFace() + 89, this->GetUpFace()+ 19,0xff1f1f1f);
			break;

		case ALIEN3:
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 50, GetLeftFace() + 89, this->GetUpFace()+ 55, 0xff1f1f1f);
			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 50, GetLeftFace() + 39, this->GetUpFace()+ 55, 0xff1f1f1f);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 89, this->GetUpFace()+ 55, GetLeftFace() + 89, this->GetUpFace()+ 50,0xff1f1f1f);

			for (int i = 0; i < this->GetHealth()*.36; i++)
				Engine->Gfx_RenderLine(this->GetLeftFace() + 40 + i, this->GetUpFace()+ 50, this->GetLeftFace()+ 40 +i, this->GetUpFace() + 55,0xff00c9de);

			Engine->Gfx_RenderLine(this->GetLeftFace() + 39, this->GetUpFace()+ 56, GetLeftFace() + 89, this->GetUpFace()+ 56,0xff1f1f1f);
			break;

		}
		
	}
////////////////////////////////////////////////////////////
	if( eID == HUMAN && bShowSpeakerFlag)
	{
		if(eFACING == FACELEFT) Speaker->SetFlip(true,false);

		Speaker->RenderEx(vPosition.x+55,vPosition.y-30,0.0f,0.4f,0.4f);
		if(ShowSpeaker.TimerEnd()) bShowSpeakerFlag = false; 
	}
}

void Enemy::Die()		{	Player::Die();  ChangeStance(DEAD);  }


void Enemy::Update(float fTime)
{
	anim->Update(fTime);	
	
	if( eCURRENTSTANCE != MELEE )	  meleeFlag = false;
	else if( anim->GetFrame() != 1 )  meleeFlag = true;

	if( eCURRENTSTANCE != THROW_GRENADE )   grenadeFlag = false;
	else if( anim->GetFrame() != 1 )		grenadeFlag = true;	

	if( eCURRENTSTANCE != IDLE && eCURRENTSTANCE != DEAD && !anim->IsPlaying() && !Player::IsDead() )  {  SetAnimation(IDLE);  }
	if( SpeakTimer.TimerEnd() )   bSpeakFlag = true;	
	
	if(FireBullet.TimerEnd())     bFireFlag = true; 

}

void Enemy::SetFacing(ePLAYER_STANCE eface)
{
   if(eface == FACERIGHT)
   {
		 eFACING = FACERIGHT;
		 switch(eID)
		 {
		 case HUMAN:	 anim->SetFlip(false,false); 	break;
		 case ALIEN1:	    
		 case ALIEN2:
		 case ALIEN3:    anim->SetFlip(true,false);    break;
		 }
   }
   else 
   if( eface == FACELEFT ) 
   {
	    eFACING = FACELEFT;
		switch(eID)
		{
			case HUMAN:	 anim->SetFlip(true,false); 	break;
			case ALIEN1:	    
			case ALIEN2:
			case ALIEN3: anim->SetFlip(false,false);    break;
		}	        
   }

}

void Enemy::ChangeStance(ePLAYER_STANCE eSTANCE)
{
	if( eCURRENTSTANCE != eSTANCE )
	{	
		SetAnimation(eSTANCE);
	}
}


bool Enemy::Init(HGE* Engine,HTEXTURE hTex,HTEXTURE hSpeakerTex)
{
	switch(eID)
	{
	case HUMAN:	anim = new hgeAnimation(hTex, 7, 10, 120,   840, 120, 140);   // soldier
		FireRate = 500;  Player::SetSpeed(120.0f); Player::SetMaxHealth(100); Player::ResetHealth();
		break;
	case ALIEN1: 
		anim = new hgeAnimation(hTex, 8, 10, 120,   0, 120, 140);   // yellow
				FireRate = 750;  Player::SetSpeed(90.0f); Player::SetMaxHealth(120);  Player::ResetHealth();
		break; 
	case ALIEN2: 	
		anim = new hgeAnimation(hTex, 8, 10, 120, 140, 120, 140);   // red ones
		FireRate = 850;    Player::SetSpeed(120.0f);  Player::SetMaxHealth(220);   Player::ResetHealth();
		
		break; 
	case ALIEN3:    
		anim = new hgeAnimation(hTex, 6, 10, 120, 280, 120, 140);   // blue big ones
		FireRate = 1000;   Player::SetSpeed(140.0f);  Player::SetMaxHealth(160);   Player::ResetHealth();
		break;
	}
	

	if(eID == HUMAN)
	{	
		Speaker = new hgeSprite(hSpeakerTex,0.0f,0.0f,85.0f,75.0f);
		Speaker->SetColor(0xF0ffffff);
	}

	FireBullet.setEndTime(FireRate);
	SetFacing(eFACING);	
	SetAnimation(eCURRENTSTANCE);
	return true;
}

void Enemy::SetAnimation(ePLAYER_STANCE eSTANCE)
{
	float fSpriteYPos=0.0f, fSpriteXpos=0.0f;
	int   iFrames=0;
	const float colWidth = 120.0f;
	const float colHeight = 140.0f;

	switch (eSTANCE)
	{
	case IDLE:	    
			switch(eID)
			{
			case HUMAN:    fSpriteXpos=0;  fSpriteYPos=980;   iFrames=1;
				break;
			case ALIEN1:   fSpriteXpos=0;  fSpriteYPos=0;     iFrames=1;
				break;
			case ALIEN2:   fSpriteXpos=0;  fSpriteYPos=140;	  iFrames=1;
				break;
			case ALIEN3:   fSpriteXpos=0;  fSpriteYPos=280;   iFrames=1;
				break;
			}
			anim->SetTextureRect(fSpriteXpos,fSpriteYPos,120,140);
			anim->SetFrames(iFrames);
			anim->Play();
			anim->SetMode(HGEANIM_NOLOOP);
			anim->SetMode(HGEANIM_FWD);
			eCURRENTSTANCE = IDLE;
			break;

	case RUNNING:
			switch(eID)
			{
			case HUMAN:    fSpriteXpos=0;  fSpriteYPos=840;     iFrames=6;
				break;
			case ALIEN1:   fSpriteXpos=120;  fSpriteYPos=0;     iFrames=8;
				break;
			case ALIEN2:   fSpriteXpos=120;  fSpriteYPos=140;	iFrames=6;
				break;
			case ALIEN3:   fSpriteXpos=120;  fSpriteYPos=280;   iFrames=8;
				break;
			}
			anim->SetTextureRect(fSpriteXpos,fSpriteYPos,120,140);	
			anim->SetFrames(iFrames);
			anim->SetSpeed(7);
			anim->SetMode(HGEANIM_NOLOOP);
			anim->SetMode(HGEANIM_FWD);
			anim->Play();
			eCURRENTSTANCE = RUNNING;
			break;
		
	case THROW_GRENADE: 
			 if( eID != HUMAN )
			 {
				  switch(eID)
				  {
				  case ALIEN1:   fSpriteXpos=480;  fSpriteYPos=420;
							  break;
				  case ALIEN2:	 fSpriteXpos=480;  fSpriteYPos=560;	
							  break;
				  case ALIEN3:   fSpriteXpos=480;  fSpriteYPos=700;
							  break;
				  }
				  anim->SetTextureRect(fSpriteXpos,fSpriteYPos,120,140);	
				  anim->SetFrames(2);
				  anim->SetSpeed(5);
				  anim->SetMode(HGEANIM_NOLOOP);
				  anim->SetMode(HGEANIM_FWD);	
				  anim->Play();		
				  eCURRENTSTANCE = THROW_GRENADE;	
			}			
			break;

	case MELEE:		
	  if(eID == ALIEN2)
	  {	
		anim->SetTextureRect(720,560,130,140);	
		anim->SetFrames(2);
		anim->SetSpeed(8);
		anim->SetMode(HGEANIM_NOLOOP);
		anim->SetMode(HGEANIM_FWD);
		anim->Play();			
		eCURRENTSTANCE = MELEE;
		break;
	  }

	case DEAD:		
		switch(eID)
		{
		case HUMAN:      fSpriteXpos=240;  fSpriteYPos=980;  iFrames = 3;
			break;
		case ALIEN1:     fSpriteXpos=0;  fSpriteYPos=420;  iFrames = 4;
			break;
		case ALIEN2:	 fSpriteXpos=0;  fSpriteYPos=560;  iFrames = 3;
			break;
		case ALIEN3:     fSpriteXpos=0;  fSpriteYPos=700;  iFrames = 4;
			break;
		}
		anim->SetTextureRect(fSpriteXpos,fSpriteYPos,120,140);	
		anim->SetFrames(iFrames);
		anim->SetSpeed(10);
		anim->SetMode(HGEANIM_NOLOOP);
		anim->SetMode(HGEANIM_FWD);
		anim->Play();			
		eCURRENTSTANCE = DEAD;
		break;
	}	
}


extern std::vector< Enemy*  > pGameEnemyList;    
void Enemy::Speak(eDIALOG_CONTEXT context, std::vector <InfoDialog> &EnemyDialogsList)
{
	if( bSpeakFlag || context == DEATH )
	{ 
		bSpeakFlag = false;
		SpeakTimer.setstart();

		if( context != DEATH )
		for(unsigned int i=0; i<EnemyDialogsList.size(); i++ )
		{
			InfoDialog Ob = EnemyDialogsList[i];
			if( Ob.eContext == context ) return;
		}
					   
		  EnemyDialogsList.push_back( InfoDialog ( EnemySpeaks (this,context), context ) );

		  if( context != DEATH )
		  {			 
		     bShowSpeakerFlag = true;
		     ShowSpeaker.setstart();
		  }
   }
 
}

void Enemy::PlayDeathSound(std::vector <InfoDialog> &EnemyDialogsList)
{
	EnemyDialogsList.push_back( InfoDialog ( EnemySpeaks(this,DEATH), DEATH ) );
}