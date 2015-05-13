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




#include <vector>
#include <hge.h>
#include "Protagonist.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include "sounds.h"
#include "LevelObjects.h"
using std::vector;


extern int Total_Score;
void AddScore(hgeVector, char*,enum eScores);
extern HGE *Engine;
extern HTEXTURE ParTex;
extern HTEXTURE hTexBullets;
extern std::vector<Bonus*> vBonus;
extern std::vector< Bullet* > vInGameBullets;
extern std::vector< Enemy*  > pGameEnemyList;
extern std::vector< hgeParticleSystem* > ParticleList;
extern std::vector< hgeParticleSystem* > LauncherEffectParticleList; 
//enum eParticles { BLACK_SMOKE, BROWN_SMOKE, GREY_SMOKE, HIT_EFFECT, HIT_BLOOD, HIT_FIRE, JUMP_DUST, LAUNCHER_TRAIL, GUN_SPARK, BLAST,GRENADE_BLAST};
hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int direction);
extern vector <SoundInfo> SoundEffectsList;
extern Protagonist *Aztec;
extern bool bDisplayBonusMessage;
bool CheckBound(Bullet* B);
																		  // it takes a list of bullets as a reference							
Bullet* createBullet(Protagonist* masterChief, HTEXTURE hTex, HGE* Engine,std::vector< Bullet* > &vInGameBullets)
{
	float fHeight = 50.0f;
	float fWidth = 100.0f;
	float dirY = 0.0f;
	float dirX = 0.65f;
							
	switch( masterChief->GetStance() )  // get current stance of the player
 	{
	
	case IDLE:
	case RUNNING:	
					switch(masterChief->GetWeapon())  // get current weapon selected			
					{
					case ASSAULTRIFLE:			 fHeight = 49.0f;  fWidth = 103.0f;
												 break;	
					case SEMIAUTO:				 fHeight = 47.0f;  fWidth = 101.0f;
												 break;	
					case SHOTGUN:                fHeight = 48.0f;  fWidth = 115.0f;
												 break; 
					case ROCKETLAUNCHER:		 fHeight = 41.0f;  fWidth = 96.0f;
												 break;
					}				
					break; // break case 1 of outer switch
	
	case LOOKUP:	
					switch(masterChief->GetWeapon())  // get current weapon selected			
					{
					case ASSAULTRIFLE:			 fHeight = 25.0f-3;  fWidth = 84.0f; 
						break;	
					case SEMIAUTO:				 fHeight = 23.0f-3;  fWidth = 76.0f; 
						break;	
					case SHOTGUN:                fHeight = 18.0f-4;  fWidth = 94.0f; 
						break; 
					case ROCKETLAUNCHER:		 fHeight = 22.0f-3;  fWidth = 70.0f; 
						break;
					}
					dirY=-1.0f;
					break;
	case LOWMOVE:
	case DUCK:		
					switch(masterChief->GetWeapon())  // get current weapon selected			
					{
					case ASSAULTRIFLE:			 fHeight = 78.0f;  fWidth = 103.0f;
						break;	
					case SEMIAUTO:				 fHeight = 76.0f;  fWidth = 101.0f;
						break;	
					case SHOTGUN:                fHeight = 77.0f;  fWidth = 115.0f;
						break; 
					case ROCKETLAUNCHER:		 fHeight = 70.0f;  fWidth =  96.0f;
						break;
					}
					break;
	
	
	case JUMPING:  
					switch(masterChief->GetWeapon())  // get current weapon selected			
					{
					case ASSAULTRIFLE:			 fHeight = 42.0f;  fWidth = 101.0f;
						break;	
					case SEMIAUTO:				 fHeight = 39.0f;  fWidth =  99.0f;
						break;	
					case SHOTGUN:                fHeight = 39.0f;  fWidth = 113.0f;
						break; 
					case ROCKETLAUNCHER:		 fHeight = 34.0f;  fWidth =  94.0f;
						break;
					}
					break;
	
	}

	eBULLETID id;  
		
	switch(masterChief->GetWeapon())  // get current weapon selected			
	{
	case ASSAULTRIFLE:		id =  ASSAULTRIFLE_BULLET;		  
		break;	
	case SEMIAUTO:			id = SEMIAUTO_BULLET;	
		break;	
	case SHOTGUN:           id = SHOTGUN_BULLET;    fHeight += 6.0f;
		break; 
	case ROCKETLAUNCHER:	id = ROCKETLAUNCHER_BULLET;	  
		break;
	}
	
	Bullet* bul=0;	

	if( masterChief->GetFacing() == FACELEFT ) { dirX *= -1.0f;  fWidth -= fWidth-5; } 
	if( masterChief->GetFacing() == FACELEFT && masterChief->GetStance() == LOOKUP ) { fWidth+=20; fHeight-=5; }
	bul = new Bullet( id, hgeVector(masterChief->vPosition.x+fWidth, masterChief->vPosition.y+fHeight), hgeVector(dirX,dirY) );

	if(bul)
	{
	    bul->Init(Engine,hTex);  // allocates resources     

		if(bul->GetId()==ROCKETLAUNCHER_BULLET)  // if new bullet is rocket launcher
		{
		  hgeParticleSystem *par = ParticleFactory( 
													LAUNCHER_TRAIL, 
													( bul->vDirection.x < 0 )? ( bul->GetRightFace() ):( bul->GetLeftFace() ), 
													  bul->vPosition.y + (bul->GetHeight()/2),	
													  0.8f  
												   );

		   bul->part = par; // bullet keeps track of the trail in part 
		   LauncherEffectParticleList.push_back(par); // push it in the list
		}

		vInGameBullets.push_back( bul);
	}
	
	return bul;
}

