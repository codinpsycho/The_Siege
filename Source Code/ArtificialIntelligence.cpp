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



#include "TileMap.h"
#include "Enemy.h"
#include "Protagonist.h"
#include "hgeanim.h"
#include "LevelObjects.h"
#include <hgeparticle.h>
#include <string>
#include <vector>
#include "sounds.h"
#include "dialog.h"
#include "Bullet.h"

using std::vector;

Bullet* createEnemyBullet(Enemy* , HTEXTURE , HGE* Engine,std::vector< Bullet* > &);
extern std::vector< Bullet*> vInGameBullets;
extern TileMap *BoxSprite;
extern TileMap *MixSprite;
extern std::vector< Enemy* > pGameEnemyList;    
std::vector < Enemy* > vIdleStateEnemies;
extern std::vector< hgeParticleSystem* > ParticleList;	
extern HTEXTURE hTexBullets;
extern std::vector<Grenade*> GrenadeList;
extern HTEXTURE hTexBullets;
extern vector <SoundInfo> SoundEffectsList;
extern std::vector<Grenade*> GrenadeList;
static bool Grenadeflag = false;
const int ALIENS_PER_FRAME = 3;
const int SCREENWIDTH = 1366;
extern HTEXTURE hTexEnemy;
extern HTEXTURE DamageBoxTex;
extern HGE* Engine;
extern std::vector< Enemy*  > pDeadBodies;
extern vector <InfoDialog> EnemyDialogsList;
extern int THIS_IS_LEVEL_NUMBER;

hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int dir);
Grenade* createGrenade(Enemy* , HTEXTURE );
bool AdjustEnemies(Enemy* pEnemy, std::vector< Enemy* > &pGameEnemyList );
bool ProceedAdjustments(Enemy *&enemy, float dt);
Grenade* createGrenade(Enemy* enm, HTEXTURE hTex);
void ManageEnemyParticleEffect(Enemy *En);
//////////////////////////////// Functions ////////////////////
inline float GetPlayerDist(Enemy *enm,Protagonist *pro)   // returns the distance b/w the enemy and the player sprites about the anchor point
{  return ( enm->vPosition.x - pro->vPosition.x );	  }

inline float turnPositive(float p ) 
{   if(p < 0) p *= -1;   return p; }  

void LaunchGrenade(Enemy* enemy)
{	
	if( enemy->ThrowGrenade() )
	{
		enemy->ChangeStance(THROW_GRENADE);
		//ENEMYSTANCE = THROW_GRENADE;
		GrenadeList.push_back ( createGrenade(enemy,hTexBullets) );
	}
}

float DerermineFace(const Enemy* enemy)
{ 
  float face=0.0f, x=0.0f;
  	
  switch( enemy->GetId() )	
  {
   case HUMAN : 
	   x = 65.0f;
	   break;
   case ALIEN1 : 
   case ALIEN2 :	
   case ALIEN3 :	    
	   x = 65.0f;  
	   break;
  }
	
  if( enemy->GetFacing() == FACELEFT ) face = enemy->vPosition.x + x;
  else 
	  face = enemy->GetRightFace() - x;	
  return face;
}


