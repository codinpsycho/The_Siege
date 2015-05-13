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



#include "Protagonist.h"
#include "hgeanim.h"
#include "hge.h"

// Constructor
Protagonist::Protagonist(void): Player(230.0f),AssaultRifle(ASSAULTRIFLE,PRIMARY),SideArm(SEMIAUTO,SECONDARY),ShotGun(SHOTGUN,PRIMARY),RocketLauncher(ROCKETLAUNCHER,PRIMARY)
{
	eCURRENTSTANCE = IDLE;
	eCURRENTWEAPON = AssaultRifle.GetWeaponID();
	pCurrentWeapon = &AssaultRifle;
	       eFACING = FACERIGHT;
	     iGrenades = 6; 
	SpriteSheet[0] = SpriteSheet[1] = MainAnimation = 0;
	vDirection = hgeVector(1,0);
}

//Destructor
Protagonist::~ Protagonist()
{
	
}

ePLAYER_STANCE Protagonist::GetStance() const	  {  return eCURRENTSTANCE;			    }
float Protagonist::GetHeight() const    		  {  return MainAnimation->GetHeight(); }
void Protagonist::Render() const				  {  MainAnimation->Render( vPosition.x, vPosition.y );  }
void Protagonist::Play()						  {  MainAnimation->Play();								 }	

void Protagonist::Release(HGE* engine)                
{  
	delete SpriteSheet[0]; 
	delete SpriteSheet[1];   
	engine->Texture_Free(Texture[0]);	
	engine->Texture_Free(Texture[1]);    
	SpriteSheet[0] = SpriteSheet[1] = MainAnimation = NULL;
}

void Protagonist::SetZdepth(float z,int i)
{
	SpriteSheet[0]->SetZ(z,i);
	SpriteSheet[1]->SetZ(z,i);
}

void Protagonist::Die()				
{  
	ChangeStance(DEAD);
	Player::Die();	
} 	   


void Protagonist::ChangeStance(ePLAYER_STANCE eSTANCE)
{
	if( !Player::IsDead() && eCURRENTSTANCE != eSTANCE )
	{
		SetAnimation(eSTANCE);
	}
	else if( Player::IsDead() )
	{
		SetAnimation(DEAD);
	}
}

ePLAYER_STANCE Protagonist::GetFacing() const 
{
	return eFACING;
}

void Protagonist::SetFacing( ePLAYER_STANCE eFACE, bool flip)
{
	if ( eFACING != eFACE )
   {
		eFACING = eFACE;
		SpriteSheet[0]->SetFlip(flip,false); // flip both the sprite sheet objects to continue with flipped Player
		SpriteSheet[1]->SetFlip(flip,false);

		(eFACING == FACERIGHT) ? vDirection.x = 1 : vDirection.x = -1;
   }
}

//////////////////////////////////////////  INITIALIZATION  /////////////////////////////////////////////////

///////////////////////////////////////////////////////////
bool Protagonist::Init(HGE *hge)
{ 
	const int NUM = 2;
	char *str[NUM];	     
	str[0] = "Sprites\\MasterChiefStyle1.png";
 	str[1] = "Sprites\\MasterChiefStyle2.png";

	// DIFFERENT SPRITE SHEETS TO LOAD TEXTURE FROM

	for ( int i = 0; i<NUM; i++ )
	{
		Texture[i] = hge->Texture_Load( str[i] );	
		if( !Texture[i] )   
		{  
			MessageBox(0,*str,"Can't Load Texture",MB_OK | MB_ICONERROR | MB_APPLMODAL);  
			return false;
		}         
	}																					 // note dimensions		

	SpriteSheet[0] = new hgeAnimation(Texture[0], 10, 10, 0, 0, 120, 140);
	SpriteSheet[1] = new hgeAnimation(Texture[1],  6, 10, 0, 0, 120, 140);
	MainAnimation = SpriteSheet[0];
	MainAnimation->SetTextureRect(0,560,120,140);
	MainAnimation->SetFrames(1);
    MainAnimation->SetMode(HGEANIM_NOLOOP);
	Play();
	return true;		
}

///////////////////////////////   SET ANIMATION   //////////////////////////////////////////////////////
////// sets the sprite animation for the player with the current weapon   // valid for range 1 to 8