void Move(std::vector< Bullet* > &Bul, float dt, HGE* Engine)
{
	for(unsigned int i=0 ; i<Bul.size(); i++)
	{
		if( !Bul[i]->IsDead() && CheckBound(Bul[i])  )  // if dead is false and CheckBound returns true
		{
			Bul[i]->Move(dt);
		}
		else
		{
			if( Bul[i]->GetId() == ROCKETLAUNCHER_BULLET )  // bullet dies any ways
			{
				for(int pin=0; pin<LauncherEffectParticleList.size(); pin++)		
				{
					if( Bul[i]->part == LauncherEffectParticleList[pin] )
					{
						Bul[i]->part = 0;
						LauncherEffectParticleList[pin]->Stop();
					}
				}
			}
			
			Bullet * ptr = Bul[i];  // get the pointer to the bullet obj in memory
			ptr->Release();			// release memory of the members of object
			delete ptr;				// delete the pointer created with new in the CreateBullet() function
 			Bul.erase(Bul.begin() + i);
			if( i != 0  && i != Bul.size() )  i--;
			continue;
		}
	}
}



Bullet* createEnemyBullet(Enemy* enemy, HTEXTURE hTex, HGE* Engine,std::vector< Bullet* > &vInGameBullets)
{
	float fHeight = 50.0f;
	float x=0;
	float dirX = -1.0f;
	eBULLETID id;  

	switch(enemy->GetId())
	{
	case HUMAN:  x  = ( enemy->GetFacing() == FACERIGHT ) ? (enemy->GetRightFace()-27):(enemy->GetLeftFace()+27);
		fHeight = 47.0f;
		id = ENEMYBULLET_TYPE1;
		break;	
	case ALIEN1: x  = ( enemy->GetFacing() == FACERIGHT ) ? (enemy->GetRightFace()-20):(enemy->GetLeftFace()+20);
		fHeight = 95.0f;
		id = ENEMYBULLET_TYPE2;
		break;
	case ALIEN2: x  = ( enemy->GetFacing() == FACERIGHT ) ? (enemy->GetRightFace()-10):(enemy->GetLeftFace()+10);
		fHeight = 65.0f;
		id = ENEMYBULLET_TYPE3;
		break;
	case ALIEN3: x  = ( enemy->GetFacing() == FACERIGHT ) ? (enemy->GetRightFace()-20):(enemy->GetLeftFace()+20);
		fHeight = 95.0f;
		id = ENEMYBULLET_TYPE4;
		break;
	}

	if( enemy->GetFacing() == FACELEFT )	
	{ dirX = -1.0f;  }
	else 
	{	dirX = 1.0f; }


	Bullet* bul = new Bullet( id, hgeVector( x, enemy->vPosition.y+fHeight ), hgeVector(dirX,0.0f) );
	bul->Init(Engine,hTex);
	vInGameBullets.push_back(bul);

	return bul;
}