bool AdjustEnemies(Enemy* pEnemy, std::vector< Enemy* > &pGameEnemyList )
{
	int qSize = vIdleStateEnemies.size();
	--qSize;

	for(int i=qSize; i > 0; i-- )
	{ 
		Enemy* EnCount = vIdleStateEnemies[i];

		if( pEnemy != EnCount )
		{
			float fDist = pEnemy->vPosition.x - EnCount->vPosition.x;

			if( ( fDist < +4.0f && fDist > -4.0f )/* fDist == 0.0f*/ 
				&& ( pEnemy->eAI_STATE != ADJUSTRIGHT && EnCount->eAI_STATE != ADJUSTRIGHT ) 
				&& ( pEnemy->eAI_STATE != ADJUSTLEFT && EnCount->eAI_STATE != ADJUSTLEFT)    )
			{
				switch(pEnemy->GetId())
				{
				case  HUMAN: pEnemy->fAdjVal = 35.0f;  break;
				case ALIEN1:					
				case ALIEN3: pEnemy->fAdjVal = 30.0f;  break;
				case ALIEN2: pEnemy->fAdjVal = 25.0f;   				
				}	

				if( /*EnCount->vDirection.x == -1 &&*/ EnCount->GetFacing() == FACELEFT )
				pEnemy->SetAiState(ADJUSTRIGHT);
				else
				pEnemy->SetAiState(ADJUSTLEFT);

				return true;
			}
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProceedAdjustments(Enemy *&enemy, float dt)
{
	if(enemy->fAdjVal < 1.0f)
	{  
		enemy->fAdjVal = 0.0f;
		enemy->RestoreAiState();	
		enemy->anim->SetMode(HGEANIM_FWD); ////
		( enemy->GetFacing() == FACELEFT ) ? enemy->vDirection.x = -1 : enemy->vDirection.x = 1 ; 
		enemy->ChangeStance(IDLE);
		return false;
	}	
	
	enemy->fAdjVal -= 1.0f;
	float dir = 0.0f;
	enum ANIM{FORWARD=0,REVERSE=1}; 
	eARTIFICIAL_INTELLIGENCE ENEMY_AI = enemy->GetAiState();
	ePLAYER_STANCE ENEMY_FACING = enemy->GetFacing();
	ANIM PLAYANIM; 

	if( ENEMY_FACING == FACELEFT )
	{
		if(ENEMY_AI == ADJUSTLEFT)
		{
			dir = -1.0f;
			PLAYANIM = FORWARD;
		}
		else
		{
			dir = 1.0f;
			PLAYANIM = REVERSE;
		}
	}
	else 
	{
		if(ENEMY_AI == ADJUSTLEFT)
		{
			dir = -1.0f;
			PLAYANIM = REVERSE;
		}
		else 
		{
			dir = 1.0f;
			PLAYANIM = FORWARD;
		}
	}
		
	enemy->vDirection.x = dir;
	enemy->vPosition.x += dir * (enemy->GetSpeed() * dt);
	
	ANIM OLDMODE;

	switch ( enemy->anim->GetMode() )
	{
	case 0:  OLDMODE = FORWARD;
		  break;
	case 1:  OLDMODE = REVERSE;
		  break;
	}
	
	if( PLAYANIM != OLDMODE )
	{
	if( PLAYANIM == FORWARD )
		enemy->anim->SetMode(HGEANIM_FWD);
	else 
		enemy->anim->SetMode(HGEANIM_REV);
	}

	if( !enemy->anim->IsPlaying() ) 	enemy->ChangeStance(IDLE);  	  		
	enemy->ChangeStance(RUNNING);

  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NearGrenade(Enemy* enemy)
{
   for(int i=0; i<GrenadeList.size(); i++)
   {
		   Grenade *grenade = GrenadeList[i];
		   float center =  enemy->GetRightFace() - enemy->vPosition.x;	
		   center/=2;
		   center += enemy->vPosition.x;
			ePLAYER_STANCE STANCE =  enemy->GetStance();
		   float diff = center - grenade->vPosition.x;

			if( ( (diff > 0 && diff < 85.0f) || (diff < 0 && diff > -85) ) && grenade->vSpeed.y == 0.0f && (STANCE == IDLE || grenade->GetId() == LAUNCHER_GRENADE ) )
			{
				 
					if( enemy->GetFacing() == FACERIGHT )		
					{
						if( grenade->vPosition.x >= center )	 // adjust
						{
							if( enemy->GetAiState() != ADJUSTRIGHT )
							{ 
							  enemy->fAdjVal = 60.0f;
							  enemy->eAI_STATE = ADJUSTRIGHT;				
							}
						}
						else 
							if( STANCE != RUNNING )
							enemy->ChangeStance(RUNNING);
						return true;
					}
					else
					{
						 if( grenade->vPosition.x <= center ) // adjust
						 {
							 if( enemy->GetAiState() != ADJUSTRIGHT )
							 {
							   enemy->fAdjVal = 60.0f;
							   enemy->eAI_STATE = ADJUSTRIGHT;				
							 }
						 }
						 else 
							 if( STANCE != RUNNING )
							 enemy->ChangeStance(RUNNING);
						return true;	   
					}
			 }   
   }

return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetEnemyFace(Enemy* enemy, ePLAYER_STANCE FACE)
{
 float face;

 switch( enemy->GetId() )
 {
 case HUMAN:  face = ( FACE == FACELEFT ) ? ( enemy->GetLeftFace()+30 ) : ( enemy->GetRightFace()-30 );     break;
 case ALIEN1:
 case ALIEN3: face = ( FACE == FACELEFT ) ? ( enemy->GetLeftFace()+20 ) : ( enemy->GetRightFace()-20 );  	break;
 case ALIEN2: face = ( FACE == FACELEFT ) ? ( enemy->GetLeftFace()+10.0f ) : ( enemy->GetRightFace()-10.0f );		
 }	

return face;
}


enum BODY 
{
	FRONT, BACK, OTHER 
};
static float GetPlayerFace( Protagonist *Aztec, BODY Surface )
{
	float face = Aztec->vPosition.x + 60.0f;
	
	switch(Surface)
	{
	 case FRONT: face = ( Aztec->GetFacing() == FACERIGHT ) ? ( Aztec->GetRightFace()-50.0f ):( Aztec->GetLeftFace()+50.0f );   break;
	 case BACK:  face = ( Aztec->GetFacing() == FACERIGHT ) ? ( Aztec->GetLeftFace()+35.0f  ):( Aztec->GetRightFace()-35.0f );  break;
	 case OTHER: face = ( Aztec->GetFacing() == FACERIGHT ) ? ( Aztec->GetRightFace()-20.0f ):( Aztec->GetLeftFace()+20.0f );   break;
	}	

 return face; 
}



void SetBoxWidth( LevelObjects& object, float &Right, float &Left )
{
	switch( object.GetId() )
	{
	case 1: Right = object.GetRightFace() - 10.0f; Left = object.GetLeftFace() +  0.0f;	 break;  
	case 2: Right = object.GetRightFace() -  4.0f; Left = object.GetLeftFace() +  6.0f;  break;
	case 3: Right = object.GetRightFace() -  0.0f; Left = object.GetLeftFace() + 11.0f;  break;
	case 4: Right = object.GetRightFace() -  2.0f; Left = object.GetLeftFace() + 11.0f;  break;
	case 5: Right = object.GetRightFace() -  2.0f; Left = object.GetLeftFace() + 22.0f;	 break;
	case 6: Right = object.GetRightFace() - 20.0f; Left = object.GetLeftFace() +  2.0f;   
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


void CreateEnemyLauncherSpark(Enemy* enemy);

void ControlEnemy(Protagonist* &Aztec, Enemy* &enemy, float dt) 
{
	// Get Current State Of An Enemy
	enum eSETSTANCE { TO_NOTHING, TO_RUNNING, TO_IDLE, TO_THROW_GRENADE, TO_MELEE };

		   ePLAYER_STANCE ENEMYSTANCE = enemy->GetStance();
		   ePLAYER_STANCE ENEMYFACING = enemy->GetFacing();
	eARTIFICIAL_INTELLIGENCE ENEMY_AI = enemy->GetAiState();
		   const eENEMY ENEMYIDENTITY = enemy->GetId();
		     eSETSTANCE CHANGE_STANCE = TO_NOTHING;
			 
			 const float fDistance = GetPlayerDist(enemy,Aztec);   // distance between enemy and player
			 const float fCentre = Aztec->vPosition.x+55.0f;		
			 const float fEnemyFace = DerermineFace(enemy);
		
		enemy->Update(dt);   // Update
		if ( enemy->IsDead() ) return;	

	if( ENEMYSTANCE == MELEE && enemy->anim->GetFrame() == 1 && enemy->meleeFlag )
	{
		float feEnmFace = GetEnemyFace(enemy,enemy->GetFacing());
		float fePlayerFront = GetPlayerFace( Aztec, FRONT );
		float fpPlayerBack = GetPlayerFace( Aztec, BACK );
		eSOUNDEFFECTS PlayEffect=NULL_SOUND; 
		SoundEffectsList.push_back( PlaySoundEffect(MELEE_MISS) );
		enemy->meleeFlag = false;

			if(  ( fePlayerFront <= feEnmFace && feEnmFace <= fpPlayerBack ) || ( fePlayerFront > feEnmFace && feEnmFace >= fpPlayerBack )  )	
			{
				if( Aztec->GetDownFace() >= (enemy->vPosition.y + 35.0f) )
				{
					Aztec->LowerHealth(20);
					
					int dir = ( fCentre < fEnemyFace )? -1 : 1; 
					int m = (enemy->GetFacing()== FACERIGHT)? +1 : -1;
					float x = 	feEnmFace + m*10.0f;
					float y =  enemy->vPosition.y + 55.0f;

					SoundEffectsList.push_back( PlaySoundEffect(MELEE_ALIEN2) );

					ParticleList.push_back( ParticleFactory(HIT_BLOOD, x, y, dir) );
					ParticleList.push_back( ParticleFactory(HIT_BLOOD, x, y-10.0f, dir) );
					return;
				}
			}
		    
			
			for( int n = 0; n < BoxSprite->Objects.size(); n++ )
			{
				float BoxLeft  = BoxSprite->Objects[n].GetLeftFace();
				float BoxRight = BoxSprite->Objects[n].GetRightFace();
				SetBoxWidth( BoxSprite->Objects[n],BoxRight,BoxLeft );	
				if ( BoxLeft <= feEnmFace && feEnmFace <= BoxRight )  // collision detected
				{		
						BoxSprite->Objects[n].DecreaseHealth(50.0f);

						if (  ( BoxSprite->Objects[n].GetHealth() <= 50 ) && ( BoxSprite->Objects[n].GetId() == 1 || BoxSprite->Objects[n].GetId() == 2 )  )
						{
							BoxSprite->Objects[n].SetImage(DamageBoxTex);
							if(!BoxSprite->Objects[n].bDamageFlag)
								SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			

							if ( Aztec->GetFacing() == FACELEFT )
							{
								BoxSprite->Objects[n].Spr->SetFlip(true,false,false); 
								if(!BoxSprite->Objects[n].bDamageFlag)
									SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			
							}		
							BoxSprite->Objects[n].bDamageFlag = true;
						}
						
						switch(BoxSprite->Objects[n].GetId())
						{
						case 1: PlayEffect=MELEE_WOOD_BOX; break;
						case 2: PlayEffect=(BoxSprite->Objects[n].GetHealth()>50) ? MELEE_STEEL_BOX : MELEE_WOOD_BOX ; break;
						case 3: 
						case 4: PlayEffect=MELEE_ROCK; break;
						case 5:
						case 6: PlayEffect=MELEE_COIL; break;
						}

						SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );

						if( BoxSprite->Objects[n].GetHealth() <= 0 || BoxSprite->Objects[n].IsDead() )
						{
							enemy->ChangeStance(RUNNING);
							ENEMYSTANCE = enemy->GetStance();
							eParticles par;
							float dir=0.0f,x,y;
							switch( BoxSprite->Objects[n].GetId() )
							{
							 case 1:   
							 case 2:   par = BROWN_SMOKE; break;
							 case 3:   
							 case 4:   par = GREY_SMOKE; break; 
							}

							switch(BoxSprite->Objects[n].GetId())
							{
							case 1: PlayEffect=BREAK_WOOD_MELEE; break;
							case 2: PlayEffect=BREAK_WOOD_MELEE; break;
							case 3: 
							case 4: PlayEffect=BREAK_ROCK_MELEE; break;
							case 5:
							case 6: PlayEffect=BREAK_COIL_MELEE; break;
							}

							SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );

							x = BoxSprite->Objects[n].GetRightFace() - BoxSprite->Objects[n].GetLeftFace();
							y = BoxSprite->Objects[n].GetDownFace() - BoxSprite->Objects[n].GetUpFace();
							x/=2; x += BoxSprite->Objects[n].GetLeftFace();  y /= 2.0f; y += BoxSprite->Objects[n].GetUpFace();
							
							ParticleList.push_back ( ParticleFactory(par,x,y-20,dir) );
							ParticleList.push_back ( ParticleFactory(par,x,y+15,dir) );
							
							BoxSprite->Objects.erase(BoxSprite->Objects.begin() + n );
							
						}
					return ;
				}			
			}
			if(THIS_IS_LEVEL_NUMBER == 1)
			{
				if( MixSprite->Objects.size() > 0 )
				for( int q=0; q< MixSprite->Objects.size(); q++ )
				{
					if( !MixSprite->Objects[q].IsCollidable() ) continue;

					float BoxLeft  = MixSprite->Objects[q].GetLeftFace();
					float BoxRight = MixSprite->Objects[q].GetRightFace();
					SetBoxWidth( MixSprite->Objects[q],BoxRight,BoxLeft );
					if ( BoxLeft <= feEnmFace && feEnmFace <= BoxRight )  // collision detected
					{	
						MixSprite->Objects[q].DecreaseHealth(50.0f);		
						
						switch(MixSprite->Objects[q].GetId())
						{
						case 5:
						case 6: PlayEffect=MELEE_COIL; break;
						}

						SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );


						if( MixSprite->Objects[q].IsDead() || MixSprite->Objects[q].GetHealth() <= 0 )
						{
							enemy->ChangeStance(RUNNING);
							ENEMYSTANCE = enemy->GetStance();

							switch(MixSprite->Objects[q].GetId())
							{
							case 1: PlayEffect=BREAK_WOOD_MELEE; break;
							case 2: PlayEffect=BREAK_WOOD_MELEE; break;
							case 3: 
							case 4: PlayEffect=BREAK_ROCK_MELEE; break;
							case 5:
							case 6: PlayEffect=BREAK_COIL_MELEE; break;
							}

							SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );

							float dir=0.0f,x,y;
							x = MixSprite->Objects[q].GetRightFace() - MixSprite->Objects[q].GetLeftFace();
							y = MixSprite->Objects[q].GetDownFace() - MixSprite->Objects[q].GetUpFace();

							if( MixSprite->Objects[q].GetId() == 5 )
							{
							   y = MixSprite->Objects[q].GetUpFace() + 80.0f;
							   x/=2.0f; x += MixSprite->Objects[q].GetLeftFace();
							}
							else 
							{  x/=2.0f; x += MixSprite->Objects[q].GetLeftFace();  y /= 2.0f; y += MixSprite->Objects[q].GetUpFace();  }
							
							ParticleList.push_back ( ParticleFactory(BLACK_SMOKE,x,y-18.0f,dir) );
							ParticleList.push_back ( ParticleFactory(BLACK_SMOKE,x,y+15.0f,dir) );
							
							MixSprite->Objects.erase(MixSprite->Objects.begin() + q );
						}
						return ;
					}	
				}
		  
		  return ;	
		}
	}

	if ( ENEMYSTANCE == THROW_GRENADE && enemy->anim->GetFrame() == 1 &&  enemy->grenadeFlag )
	{
		GrenadeList.push_back ( createGrenade(enemy,hTexBullets) ); 
		SoundEffectsList.push_back( PlaySoundEffect(MELEE_MISS) );
		enemy->anim->Stop();
		enemy->grenadeFlag = false;
		return;
	}

	// check if a grenade is nearby

	if( ENEMYIDENTITY == HUMAN && (rand()%9) == 6	&& GrenadeList.size() > 0 )	
	{
		enemy->Speak(WARN,EnemyDialogsList);			
	}

	if( NearGrenade(enemy) )
	{
		ENEMYSTANCE = enemy->GetStance();
		ENEMY_AI = enemy->GetAiState();
	}
	
	/////////////// Set Enemy Facing //////////////////////////////////////////////////////////////////
		if( fEnemyFace <= fCentre )	
		{
			if( ENEMYFACING == FACELEFT )	  // enemy turns right 
			{
				enemy->SetFacing(FACERIGHT);
				ENEMYFACING = FACERIGHT;
				enemy->vDirection.x = 1;
				
				if(ENEMY_AI == STRATEGY && ENEMYSTANCE != IDLE ) 
				{
					enemy->ChangeStance(IDLE);	
					ENEMYSTANCE = enemy->GetStance();
				}
				else 
				if( ENEMY_AI == ATTACK && ENEMYSTANCE == IDLE )
				{
					enemy->ChangeStance(RUNNING);	
					ENEMYSTANCE = enemy->GetStance();
				}
			}
		}
		else if( (fCentre+100) < fEnemyFace || ENEMYSTANCE == IDLE ) 
		{
			if( ENEMYFACING == FACERIGHT )	 // if enemy faces right, it turns left
			{
				enemy->SetFacing(FACELEFT);   
				ENEMYFACING = FACELEFT;
				enemy->vDirection.x = -1;
				
				if(ENEMY_AI == ATTACK)
				{   		
					enemy->ChangeStance(IDLE);	
					ENEMYSTANCE = enemy->GetStance();
				}
				
			}
		}
////////////////////////////////////////////////////////////////////  Facing of an enemy is updated every frame

////////////////////////////////////////////////////////////////////  Control Stances of enemy
	    if ( ENEMY_AI != ADJUSTRIGHT && ENEMY_AI != ADJUSTLEFT && ENEMYSTANCE != MELEE )
		{
				///////////////////////////////////////////////////////////// ADVANCED ATTACKING 
			    
				if(ENEMYIDENTITY == HUMAN && (Aztec->GetStance() == DUCK || Aztec->GetStance() == LOWMOVE) 
																			&& enemy->vPosition.x < SCREENWIDTH-160.0F && enemy->GetRightFace() > 0 )
				{
					if( ( ( fDistance > 150.0f && fDistance < 600.0f ) || ( fDistance < -5.0f && fDistance > -420.0f ) )
					&& (rand()%11) == 7 && GrenadeList.size() <= 1 && (rand()%4 == 3) )	
					{
						if( enemy->UseGrenade.TimerEnd() )	
						{
							Grenade* gred = createGrenade(enemy,hTexBullets);
							gred->vSpeed.y  += 100.0f;
							
							//gred->vSpeed.x = turnPositive(fDistance-70.0f);

							if( fDistance >= 0 )
							gred->vSpeed.x = fDistance-70.0f;
							if( fDistance < 0 )
							gred->vSpeed.x  =  -fDistance-70.0f;	

							GrenadeList.push_back(gred);
							SoundEffectsList.push_back (PlaySoundEffect(ROCKET_LAUNCHER));
							
							CreateEnemyLauncherSpark(enemy);
							if(fDistance < 200.0f && fDistance > 0)
								enemy->SetAiState(ADJUSTRIGHT);
							    enemy->fAdjVal = 20.0f;
								return;
						}
					}	
				}	
				

				if( Aztec->GetStance() == IDLE && ENEMYSTANCE == IDLE )
				{
					bool GoFlag = false;

					if ( Aztec->GetFacing() == FACERIGHT && ENEMYFACING == FACELEFT )
					{
						if( fDistance < 30 && fDistance > -10 ) 
							GoFlag = true;
					}	
					else if ( Aztec->GetFacing() == FACELEFT && ENEMYFACING == FACERIGHT )
					{
						if( fDistance > -30 && fDistance < 0 ) 
							GoFlag = true;
					}
					else if ( Aztec->GetFacing() ==  ENEMYFACING )
					{
						if( fDistance < 40 && fDistance > -15 ) 
							GoFlag = true;
						else 
							if( fDistance > -40 && fDistance < 15 ) 
								GoFlag = true;
					}

					if( GoFlag == true )
					{
						switch(ENEMYIDENTITY)
						{
						case HUMAN: enemy->fAdjVal = 50.0f;
							break;
						case ALIEN1:					
						case ALIEN3:	enemy->fAdjVal = 40.0f;		
							break;
						case ALIEN2:	enemy->fAdjVal = 20.0f;				
						}	
						if(ENEMYFACING == FACELEFT)
							enemy->SetAiState(ADJUSTRIGHT);
						else
							enemy->SetAiState(ADJUSTLEFT);

						return; 
					}
				}
				///////////////////////////////////////////////////////////// ADVANCED ATTACKING... END	 
				
				///////////////////////////////////////////////////////////// STATE CHANGE ///////////			
				
				if( ENEMYIDENTITY == ALIEN2 )
				{	
						if( ( fDistance <  65.0f && fDistance > -65.0f && ENEMYFACING == FACELEFT  ) ||
							( fDistance > -65.0f && fDistance < 65.0f && ENEMYFACING == FACERIGHT )  )  
						{
							if ( Aztec->GetStance() != JUMPING )
							if( enemy->Melee.TimerEnd() )
							{
								enemy->ChangeStance(MELEE);
								ENEMYSTANCE = MELEE; 
 								return;
							}
						}
						else
						{																 // remove facing from here			
							if ( ENEMYSTANCE == IDLE && fDistance > 65.0f && fDistance <= 200.0f )
							{
								CHANGE_STANCE = TO_RUNNING;
							}
							else  if ( ENEMYSTANCE == IDLE && fDistance < -75.0f && fDistance >= -310.0f && ENEMY_AI == ATTACK )
							{		
									CHANGE_STANCE = TO_RUNNING;
							}
							else 
							{	
								bool flag = true;
								
								for(int i=0; i<BoxSprite->Objects.size(); i++)
								{
									LevelObjects & Ob = BoxSprite->Objects[i];
									if( Ob.IsCollidable() && !Ob.IsDead() && Ob.GetLeftFace() < SCREENWIDTH && Ob.GetRightFace() > 0 )
									{
										float diff = enemy->vPosition.x - Ob.GetLeftFace();
									  if( ( diff > 0.0f && diff < 180.0f && ENEMYFACING == FACELEFT ) 
									   || ( diff < 0.0f && diff > -180.0f && ENEMYFACING == FACERIGHT ) ) 
									  {
										CHANGE_STANCE = TO_RUNNING;	
										flag = false;
									  }
									}
								}	

								if( THIS_IS_LEVEL_NUMBER == 1 )
								{
									if(flag )
									for(int i=0; i<MixSprite->Objects.size(); i++)
									{
										LevelObjects & Ob = MixSprite->Objects[i];
										if( Ob.IsCollidable() && !Ob.IsDead() && Ob.GetLeftFace() < SCREENWIDTH && Ob.GetRightFace() > 0 )
										{
											float diff = enemy->vPosition.x - Ob.GetLeftFace();
											if( ( diff > 0.0f && diff < 180.0f && ENEMYFACING == FACELEFT ) 
											 || ( diff < 0.0f && diff > -180.0f && ENEMYFACING == FACERIGHT ) ) 
											{
												CHANGE_STANCE = TO_RUNNING;	
											}
										}
									}
								}				
							}

						}

				}// END OF ALIEN2 BLOCK
                
				if( ENEMYIDENTITY != HUMAN  && fDistance > 230 && fDistance < 650  )   // THROW GRENADE
				{
					CHANGE_STANCE = TO_THROW_GRENADE; 		
				}
				
				if( ENEMY_AI == CHASE && CHANGE_STANCE == TO_NOTHING )				
				{
						if( ENEMYFACING == Aztec->GetFacing() && fDistance < 0.0f )	  // direction of player and enemy should be same		
						{
							if( fDistance < -190.0f && fDistance > -320.0f )                   // start chasing and don't fire if aliens
							{
								CHANGE_STANCE = TO_RUNNING;
								if(ENEMYIDENTITY == HUMAN && !(rand()%2) )  enemy->Speak(TAUNT,EnemyDialogsList);
							}
							else 
								if( fDistance <= -320.0f )										// stop chasing and give up, try throwing a grenade
								{
									if( ENEMYIDENTITY != HUMAN )
										    CHANGE_STANCE = TO_THROW_GRENADE; 
									else 
									{	
										CHANGE_STANCE = TO_IDLE;	
										if(ENEMYIDENTITY == HUMAN && !(rand()%2) )  enemy->Speak(COMMAND,EnemyDialogsList);
									}
								}
								else 
									if( fDistance > - 80.0f && fDistance < 0.0f && ENEMYIDENTITY != ALIEN2 && ENEMYFACING == FACERIGHT)	
									{	
										CHANGE_STANCE = TO_IDLE;

										if(ENEMYIDENTITY == HUMAN && !(rand()%2) )  
											enemy->Speak(COMPROMISE,EnemyDialogsList);

											
												if( ((rand()%29) == 16) && enemy->Fire() )
												{	
													createEnemyBullet(enemy,hTexBullets,Engine,vInGameBullets);
													SoundEffectsList.push_back(PlaySoundEffect(NPC_ASSAULT_FIRE));
													if( ENEMYIDENTITY == HUMAN )	
													   ManageEnemyParticleEffect(enemy);
												}
											

									}
						}	
				}

				////////////////////////////////////////////  Check if enemy throws Grenade
				
					if( CHANGE_STANCE == TO_THROW_GRENADE )
					{	
						if( enemy->ThrowGrenade()  && ( rand()%5 == 3 ) && GrenadeList.size() < 3 )
						{
							enemy->ChangeStance(THROW_GRENADE);
							ENEMYSTANCE = THROW_GRENADE;
							return;
						}
						else
							CHANGE_STANCE == TO_NOTHING;
					}
				
				///////////////////////////////// this is where the enemy actually changes its stance 

					if( fDistance < 600 && fDistance > 200 && (rand()%31) == 7 && (rand()%9) == 6 && ENEMYIDENTITY != ALIEN2 )
					{
						CHANGE_STANCE = TO_IDLE;	
					}
				
					if( CHANGE_STANCE == TO_NOTHING && ENEMYSTANCE != THROW_GRENADE && ENEMY_AI != CHASE )  
					{  
					  if( (rand()%6) == 2 && (rand()%5) == 2 && enemy->CanChangeStance() && enemy->vPosition.x < 1200.0f && enemy->vPosition.x > 20 )

						{
							if( ENEMYSTANCE == RUNNING && fDistance > 230 )
							{
								// change stance
									CHANGE_STANCE  = TO_IDLE;  

									if( ENEMYIDENTITY == HUMAN && !(rand()%2) )			
									{
										if(ENEMY_AI == STRATEGY)
										{
											switch( (rand()%3) )
											{				
											case 0:	enemy->Speak(COMMAND,EnemyDialogsList); break;
											case 1:	enemy->Speak(REQUEST,EnemyDialogsList);	break;
											case 2:	enemy->Speak(STATUS,EnemyDialogsList);	break;
											}
										}
										else if(ENEMY_AI == ATTACK)
										{
											if( !(rand()%2) )
											enemy->Speak(COMMAND,EnemyDialogsList);
											else 
											enemy->Speak(TAUNT,EnemyDialogsList);			
										}
									}  
							}
							else 
								if ( ENEMYSTANCE == IDLE )
								{
										CHANGE_STANCE = TO_RUNNING;  

									if( ENEMYIDENTITY == HUMAN && !(rand()%2) && (fDistance > 200.0f || fDistance < -200) )			
									{
										if(ENEMY_AI == STRATEGY)
										{
											switch( (rand()%3) )
											{				
												case 0:	enemy->Speak(COMMAND,EnemyDialogsList); break;
												case 1:	enemy->Speak(REQUEST,EnemyDialogsList);	break;
												case 2:	enemy->Speak(STATUS,EnemyDialogsList);	break;
											}
										}
										else if(ENEMY_AI == ATTACK)
										{
												enemy->Speak(TAUNT,EnemyDialogsList);			
										}
									}
								}
						}
					}
				
				//////////////////////////////////////////////////////////////  CHANGE STANCE HERE
				if( ENEMYSTANCE != MELEE && ENEMYSTANCE != THROW_GRENADE )
				{
					switch(CHANGE_STANCE)
					{
					case TO_IDLE:		enemy->ChangeStance(IDLE);
						ENEMYSTANCE = enemy->GetStance(); 
						ENEMYFACING = enemy->GetFacing(); 
						CHANGE_STANCE=TO_NOTHING;
						break;
					case TO_RUNNING:    enemy->ChangeStance(RUNNING);
						ENEMYSTANCE = enemy->GetStance(); 
						ENEMYFACING = enemy->GetFacing(); 
						CHANGE_STANCE=TO_NOTHING;
						break;	
					}
				}

			}
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////  Adjust Logic

		for( int qi=0; qi < vIdleStateEnemies.size(); qi++ ) // maintain the queue for enemies with stance IDLE
		{
			if( vIdleStateEnemies[qi]->GetStance() != IDLE )
			{	
				vIdleStateEnemies.erase( vIdleStateEnemies.begin() + qi );
				if( qi !=0 && qi != (vIdleStateEnemies.size()-1) ) --qi;
			}
		}

		if( ENEMYSTANCE == IDLE )
		{
			const int qSize = vIdleStateEnemies.size();
			bool flag = true;

			if( qSize > 0 ) // check if this enemy already exists in the queue
				for( int q=0; q < qSize; q++ )  if( enemy == vIdleStateEnemies[q] )	 {  flag = false;  break;  }	

				if(flag)  vIdleStateEnemies.push_back(enemy);   // push this enemy in to the queue

				AdjustEnemies(enemy,pGameEnemyList); 
				ENEMY_AI = enemy->GetAiState();
				ENEMYSTANCE = enemy->GetStance();
		}

		if( ENEMY_AI == ADJUSTRIGHT || ENEMY_AI == ADJUSTLEFT )
		{
			if( !ProceedAdjustments(enemy,dt) )
			{
				ENEMYSTANCE = enemy->GetStance(); 
				ENEMY_AI = enemy->GetAiState();
				return ;
			}
		}

		
		if( ENEMYSTANCE != MELEE && ENEMYSTANCE != THROW_GRENADE )
		{   
			///////////////////////////////// Check for obstacles ////////////////////////////////  Collision Detection
			std::vector< LevelObjects* >  OnScreenObjects;  // maintain a queue of objects visible on screen
				
			for ( int s=0; s < BoxSprite->Objects.size(); s++ )
			{		
				LevelObjects *LevOb = &BoxSprite->Objects[s];	
				if( LevOb->GetRightFace() > -1.0f && LevOb->GetLeftFace() < 1400 && !LevOb->IsDead() )
				{
					OnScreenObjects.push_back(LevOb);	
				}
			}

			if( THIS_IS_LEVEL_NUMBER == 1 )
			{
				for ( int s=0; s < MixSprite->Objects.size(); s++ )
				{		
					LevelObjects *LevOb = &MixSprite->Objects[s];	
					if( LevOb->GetRightFace() > -1.0f && LevOb->GetLeftFace() < 1400 && !LevOb->IsDead() && LevOb->GetId() != 7 && LevOb->GetId() != 8 )
					{
						OnScreenObjects.push_back(LevOb);	
					}
				}
			}
			
			for ( int ic=0; ic<OnScreenObjects.size(); ic++ )
			{  
				float ObjectLeft;  // = OnScreenObjects[ic]->GetLeftFace();
				float ObjectRight; // = OnScreenObjects[ic]->GetRightFace();
				SetBoxWidth(*OnScreenObjects[ic],ObjectRight,ObjectLeft);	
				if( ObjectRight > GetEnemyFace(enemy,FACELEFT) && ObjectLeft < enemy->vPosition.x )	
				{
					if( ENEMY_AI == ADJUSTLEFT )
					{ 
						enemy->eAI_STATE = ADJUSTRIGHT; 
						enemy->fAdjVal += 15; 
					}
					else if(ENEMYIDENTITY != ALIEN2)
					{
					  enemy->ChangeStance(IDLE);
					  ENEMYSTANCE = enemy->GetStance();
					}
					else
					{
						if( enemy->Melee.TimerEnd() && ENEMYFACING == FACELEFT )
						{
							enemy->ChangeStance(MELEE); 
							return; 
						}
						else 
						{	
							enemy->ChangeStance(IDLE);
							ENEMYSTANCE = enemy->GetStance();	
						}
						
					}
				}	
				else 
				if( ObjectLeft < GetEnemyFace(enemy,FACERIGHT) && ObjectLeft > enemy->vPosition.x )	
				{  
					if( enemy->eAI_STATE == ADJUSTRIGHT )
					{  
						enemy->eAI_STATE = ADJUSTLEFT; 
						enemy->fAdjVal += 15; 
					}
					else if(ENEMYIDENTITY != ALIEN2)
					{
						enemy->ChangeStance(IDLE);
						ENEMYSTANCE = enemy->GetStance();
					}
					else
					{
						if( enemy->Melee.TimerEnd() && ENEMYFACING == FACERIGHT )
						{
						    enemy->ChangeStance(MELEE);
							return; 
						}
						else 
						{	
							enemy->ChangeStance(IDLE);
							ENEMYSTANCE = enemy->GetStance();	
						}
					}
				}	
			}

			//////////////////////////////////////////////////////////////////////////////////////
		}
		
		///////////////////////////////// Movement ////////////////////////////////////////////////////////////////
		
		if( ENEMY_AI != ADJUSTRIGHT && ENEMY_AI != ADJUSTLEFT && ENEMY_AI != MELEE && ENEMY_AI != THROW_GRENADE ) 
		{
			if( ENEMYSTANCE == RUNNING )
			{
				enemy->Move(dt);
				if( !enemy->IsPlaying() ) enemy->ChangeStance(IDLE);
			    enemy->ChangeStance( RUNNING ); 

					//////////////////////////////////////////////////////////////////////////////////////////////////
					if( ENEMYIDENTITY == HUMAN && (rand()%9) == 7 && (fDistance < -250.0f || fDistance > 350.0f) && enemy->vPosition.x < 1340.0f )			
					{
						if(ENEMY_AI == STRATEGY)
						{
							int num = 0; for (int p=0; p < pGameEnemyList.size(); p++) if( pGameEnemyList[p]->vPosition.x < 1340.0f ) num++;

							switch( (rand()%2) )
							{				
							case 0:	if(num > 1)  enemy->Speak(COMMAND,EnemyDialogsList); 
									else  enemy->Speak(STATUS,EnemyDialogsList);			

							case 1:	if(num > 1)  enemy->Speak(STATUS,EnemyDialogsList);	
									else  enemy->Speak(REQUEST,EnemyDialogsList);			
									break;
							}
						}
						else //if(ENEMY_AI == ATTACK)
						{	
								enemy->Speak(COMMAND,EnemyDialogsList);			
						}
					}  
					/////////////////////////////////////////////////////////////////////////////////////////////////
			}
			else 
				if( ENEMYSTANCE == IDLE )
				{
					
					if( ENEMYIDENTITY != HUMAN && enemy->vPosition.x < 1360.0f && 
												( ENEMYFACING != Aztec->GetFacing() || (fDistance < -50 &&  ENEMYFACING == Aztec->GetFacing()) )  )
					{
						if( ((rand()%20) == 16) && enemy->Fire() && (rand()%3 == 2) )
						{
							createEnemyBullet(enemy,hTexBullets,Engine,vInGameBullets);
							SoundEffectsList.push_back(PlaySoundEffect(NPC_ASSAULT_FIRE));
						}				
					}
					
					    //////  speak  ////////////////////////////////////////////////////////////////////////////////////////////
						if( ENEMYIDENTITY == HUMAN && (rand()%9) == 7 && (fDistance < -250.0f || fDistance > 250.0f) && enemy->vPosition.x < 1340.0f )			
						{
							if(ENEMY_AI == STRATEGY)
							{
								int num = 0; for (int p=0; p < pGameEnemyList.size(); p++) if( pGameEnemyList[p]->vPosition.x < 1340.0f ) num++;

								switch( (rand()%2) )
								{				
								case 0:	if(num > 1)  enemy->Speak(COMMAND,EnemyDialogsList); 
										else  enemy->Speak(STATUS,EnemyDialogsList);			

								case 1:	if(num > 1)  enemy->Speak(REQUEST,EnemyDialogsList);	
										else  enemy->Speak(STATUS,EnemyDialogsList);			
										break;
								}
							}
							else //if(ENEMY_AI == ATTACK )
							{	
								enemy->Speak(TAUNT,EnemyDialogsList);			
							}

 							
						}  
					/////////////////////////////////////////////////////////////////////////////////////////////////
				}
		}


		if( ENEMYIDENTITY == HUMAN && enemy->vPosition.x < 1360.0f && 
		  ( ENEMYFACING != Aztec->GetFacing() || (fDistance < -50 &&  ENEMYFACING == Aztec->GetFacing()) )  )	
		{
			if(((rand()%30) == 16) && (rand()%3) == 2  && enemy->Fire() )
			{
				createEnemyBullet(enemy,hTexBullets,Engine,vInGameBullets);
				SoundEffectsList.push_back(PlaySoundEffect(NPC_ASSAULT_FIRE));
				ManageEnemyParticleEffect(enemy);
			}
		}

}



////////////////////////////////////////  ALIENS  ////////////////////////////////////////////////////////////////////////

float GenerateX()
{
	float temp = 1450 + rand()%300 + ( 20 * (rand()%2) ) ;

	for (unsigned int i = 0; i < BoxSprite->Objects.size(); i++ )
	{
		if ( temp > BoxSprite->Objects[i].GetLeftFace()  && temp < BoxSprite->Objects[i].GetRightFace()  )
		{
			GenerateX();
		}
	}
	if ( THIS_IS_LEVEL_NUMBER == 1)
	{
		for (unsigned int i = 0; i < MixSprite->Objects.size(); i++ )
		{
			if ( temp > MixSprite->Objects[i].GetLeftFace()  && temp < MixSprite->Objects[i].GetRightFace() && BoxSprite->Objects[i].IsCollidable() )
			{
				GenerateX();
			}
		}
	}

	return temp;
}


Enemy* CreateEnemy(int opt)  /// Enemy(eENEMY id,ePLAYER_STANCE face,ePLAYER_STANCE eStance,hgeVector vPos,hgeVector vDir) ....constructor
{
	eENEMY id=HUMAN; // default
	ePLAYER_STANCE Facing=FACELEFT;
	float dir = -1.0f;
	float x = 0.0f;
	/*
	switch( rand()%3 )	
	{
	case 0: if(rand()%5 == 2)
			{
				x = -120 -1*(rand()%101);
				dir = 1.0f; 
				Facing = FACERIGHT;
				break;
			}
	
	default: x = GenerateX();
	}
	*/
	float yP = 480.0f;
	
	if(THIS_IS_LEVEL_NUMBER==2) yP = 565;

	hgeVector vPos( SCREENWIDTH+100+( rand()%201 ), yP );
	
	switch(opt)
	{
	case 0:  id = HUMAN;   vPos.y += 5.0f;		break;
	case 1:  id = ALIEN1;  		break; 
	case 2:  id = ALIEN3;  		break; 
	case 3:  id = ALIEN2;  vPos.y -= 2.0f;		break;
	}

	
	Enemy *enemy = new Enemy ( id, Facing,( ( rand()%37 == 23 )? IDLE : RUNNING ), vPos, hgeVector(dir,0.0f) );

	if( enemy->GetFacing() == FACERIGHT ) enemy->eAI_STATE = ATTACK;
	
	return enemy;
}

bool LevelOneFlag=true;
extern HTEXTURE hSpeakerTex;

bool BringEnemy(int level)
{
	srand(time(NULL));
	if( pGameEnemyList.size() < ALIENS_PER_FRAME+(rand()%3) )   
	{
		int opt=0;	
		if(level == 1)  opt = 0; // only human 
		else  opt = rand()%4;    // 0,1,2,3		
		
		Enemy* enemy = CreateEnemy(opt);
		enemy->Init(Engine,hTexEnemy,hSpeakerTex);
		pGameEnemyList.push_back(enemy);

		return true;
	}/// end of if block	 			
	return false;
}



////////////////////////////////////  check existance with in screen and list ///////////////////////////
void checkExistance()
{
	for(int i=0; i<pGameEnemyList.size(); i++)
	{	
		// if enemy is dead and death animation has been played
		if( pGameEnemyList[i]->IsDead() && !pGameEnemyList[i]->anim->IsPlaying() )  
		{  
			pDeadBodies.push_back(pGameEnemyList[i]);  // this pushes the pointer created with new in to another list 
			// erase the pointer member now from the main enemy list
			vector<Enemy*>::iterator itr=pGameEnemyList.begin();
			itr+=i;
			itr = pGameEnemyList.erase(itr);
			if( i != 0  && i != pGameEnemyList.size() )
				i--;
			continue;
		}		
		if( pGameEnemyList[i]->vPosition.x < -600 ) 
		{   
			pGameEnemyList[i]->Release();  // call frees all the memory consumed by the inside of the object
			delete pGameEnemyList[i];
			std::vector<Enemy*>::iterator itr = pGameEnemyList.begin();
			itr += i;
			itr = pGameEnemyList.erase(itr);
			if( i != 0  && i != pGameEnemyList.size() )
				i--;
			continue;
		}
	}

	////// check and clear deadbodies
	for ( int bl=0; bl<pDeadBodies.size(); bl++  )
		if( pDeadBodies[bl]->vPosition.x < -200 ) // if dead body crosses this mark they'll be removed
		{   
			pDeadBodies[bl]->Release();
			delete pDeadBodies[bl];
			std::vector<Enemy*>::iterator itr = pDeadBodies.begin();
			itr += bl;
			itr = pDeadBodies.erase(itr);
			if( bl != 0  && bl != pDeadBodies.size() )   bl--;
			continue;
		}

}



void CreateEnemyLauncherSpark(Enemy* enemy)
{
	if( enemy->GetId() != HUMAN ) return;
	
	float x=0.0f, fHeight=0.0f;

	x  = ( enemy->GetFacing() == FACERIGHT ) ? (enemy->GetRightFace()-27):(enemy->GetLeftFace()+27);

	fHeight = 58.0f;

	int dir =  ( enemy->GetFacing() == FACERIGHT ) ?  -1 : 1 ;

	
	
	ParticleList.push_back(ParticleFactory(LAUNCHER_SPARK, x, enemy->vPosition.y + fHeight, dir ) );
	
}