void Protagonist::SetAnimation(ePLAYER_STANCE eSTANCE)
{
		float fSpritePos=0.0f, fSpriteXpos=0.0f;
		int   iFrames=0;
		const float colWidth = 120.0f;
		const float colHeight = 140.0f;

		switch (eSTANCE)
		{
			case IDLE:	    
							switch ( eCURRENTWEAPON )                              // the animation will be selected from the sprite sheet on the 
							{													   // basis of current weapon 				
							case ASSAULTRIFLE:	    fSpritePos = 560;   break;
							case SEMIAUTO:		    fSpritePos = 700;   break;
							case SHOTGUN:           fSpritePos = 840;   break;
							case ROCKETLAUNCHER:    fSpritePos = 980;   break;
							case SNIPER:			break;
							}
							SpriteSheet[0]->SetTextureRect(0,fSpritePos,120,140);

							MainAnimation = SpriteSheet[0];
							MainAnimation->SetFrames(1);
							MainAnimation->SetMode(HGEANIM_NOLOOP);
							Play();	
							eCURRENTSTANCE = IDLE;		
							break;
			case RUNNING:   

							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos =   0;  iFrames =  9; break;
							case SEMIAUTO:		    fSpritePos = 140;  iFrames = 10; break;
							case SHOTGUN:           fSpritePos = 280;  iFrames = 10; break;
							case ROCKETLAUNCHER:    fSpritePos = 420;  iFrames = 10; break;
							case SNIPER:			break;
							}	
							SpriteSheet[0]->SetTextureRect(0,fSpritePos,120,140);
							SpriteSheet[0]->SetFrames(iFrames);
							SpriteSheet[0]->SetSpeed(12);
							SpriteSheet[0]->SetMode(HGEANIM_FWD|HGEANIM_NOLOOP);				
							MainAnimation = SpriteSheet[0]; 
							Play();
							eCURRENTSTANCE = RUNNING;
							break;

			case LOOKUP:    
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos = 560;   break;
							case SEMIAUTO:		    fSpritePos = 700;   break;
							case SHOTGUN:           fSpritePos = 840;   break;
							case ROCKETLAUNCHER:    fSpritePos = 980;   break;
							case SNIPER:			break;
							}
							SpriteSheet[0]->SetTextureRect(0,fSpritePos,colWidth,colHeight);
							SpriteSheet[0]->SetFrames(4);  
							SpriteSheet[0]->SetSpeed(25);
							SpriteSheet[0]->SetMode(HGEANIM_NOLOOP);				
							MainAnimation = SpriteSheet[0];	
							Play();
							eCURRENTSTANCE = LOOKUP;
							break;

			case THROW_GRENADE: 
							SpriteSheet[0]->SetTextureRect(0,1120,colWidth,colHeight);
							SpriteSheet[0]->SetFrames(5);
							SpriteSheet[0]->SetSpeed(10);
							SpriteSheet[0]->SetMode(HGEANIM_NOLOOP);
							MainAnimation = SpriteSheet[0]; 
							Play();
							eCURRENTSTANCE = THROW_GRENADE;
							break;
			case DUCK:		
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos =   0;   break;
							case SEMIAUTO:		    fSpritePos = 140;   break;
							case SHOTGUN:           fSpritePos = 280;   break;
							case ROCKETLAUNCHER:    fSpritePos = 420;   break;
							case SNIPER:			break;
							}
							
							SpriteSheet[1]->SetTextureRect(0,fSpritePos,colWidth,colHeight);
							SpriteSheet[1]->SetFrames(2);
							SpriteSheet[1]->SetMode(HGEANIM_NOLOOP);				
							SpriteSheet[1]->SetSpeed(15);
							MainAnimation = SpriteSheet[1]; 
							MainAnimation->SetFrame(0); 
							Play();
							eCURRENTSTANCE = DUCK;
							break;
			case MELEE:		
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos =   0; iFrames=2;  break;
							case SEMIAUTO:		    fSpritePos = 140; iFrames=2;  break;
							case SHOTGUN:           fSpritePos = 280; iFrames=2;  break;
							case ROCKETLAUNCHER:    fSpritePos = 420; iFrames=1;  break;
							case SNIPER:			break;
							}
							SpriteSheet[1]->SetTextureRect(480,fSpritePos,colWidth,colHeight);
							SpriteSheet[1]->SetFrames(iFrames);
							SpriteSheet[1]->SetMode(HGEANIM_NOLOOP);
							SpriteSheet[1]->SetSpeed(5);
							MainAnimation = SpriteSheet[1]; 
							Play();
							eCURRENTSTANCE = MELEE;
							break;
			case LOWMOVE:	
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos =   0;   break;
							case SEMIAUTO:		    fSpritePos = 140;   break;
							case SHOTGUN:           fSpritePos = 280;   break;
							case ROCKETLAUNCHER:    fSpritePos = 420;   break;
							case SNIPER:			break;
							}

							SpriteSheet[1]->SetTextureRect(120,fSpritePos,colWidth,colHeight);
							SpriteSheet[1]->SetFrames(3); SpriteSheet[1]->SetSpeed(2.8);
							SpriteSheet[1]->SetMode(HGEANIM_NOLOOP);				
							MainAnimation = SpriteSheet[1]; Play();
							eCURRENTSTANCE = LOWMOVE;	
							break;	
			case JUMPING:   
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos = 560; fSpriteXpos =   0; iFrames=2;  break;
							case SEMIAUTO:		    fSpritePos = 700; fSpriteXpos =   0; iFrames=2;  break;
							case SHOTGUN:           fSpritePos = 560; fSpriteXpos = 240; iFrames=2;  break;
							case ROCKETLAUNCHER:    fSpritePos = 700; fSpriteXpos = 240; iFrames=2;  break;
							case SNIPER:			break;
							}
							SpriteSheet[1]->SetTextureRect( fSpriteXpos,fSpritePos,colWidth,colHeight);
							SpriteSheet[1]->SetFrames(iFrames);
							SpriteSheet[1]->SetMode(HGEANIM_NOLOOP);
							SpriteSheet[1]->SetSpeed(1.5f);
							MainAnimation = SpriteSheet[1]; 
							Play();
							eCURRENTSTANCE = JUMPING;
							break;	
			
			case DEAD:		
							SpriteSheet[1]->SetTextureRect( 0,840,colWidth,colHeight);
							SpriteSheet[1]->SetFrames(3);
							SpriteSheet[1]->SetMode(HGEANIM_NOLOOP);
							SpriteSheet[1]->SetSpeed(8);
							MainAnimation = SpriteSheet[1]; 
							Play();
							eCURRENTSTANCE = DEAD;
							break;

			case MOVE_BACK:
							switch ( eCURRENTWEAPON )
							{
							case ASSAULTRIFLE:	    fSpritePos =   0;  iFrames =  9; break;
							case SEMIAUTO:		    fSpritePos = 140;  iFrames = 10; break;
							case SHOTGUN:           fSpritePos = 280;  iFrames = 10; break;
							case ROCKETLAUNCHER:    fSpritePos = 420;  iFrames = 10; break;
							case SNIPER:			break;
							}	
							SpriteSheet[0]->SetTextureRect(0,fSpritePos,120,140);
							SpriteSheet[0]->SetFrames(iFrames);
							SpriteSheet[0]->SetSpeed(12);
							SpriteSheet[0]->SetMode(HGEANIM_REV|HGEANIM_NOLOOP);				
							MainAnimation = SpriteSheet[0]; 
							Play();
							eCURRENTSTANCE = MOVE_BACK;	
								break;
		}	
}