// this function returns true if the bullet is within screen and returns false when not
bool CheckBound(Bullet* B)
{
	if( B->vPosition.x < -100 || B->vPosition.x > 1400 || B->vPosition.y < 0 )    
	{	
		return false; 	
	}
  return true;
}



void CreateEffect( Bullet* bul, std::vector< hgeParticleSystem* > &ParticleList );
void BulletCollisionPro(  )
{
	if (Aztec->IsDead()) return; 
	float left ;
	float right ;
	float head = Aztec->GetUpFace();
	

	if( Aztec->GetStance() == DUCK || Aztec->GetStance() == LOWMOVE) 
	{
		head+=66.0f;
	}
	else 
		head+=36.0f;

	if(Aztec->GetFacing() == FACERIGHT)
	{
		right = Aztec->GetRightFace() - 43.0f;
		left = Aztec->GetLeftFace() + 34.0f;
	}
	else 
	{
		left = Aztec->GetLeftFace() + 43.0f;
		right = Aztec->GetRightFace() - 34.0f;
	}	

	for ( int i=0; i<vInGameBullets.size(); i++ )
	{
		eBULLETID id = vInGameBullets[i]->GetId();
		if( !vInGameBullets[i]->IsDead() && ( id == ENEMYBULLET_TYPE1 || id == ENEMYBULLET_TYPE2 || id == ENEMYBULLET_TYPE3 || id == ENEMYBULLET_TYPE4 ) )
		{	
			Bullet* bul = vInGameBullets[i];
				if( bul->GetDownFace() > head && bul->GetUpFace() < Aztec->GetDownFace() )
					if( right > bul->GetLeftFace() && bul->GetRightFace() > left )
					{
						bul->Die();
			
						switch(bul->GetId())	
						{
						case ENEMYBULLET_TYPE1:	Aztec->LowerHealth(5); AddScore(hgeVector(Aztec->GetLeftFace() + 35, Aztec->GetUpFace()), "-5",BULLET1_SUSTAINED);	 break;
						case ENEMYBULLET_TYPE2:	Aztec->LowerHealth(7); AddScore(hgeVector(Aztec->GetLeftFace() + 35, Aztec->GetUpFace()), "-5",BULLET2_SUSTAINED); 	 break;
						case ENEMYBULLET_TYPE3:	Aztec->LowerHealth(15); AddScore(hgeVector(Aztec->GetLeftFace() + 35, Aztec->GetUpFace()), "-15",BULLET3_SUSTAINED); break;
						case ENEMYBULLET_TYPE4:	Aztec->LowerHealth(12); AddScore(hgeVector(Aztec->GetLeftFace() + 35, Aztec->GetUpFace()), "-10",BULLET4_SUSTAINED);
						}

						int dir = ( bul->vDirection.x == -1 ) ? -1:1 ;
						CreateEffect( bul, ParticleList );
						SoundEffectsList.push_back(PlaySoundEffect(HIT_FLESH_ALIEN));
					}
		}
	}

}


void ManageEnemyParticleEffect(Enemy *En)
{
	ePLAYER_STANCE tempStance = En->GetStance();
	ePLAYER_STANCE tempFace = En->GetFacing();

	if( En->GetId() != HUMAN ) return; 

	if ( tempFace == FACERIGHT )
	{
		if (tempStance == RUNNING)
		{
			ParticleList.push_back(ParticleFactory(GUN_SPARK, En->vPosition.x + 85, En->vPosition.y + 48, 1));
		}
		else if ( tempStance == IDLE )
		{
			ParticleList.push_back(ParticleFactory(GUN_SPARK, En->vPosition.x + 85, En->vPosition.y + 48, -1));
		}
	}
	else if ( tempFace == FACELEFT )
	{
		if (tempStance == RUNNING)
		{
			ParticleList.push_back(ParticleFactory(GUN_SPARK, En->vPosition.x + 22, En->vPosition.y + 48, -1));
		}
		else if ( tempStance == IDLE )
		{
			ParticleList.push_back(ParticleFactory(GUN_SPARK, En->vPosition.x + 22, En->vPosition.y + 48, 1));
		}
	}

}


void GenerateBonus(LevelObjects&Lov, const int i)
{
	const int x = ( i == 1 )? 4 : 6;
	Bonus *B = 0;
	eBONUS_ID id = MEDIKIT;
	float y=0.0f;
	switch( rand()%x )
	{
	case 0: id = MEDIKIT; break; 
	case 1: id = AMMO_ASSAULTRIFLE; break; 
	case 2: id = AMMO_SIDEARM; y+= 4.0f; break; 
	case 3: id = AMMO_GRENADE; y+=5.0f;  break; 
	case 4: id = AMMO_SHOTGUN;  break; 
	case 5: id = AMMO_LAUNCHER; break; 
	}	

	B = new Bonus(id, hgeVector( Lov.GetLeftFace()+20.0f, Lov.GetDownFace()-15.0f+y ) );
	if(B)
	{   
		B->Init(hTexBullets);
		vBonus.push_back(B);
	}
}


extern CONDITION PLAYERSTATUS;
void ProcessBonus()
{
	bDisplayBonusMessage = false;
	if (Aztec->IsDead()) return; 

	float left ;
	float right ;

	if(Aztec->GetFacing() == FACERIGHT)
	{
		right = Aztec->GetRightFace() - 43.0f;
		left = Aztec->GetLeftFace() + 34.0f;
	}
	else 
	{
		left = Aztec->GetLeftFace() + 43.0f;
		right = Aztec->GetRightFace() - 34.0f;
	}
		
	for(int i=0; i<vBonus.size(); ++i)
	{
		if( vBonus[i]->IsDead() || vBonus[i]->GetRightFace() < -1.0f )
		{
			vBonus.erase( vBonus.begin() + i );
			if(i!=0 && i!= (vBonus.size()-1) ) --i;
		}
	}
	
	if( PLAYERSTATUS == ON_THE_GROUND )
	for(int l=0; l<vBonus.size(); ++l)
	{
			if( vBonus[l]->GetRightFace() > left && vBonus[l]->GetLeftFace() < right )
			{
				bDisplayBonusMessage = true;
				if( Engine->Input_GetKey() == HGEK_ENTER )
				{	
					switch( vBonus[l]->GetId() )
					{
					case MEDIKIT: if( Aztec->GetHealth() < 100 )           
								  {  Aztec->RaiseHealth(30); SoundEffectsList.push_back(PlaySoundEffect(PICK_HEALTH));  vBonus[l]->Die(); }
											 break;
					case AMMO_ASSAULTRIFLE:  if( !Aztec->AssaultRifle.IsFull() )
											 { Aztec->AssaultRifle.RaiseAmmo(40); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); vBonus[l]->Die(); }
											 break;
					case AMMO_SIDEARM:       if( !Aztec->SideArm.IsFull() )
											 { Aztec->SideArm.RaiseAmmo(20); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); vBonus[l]->Die();}
											 break;
					case AMMO_GRENADE:       if( Aztec->GetGrenade() < 6)
											 { Aztec->RaiseGrenade(1); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); vBonus[l]->Die();}
											 break;
					case AMMO_SHOTGUN:		 if( !Aztec->ShotGun.IsFull() )
											 { 
												 Aztec->ShotGun.RaiseAmmo(40); 
												 SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); 
												 vBonus[l]->Die(); 
												 extern bool bActivateShotgun;
												 bActivateShotgun = true;
											 }
											 break;	
					case AMMO_LAUNCHER:      if( !Aztec->RocketLauncher.IsFull() )
											 {
												 Aztec->RocketLauncher.RaiseAmmo(40); 
												 SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); 
												 vBonus[l]->Die();
												 extern bool bActivateLauncher;	
												 bActivateLauncher = true;
											 }
											 break;
					}

					break;
				}
		}
	}

}