///////////////////////////   UPDATE   /////////////////////////////////////////////////
void Protagonist::Move(float dt)
{  
	float MovingSpeed = 0.0f;
	//vDirection.x = ( eFACING == FACERIGHT ) ? 1 : -1;
	MovingSpeed  = ( eCURRENTSTANCE == LOWMOVE ) ? fSpeed / 3 : fSpeed;

	vPosition.x += (dt*MovingSpeed) *vDirection.x;
	vPosition.y += (dt*MovingSpeed) *vDirection.y;
}

void Protagonist::Update( HGE*engine, float ftime )    
{ 
	MainAnimation->Update( ftime );

	if( Player::IsDead() ) return;
	
	if( eCURRENTSTANCE != JUMPING  && eCURRENTSTANCE != DEAD )
	if(engine->Input_GetKeyState(HGEK_ALT) )
	{
		if( ThrowGrenade() )
		{ 
			ChangeStance( THROW_GRENADE);	
		}
	}
	else
	if (engine->Input_GetKeyState(HGEK_SHIFT) )
	{
		ChangeStance( MELEE );
	}
 	else
	if( ( engine->Input_KeyUp(HGEK_DOWN) ) && eCURRENTSTANCE == DUCK /* && eCURRENTSTANCE != THROW_GRENADE */)
	{
			ChangeStance( DUCK );
			MainAnimation->SetMode(HGEANIM_REV);
			Play(); 
	
	}
	else
	if( ( engine->Input_KeyUp(HGEK_UP) )  && eCURRENTSTANCE == LOOKUP && eCURRENTSTANCE != THROW_GRENADE )
	{
		ChangeStance( LOOKUP );
		MainAnimation->SetMode(HGEANIM_REV);
		Play();
	}
	else     ///////////////////////
		if ( !MainAnimation->IsPlaying()  || eCURRENTSTANCE == RUNNING || eCURRENTSTANCE == LOWMOVE || eCURRENTSTANCE == MOVE_BACK )
	    {	
		if ( engine->Input_KeyUp(HGEK_DOWN) /*&& eCURRENTSTANCE != LOOKUP*/ )
		{
			ChangeStance( DUCK );
			MainAnimation->SetMode(HGEANIM_REV);
			Play();
		}
		else
		if (engine->Input_GetKeyState(HGEK_UP) )
		{
			ChangeStance( LOOKUP );	
		}
		else
		if (engine->Input_GetKeyState(HGEK_DOWN) )
		{
				if( engine->Input_GetKeyState(HGEK_RIGHT)  ) // Stealth Move Right
				{
					if( eCURRENTSTANCE == LOWMOVE && !MainAnimation->IsPlaying() ) eCURRENTSTANCE = IDLE;
					ChangeStance( LOWMOVE ); 
					SetFacing( FACERIGHT,false );
					vDirection.x = +1;
				}
				else 
				if( engine->Input_GetKeyState(HGEK_LEFT)  )  // Stealth Move Left
				{
					if( eCURRENTSTANCE == LOWMOVE && !MainAnimation->IsPlaying() ) eCURRENTSTANCE = IDLE;
					ChangeStance( LOWMOVE );
					SetFacing( FACELEFT,true );
					vDirection.x = -1;
				}
				else if(eCURRENTSTANCE == LOWMOVE)   // Stealth Move
				{ 
					ChangeStance( DUCK );  MainAnimation->SetFrame(1);  
				}
 				else
				{ 
					ChangeStance( DUCK ); 
					vDirection.x = ( eFACING == FACERIGHT ) ? 1 : -1;
				}
		}
		else
		if (engine->Input_GetKeyState(HGEK_LEFT) )     // move left
		{
			if ( engine->Input_GetKeyState( HGEK_CTRL ) && eFACING == FACERIGHT )
			{
				if(eCURRENTSTANCE == MOVE_BACK && !MainAnimation->IsPlaying() ) ChangeStance(IDLE);
				ChangeStance(MOVE_BACK);		
				vDirection.x = -1;
			}
			else
			{
				if(eCURRENTSTANCE==RUNNING && !MainAnimation->IsPlaying()) eCURRENTSTANCE = IDLE;
				SetFacing( FACELEFT,true );
				ChangeStance( RUNNING ); 
				vDirection.x = -1;
			}
		}
		else
		if (engine->Input_GetKeyState(HGEK_RIGHT) )  // move right
		{
			if ( engine->Input_GetKeyState( HGEK_CTRL ) && eFACING == FACELEFT )
			{
				if(eCURRENTSTANCE == MOVE_BACK && !MainAnimation->IsPlaying() ) ChangeStance(IDLE);
				ChangeStance(MOVE_BACK);		vDirection.x = 1;
			}
			else
			{
				if(eCURRENTSTANCE==RUNNING && !MainAnimation->IsPlaying()) eCURRENTSTANCE = IDLE;
				SetFacing( FACERIGHT,false );
				ChangeStance( RUNNING );	
				vDirection.x = +1;
			}
		}
		else
		{
			ChangeStance( IDLE );
		}

	}
		/*
		if( eCURRENTSTANCE == MOVE_BACK )
		vDirection.x = ( eFACING == FACERIGHT ) ? -1 :  1;
		else
		vDirection.x = ( eFACING == FACERIGHT ) ?  1 : -1;
		*/
}	

/////////////////////////////////  

/////////////////////////////////  

void Protagonist::SelectAssaultRifle()    
{  
	eCURRENTWEAPON = AssaultRifle.GetWeaponID();    
	pCurrentWeapon = &AssaultRifle;
	SetAnimation(eCURRENTSTANCE);
	if( eCURRENTSTANCE==DUCK ) 	MainAnimation->SetFrame(1);
}
void Protagonist::SelectSideArm()  
{  
	eCURRENTWEAPON = SideArm.GetWeaponID();  
	pCurrentWeapon = &SideArm;
	SetAnimation(eCURRENTSTANCE);
	if( eCURRENTSTANCE==DUCK ) 	MainAnimation->SetFrame(1);
}
void Protagonist::SelectShotGun()  
{  
	eCURRENTWEAPON = ShotGun.GetWeaponID();  
	pCurrentWeapon = &ShotGun;
	SetAnimation(eCURRENTSTANCE);
	if( eCURRENTSTANCE==DUCK ) 	MainAnimation->SetFrame(1);
}
void Protagonist::SelectRocketLauncher()  
{  
	eCURRENTWEAPON = RocketLauncher.GetWeaponID();  
	pCurrentWeapon = &RocketLauncher;
	SetAnimation(eCURRENTSTANCE);
	if( eCURRENTSTANCE==DUCK ) 	MainAnimation->SetFrame(1);
}



bool Protagonist::SwapWeapon(WeaponObject* wep,HGE* Engine) // argument is the weapon intend to be picked
{
	Weapon obj = *wep; 

	if( obj.GetWeaponID() == AssaultRifle.GetWeaponID() )// check if the weapon is present as primary weapon	
	{
		if(!AssaultRifle.IsFull()){
			AssaultRifle.RaiseAmmo( wep->GetAmmo() );
			return false;
		}
	}
	else if( obj.GetWeaponID() == SideArm.GetWeaponID() ) 
	{
		if(!SideArm.IsFull()){
			SideArm.RaiseAmmo( wep->GetAmmo() );	
			return false;
		}
	}
	else if( obj.GetWeaponID() == ShotGun.GetWeaponID() ) 
	{
		if(!ShotGun.IsFull()){
			ShotGun.RaiseAmmo( wep->GetAmmo() );	
			return false;
		}
	}
	else if( obj.GetWeaponID() == RocketLauncher.GetWeaponID() ) 
	{
		if(!RocketLauncher.IsFull()){
			RocketLauncher.RaiseAmmo( wep->GetAmmo() );	
			return false;
		}
	}
	else // swap with current weapon
	{
		wep->SwapWeapon(*this->pCurrentWeapon);
		wep->ReInit( Engine );
		eCURRENTWEAPON = pCurrentWeapon->GetWeaponID();
		SetAnimation(eCURRENTSTANCE);
		if(eFACING == FACELEFT) wep->sprite->SetFlip(true,false);	
	}

	return true;
}


void Protagonist::ChangeWeapon(eWEAPONS eWEAPON)
{
	if( eCURRENTWEAPON != eWEAPON )
	{
		eCURRENTWEAPON = eWEAPON;
		SetAnimation(eCURRENTSTANCE);
	}

}

bool Protagonist::FireWeapon()
{
	return pCurrentWeapon->Fire();
}

eWEAPONS Protagonist::GetWeaponId()
{
	return pCurrentWeapon->GetWeaponID();
}


int Protagonist::GetWeaponAmmo()
{
	return pCurrentWeapon->GetAmmo();
}

void Protagonist::LowerHealth(int h) 
{ 
	Player::LowerHealth(h);
	if( Player::IsDead() )ChangeStance(DEAD); 
}