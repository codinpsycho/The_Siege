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





#include "StateLevel1.h"
#include <hge.h>
#include "StateGamePaused.h"
#include "GameStateManager.h"
#include <hgefont.h>
#include <hgegui.h>
#include "TileMap.h"
#include "sprite.h"
#include "Timer.h"
#include "Protagonist.h"
#include "Enemy.h"
#include "LevelObjects.h"
#include "Weapon.h"
#include "Bullet.h"
#include "sounds.h"
#include <hgeparticle.h>
#include <hgecolor.h>
#include <vector>
#include <hgesprite.h>


//Extern
extern Protagonist *Aztec;
extern hgeSprite *ParSprite;
extern hgeSprite *GunSparkSprite;
extern hgeSprite *FireHitSprite;
extern HTEXTURE ParTex;
extern HTEXTURE GunSparkTex;
extern HTEXTURE FireHitTex;
extern HTEXTURE hLeafTex;
extern HTEXTURE cloud;
extern HTEXTURE Objects;
extern hgeSprite *blastSprite;
extern hgeSprite *GrenadeBlastSprite;
extern hgeSprite *Health;
extern hgeSprite *CurWeapon;
extern hgeFont *font;
extern hgeSprite *sprGrenade;
extern CONDITION PLAYERSTATUS;
extern vector <SoundInfo> SoundEffectsList;
extern HEFFECT bird1;
extern HEFFECT bird2;
extern HTEXTURE texBirds;
extern HTEXTURE Feathertex;
extern HTEXTURE Fallingtex;
extern hgeSprite *FeatherSprite;
extern vector<ScoreUp> vScores;
extern std::vector< Bullet* > vInGameBullets;     // list of pointers to bullets
extern vector<hgeParticleSystem*> ParticleList;		//List of particle effects
void AddScore(hgeVector _position, char* _score, enum eScores);
Timer BirdTimer(9000);
bool bPlaySound = false;
extern int Total_kills, Total_Score;
extern int Birds_killed, hits_sustained, Box_destroyed,Melees, Bullets_Wasted;

// Particle Factory


// prototypes
struct ScoreUp;
void ManageParticleList(vector<hgeParticleSystem*> &ParticleList);
void RenderLeaves(vector<Leaf> &Leaves);
void UpdateLeaves(vector<Leaf> &Leaves);
void CreateEffect(Bullet* bul, LevelObjects &Box, std::vector< hgeParticleSystem* > &ParticleList);
void CreateEffect( Bullet* bul, std::vector< hgeParticleSystem* > &ParticleList );
void CreateEffect( Protagonist* Aztec,std::vector< hgeParticleSystem* > &ParticleList, eParticles id = JUMP_DUST, Enemy* enm = 0);
void CreateEffect( Protagonist* Aztec,std::vector< hgeParticleSystem* > &ParticleList, Enemy* enm=0 ,eParticles id=JUMP_DUST );
void AddLeaf(vector<Leaf> &Leaves);
hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int direction);



hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int direction) //Accepts ID and X,Y co-ordinates for the particle
{
	hgeParticleSystem *temp=0;

	if (direction > 0)  direction = 1;	
	else 
		if (direction < 0)  direction = -1;
		  else
		 	  direction = 0;

	switch (id)
	{
	case BLACK_SMOKE:    temp = new hgeParticleSystem("Particle Effects/blacksmoke.psi",ParSprite);			break;
	case BROWN_SMOKE:    temp = new hgeParticleSystem("Particle Effects/brownsmoke.psi",ParSprite);			break;
	case GREY_SMOKE:     temp = new hgeParticleSystem("Particle Effects/greysmoke.psi",ParSprite);			break;
	case HIT_EFFECT:     temp = new hgeParticleSystem("Particle Effects/hiteffect.psi",ParSprite);			break;
	case HIT_BLOOD:      temp = new hgeParticleSystem("Particle Effects/hitblood.psi",ParSprite);			break;
	case JUMP_DUST:      temp = new hgeParticleSystem("Particle Effects/jump.psi",ParSprite);				break;
	case LAUNCHER_TRAIL: temp = new hgeParticleSystem("Particle Effects/launchertrail.psi",ParSprite);      break;
	case GUN_SPARK:		 temp = new hgeParticleSystem("Particle Effects/gunspark.psi",GunSparkSprite);		break;
	case HIT_FIRE:	     temp = new hgeParticleSystem("Particle Effects/firehit.psi",FireHitSprite); 
						 FireHitSprite->SetBlendMode(BLEND_ALPHAADD);				                        break;
    case HIT_FIRE_RED:	     temp = new hgeParticleSystem("Particle Effects/firehitpink.psi",FireHitSprite);		
						 FireHitSprite->SetBlendMode(BLEND_ALPHAADD);				                        break;
	case HIT_FIRE_BLUE:	     temp = new hgeParticleSystem("Particle Effects/firehitpurple.psi",FireHitSprite);		
						 FireHitSprite->SetBlendMode(BLEND_ALPHAADD);				                        break;
	case HIT_FIRE_GREEN:	     temp = new hgeParticleSystem("Particle Effects/firehitgreen.psi",FireHitSprite);		
						 FireHitSprite->SetBlendMode(BLEND_ALPHAADD);				                        break; 	

	case BLAST:     	 temp = new hgeParticleSystem("Particle Effects/blast.psi",blastSprite);		    break;
    case GRENADE_BLAST:  temp = new hgeParticleSystem("Particle Effects/blast3.psi",GrenadeBlastSprite);    break;
	case BLAST_DEBRIS:   temp = new hgeParticleSystem("Particle Effects/debris.psi",ParSprite);             break;
	case LAUNCHER_SPARK: temp = new hgeParticleSystem("Particle Effects/LauncherSpark.psi",GunSparkSprite);	break;
	case FEATHER_RED:   temp = new hgeParticleSystem("Particle Effects/red feathers.psi",FeatherSprite);     	break;
	case FEATHER_BLUE:  temp = new hgeParticleSystem("Particle Effects/blue feathers.psi",FeatherSprite);		break;
	case FEATHER_GREEN:  temp = new hgeParticleSystem("Particle Effects/green feathers.psi",FeatherSprite);						break;
	case FEATHER_PURPLE:  temp = new hgeParticleSystem("Particle Effects/purple feathers.psi",FeatherSprite);						break;

	} // end of switch


	if(id != JUMP_DUST){ temp->info.fDirection = (direction == 1)? (4.5f): (-4.5f); }
	else temp->info.fDirection = (direction == 1)? (5.5f): (-5.5f);
		
	temp->FireAt(x,y);
	return temp;
}

void ManageParticleList(vector<hgeParticleSystem*> &ParticleList)
{
	for (unsigned int i = 0 ; i < ParticleList.size() ; i++)
	{
		if (ParticleList[i]->GetParticlesAlive() <= 0 )
		{
			ParticleList.erase( ParticleList.begin() + i );
		}
	}
}

Timer Create(1000);

void AddLeaf(vector<Leaf> &Leaves)
{
	Leaf temp;

	temp.spr = new hgeSprite(hLeafTex,0,0,17,17);

	switch (rand()%3)
	{
	case 0: temp.scale = 0.5f;
		temp.spr->SetColor(ARGB(255,220,150,20));
		temp.vel.x = 1.5f;
		break;
	case 1: temp.scale = 0.8f;
		temp.spr->SetZ(0.5);
		temp.spr->SetColor(ARGB(255,220,100,0));
		temp.vel.x = 1.1f;
		break;
	case 2: temp.scale = 1.0f;
		temp.vel.x = 0.9f;
		break;
	}

	temp.pos.x = ((rand()+1) %20)*2 + 1500 + (rand()+1)%350;
	temp.pos.y = rand()%500 + 200;
	temp.dir.x = tan(-1.2f);
	temp.dir.y = cos(-1.2f);

	temp.vel.y = 1.0f;
	temp.rotate = 1.0f;

	if(Create.TimerEnd())
	Leaves.push_back(temp);
}


void UpdateLeaves(vector<Leaf> &Leaves)
{
	if (Leaves.size() < 28)
	{
		AddLeaf(Leaves);
	}

	for (unsigned int i = 0; i < Leaves.size(); i++ )
	{
		Leaves[i].rotate += 0.02f;
		if (Leaves[i].pos.x > 0 && Leaves[i].pos.y < 768)
		{
			Leaves[i].pos.x += Leaves[i].vel.x * Leaves[i].dir.x;
			Leaves[i].pos.y += Leaves[i].vel.y * Leaves[i].dir.y;
		}
		else
		{
			delete Leaves[i].spr;
			Leaves.erase( Leaves.begin() + i );
		}
	}
}

void RenderLeaves(vector<Leaf> &Leaves)
{
	for (unsigned int i = 0; i < Leaves.size(); i++)
	{
			Leaves[i].spr->RenderEx(Leaves[i].pos.x,Leaves[i].pos.y,Leaves[i].rotate,Leaves[i].scale,Leaves[i].scale);
	}
}

////////////////////////////////// CLOUDS ////////////////////////////////////////////////////////////////////////

void AddCloud(vector<Cloud> &Clouds)
{
	Cloud temp;
	temp.spr = new hgeSprite(cloud,0,0,230,127);
	
	switch (rand()%3)
	{
	case 0: temp.scale = 0.5f;
		temp.id = 0;
		temp.fSpeedX = 12.5f;
		break;
	case 1: temp.scale = 0.75f;
		temp.id = 1;
		temp.fSpeedX = 20.8f;
		break;
	case 2: temp.scale = 1.0f;
		temp.id = 2;
		temp.spr->SetFlip(true,0);
		temp.fSpeedX = 15.0f;
		break;
	}

	temp.pos.x =  1366;//1400; + ( (rand()+1)%501 ) ;
	temp.pos.y = rand()%200;

	Clouds.push_back(temp);


}

Timer CreateCloud(2500);

void UpdateCloud(vector<Cloud> &Clouds, float dt)
{

	if (Clouds.size() < 4)
	{
		if( CreateCloud.TimerEnd() )
		AddCloud(Clouds);
	}

		for (unsigned int i = 0; i < Clouds.size(); ++i )
		{
			
			if (Clouds[i].pos.x > -300)
			{
				Clouds[i].pos.x += Clouds[i].fSpeedX * dt * -1;

			}
			else
			{
				delete Clouds[i].spr;
				Clouds.erase(Clouds.begin() + i);

			}
		}
}


void RenderCloud(vector<Cloud> &Clouds)
{
	for (unsigned int i = 0; i < Clouds.size(); ++i)
	{
		Clouds[i].spr->RenderEx(Clouds[i].pos.x, Clouds[i].pos.y, 0 , Clouds[i].scale, Clouds[i].scale );

	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateEffect( Protagonist* Aztec,std::vector< hgeParticleSystem* > &ParticleList, eParticles id ,Enemy* enm )
{
	float x = Aztec->vPosition.x +40.0f;
	float y = Aztec->GetDownFace()-5.0f;	
	float fDir=0.0f;
	
	if( id == JUMP_DUST ){	
	ParticleList.push_back( ParticleFactory(id ,x,y,1) );
	ParticleList.push_back( ParticleFactory(id ,x+40.0f,y,-1) );
	}
	if( id == HIT_BLOOD && enm != NULL ) 
	{
	  x = ( enm->GetFacing() == FACERIGHT )?( enm->vPosition.x + 52 ):( enm->GetRightFace() - 52 );
	  y = enm->vPosition.y + 50;	
	  fDir = 1.0f;
	  ParticleList.push_back( ParticleFactory(id ,x,y,-1.0f) );
	  ParticleList.push_back( ParticleFactory(id ,x,y+5.0f,-0.5f) );
	  ParticleList.push_back( ParticleFactory(id ,x,y+20.0f, 0.5f) ); 		
	}
	
	ParticleList.push_back( ParticleFactory(id ,x,y,fDir) );	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateEffect( Bullet* bul, std::vector< hgeParticleSystem* > &ParticleList )
{
	float x = bul->vPosition.x;
	float y = bul->vPosition.y;
	float fDirection = 0.0f; 
	

	if(bul->vDirection.x == -1.0f)
	{
		x += bul->GetWidth();//+5.0f;	
		fDirection = -1.0f;
	}
	else 
	{
		//x -= 5.0f;
		fDirection = 1.0f;
	}
	
	switch( bul->GetId() ) 
	{
	case SHOTGUN_BULLET:	ParticleList.push_back( ParticleFactory(HIT_FIRE,x,y,fDirection) ); break;
	case ENEMYBULLET_TYPE2:	ParticleList.push_back( ParticleFactory(HIT_FIRE_GREEN,x,y,fDirection) ); break;
	case ENEMYBULLET_TYPE3:	ParticleList.push_back( ParticleFactory(HIT_FIRE_BLUE,x,y,fDirection) ); break;
	case ENEMYBULLET_TYPE4:	ParticleList.push_back( ParticleFactory(HIT_FIRE_RED,x,y,fDirection) ); break;
	}

	ParticleList.push_back( ParticleFactory(HIT_BLOOD,x,y,fDirection) );
	ParticleList.push_back( ParticleFactory(HIT_BLOOD,x,y+10,fDirection+0.5f) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateEffect(Bullet* bul, LevelObjects &Box, std::vector< hgeParticleSystem* > &ParticleList)
{
	float x = bul->vPosition.x;
	float y = bul->vPosition.y;

	eParticles ID = BLACK_SMOKE; 
	eBULLETID eBulletId = bul->GetId();
	int  iBoxId = Box.GetId(); 
	float fDirection = 0.0f; 

	if( Box.IsDead() )  // show smoke
	{
		x = Box.GetLeftFace() + ( Box.GetRightFace()- Box.GetLeftFace() ) / 2.0f ;
		y = Box.GetUpFace()   + ( Box.GetDownFace() - Box.GetUpFace()  ) / 2.0f ;	
		switch ( iBoxId )
		{
			case 1: ID = BROWN_SMOKE;  break;
			case 2: ID = BROWN_SMOKE;  break;
			case 3: ID = GREY_SMOKE;   break;
			case 4:	ID = GREY_SMOKE;   break;
			case 5: ID = BLACK_SMOKE;  break;
			case 6:	ID = BLACK_SMOKE; 
		}		
	}
	else  // show spark
	{
		if(bul->vDirection.x == 1.0f)
		{
			x += bul->GetWidth()+5.0f;	
			fDirection = 1.0f;
		}
		else
		{
			x -= 5.0f;
			fDirection = -1.0f;
		}
		switch( eBulletId )
		{
		  case ENEMYBULLET_TYPE1:
		  case ASSAULTRIFLE_BULLET: 
		  case SEMIAUTO_BULLET:	  ID = HIT_EFFECT; 
							                       break;
		  case SHOTGUN_BULLET:	    ID = HIT_FIRE; break;
		  case ENEMYBULLET_TYPE2:	ID = HIT_FIRE_GREEN; break;
		  case ENEMYBULLET_TYPE3:	ID = HIT_FIRE_BLUE; break;
		  case ENEMYBULLET_TYPE4:	ID = HIT_FIRE_RED; break;
		}
	}
	
	ParticleList.push_back( ParticleFactory(ID,x,y,fDirection) ); // create and push the particle in to the list
}

///////////////////////////////////////////////////////////Birds//////////////////////////////////////////////////////////////
void AddBird(std::vector<Bird> &Birds, int type)
{
	Bird temp;
	temp.iHealth = 1;
	temp.anim = 0;
	temp.falling = 0;
	switch (type)
	{
	case 0 : temp.eId = RED;
		temp.anim = new hgeAnimation(texBirds, 2, 10, 0, 0, 55, 58);
		temp.falling = new hgeAnimation(Fallingtex,4,8,0,0,50,50);
		temp.falling->SetZ(0.5f);
		temp.Velocity.x = 7.6f;
		temp.Velocity.y = .15f;
		temp.Position.x =1366.0f + rand()%300;
		temp.Position.y = rand()%70;
		temp.Direction = -1;
		temp.anim->Play();
		Birds.push_back(temp);
		break;
	case 1 : temp.eId = BY;
		
		temp.anim = new hgeAnimation(texBirds, 2, 10, 0, 62, 64, 70);
		temp.falling = new hgeAnimation(Fallingtex,4,8,0,210,70,70);
		temp.falling->SetZ(0.5f);
		temp.Velocity.x = 7.9f;
		temp.Velocity.y = .1f;
		temp.Position.x =1366 + rand()%100;
		temp.Position.y = rand()%150;
		temp.Direction = -1;
		temp.anim->Play();
		Birds.push_back(temp);
		break;
	case 2 : temp.eId = GREEN;	
		
		temp.anim = new hgeAnimation(texBirds, 2, 13, 0, 137, 40, 30);
		temp.falling = new hgeAnimation(Fallingtex,4,7,0,165,50,30);
		temp.falling->SetZ(0.5f);
		temp.Velocity.x = 8.4f;
		temp.Velocity.y = .1f;
		temp.Position.x = 1366 + rand()%300;
		temp.Position.y = rand()%50;
		temp.Direction = -1;
		temp.anim->Play();
		Birds.push_back(temp);
		break;
	case 3 : temp.eId = PURPLE;
		temp.anim = new hgeAnimation(texBirds, 2, 13, 88, 132, 42, 30);
		temp.falling = new hgeAnimation(Fallingtex,4,7,0,50,50,50);
		temp.falling->SetZ(0.5f);
		temp.Velocity.x = 8.6f;
		temp.Velocity.y = .1f;
		temp.Position.x =1366 + rand()%300;
		temp.Position.y = rand()%50;
		temp.Direction = -1;
		temp.anim->Play();
		Birds.push_back(temp);
		break;
	case 4 : temp.eId = BLUE;
		temp.anim = new hgeAnimation(texBirds, 2, 9, 0, 175, 60, 60);
		temp.falling = new hgeAnimation(Fallingtex,4,8,0,100,60,60);
		temp.falling->SetZ(0.5f);
		temp.Velocity.x = 7.75f;
		temp.Velocity.y = .1f;
		temp.Position.x =1366 + rand()%300;
		temp.Position.y = rand()%100;
		temp.Direction = -1;
		temp.anim->SetFlip(true,false);
		temp.anim->Play();
		Birds.push_back(temp);
		break;
	default:
		break;
	}

}

void checkbirdbulletcollision(std::vector< Bullet* > vInGameBullets,Bird &Birds)
{
	

		for (unsigned int j = 0; j < vInGameBullets.size(); j++)
		{
			if ( Birds.IsDead() && !vInGameBullets[j]->IsDead() ) 
				if ( vInGameBullets[j]->GetRightFace() > (Birds.GetLeftFace()) && vInGameBullets[j]->GetLeftFace() < (Birds.GetRightFace()) )   // for X axis
				{ 
					if ( vInGameBullets[j]->GetUpFace() < Birds.GetDownFace()   && vInGameBullets[j]->GetDownFace() > Birds.GetUpFace() )	      // for Y axis
					{	
						hgeParticleSystem* temp = ParticleFactory(HIT_BLOOD, vInGameBullets[j]->GetLeftFace(),vInGameBullets[j]->GetDownFace() + 10, 1);
						temp->info.fParticleLifeMax = 0.9f;
						ParticleList.push_back(temp);
						ParticleList.push_back(ParticleFactory(HIT_BLOOD, vInGameBullets[j]->GetLeftFace(),vInGameBullets[j]->GetDownFace() + 10, 1));
						ParticleList.push_back(ParticleFactory(HIT_BLOOD, vInGameBullets[j]->GetLeftFace() + 15,vInGameBullets[j]->GetDownFace() - 5, 1));
						switch (Birds.eId)
						{
							
						case RED: ParticleList.push_back(ParticleFactory(FEATHER_RED,vInGameBullets[j]->GetLeftFace()  - 10,vInGameBullets[j]->GetUpFace() - 10,1));
							ParticleList.push_back(ParticleFactory(FEATHER_RED,vInGameBullets[j]->GetLeftFace() + 10,vInGameBullets[j]->GetDownFace() + 20,1));
							break;
						case BLUE: ParticleList.push_back(ParticleFactory(FEATHER_BLUE,vInGameBullets[j]->GetLeftFace()  - 10,vInGameBullets[j]->GetUpFace() - 10,1));
									ParticleList.push_back(ParticleFactory(FEATHER_BLUE,vInGameBullets[j]->GetLeftFace()  +20,vInGameBullets[j]->GetUpFace() + 10,1));
									break;						
						case GREEN: ParticleList.push_back(ParticleFactory(FEATHER_GREEN,vInGameBullets[j]->GetLeftFace()  - 10,vInGameBullets[j]->GetUpFace() - 10,1));
							ParticleList.push_back(ParticleFactory(FEATHER_GREEN,vInGameBullets[j]->GetLeftFace()  + 20,vInGameBullets[j]->GetUpFace() + 10,1));
							break;
						case PURPLE: ParticleList.push_back(ParticleFactory(FEATHER_PURPLE,vInGameBullets[j]->GetLeftFace()  - 10,vInGameBullets[j]->GetUpFace() - 10,1));
							ParticleList.push_back(ParticleFactory(FEATHER_PURPLE,vInGameBullets[j]->GetLeftFace()  + 20,vInGameBullets[j]->GetUpFace() + 10,1));
							
							break;
						}
						
						AddScore(hgeVector(Birds.GetLeftFace(),Birds.GetDownFace()),"+20",BIRD_KILL);
						SoundEffectsList.push_back( PlaySoundEffect(HIT_FLESH_HUMAN) );
						vInGameBullets[j]->Die();
						Birds.die();
						Birds.anim->Stop();
						Birds.falling->Play();
						Birds.Velocity.y = -3.3f;
						
					}
				}
				
		}
	

}

void UpdateBirds(std::vector<Bird> &Birds, float dt)
{

	if (BirdTimer.TimerEnd())
	{
		int iBirds = (int)Birds.size();
		int iType = rand()%5;

		for (unsigned int i = iBirds; i < 3 + rand()%3; i++)
		{
			AddBird(Birds,iType);
		}


	}
	

	for (unsigned int i =0; i < Birds.size(); i++)
	{
		if ( Birds[i].Position.x < -200 )
		{
			bPlaySound = false;
			delete Birds[i].anim;
			delete Birds[i].falling;
			Birds.erase(Birds.begin() + i);
			continue;

		}
		
	
		checkbirdbulletcollision(vInGameBullets,Birds[i]);
		
		

		
		if (Birds[i].IsDead())
		{
			Birds[i].anim->Update(dt);	
			
		}
		else
		{
			if (Birds[i].Velocity.x > 1.5f)
			{
				Birds[i].Velocity.x -= 0.01f;
				Birds[i].Velocity.y -= 0.06f;
			}
			
			Birds[i].falling->Update(dt);
			
		}
		
			Birds[i].Position.x += Birds[i].Velocity.x * Birds[i].Direction;
			Birds[i].Position.y += Birds[i].Velocity.y * Birds[i].Direction;
		
		
		if ( Birds[i].Position.x < 1000 &&  Birds[i].Position.x > 995 )
		{
			bPlaySound = true;

			if ( Birds[i].Position.x > - 200 && bPlaySound)
			{
				bPlaySound = false;
				if (Birds[i].eId == RED || Birds[i].eId == BY || Birds[i].eId == BLUE )
				{
					SoundEffectsList.push_back(PlaySoundEffect(BIRD_CHIRRUP2));
				}
				else
					SoundEffectsList.push_back(PlaySoundEffect(BIRD_CHIRRUP1));
			}


		}

	}


}
void RenderBirds(std::vector<Bird> Birds)
{
	for (unsigned int i =0; i < Birds.size(); i++)
	{
		if (Birds[i].IsDead())
		{
			Birds[i].anim->Render(Birds[i].Position.x, Birds[i].Position.y );
		}
		else
			Birds[i].falling->Render( Birds[i].Position.x, Birds[i].Position.y);
		
				
	}
}

void AddScore(hgeVector _position, char* _score, enum eScores tempscore)
{
	ScoreUp temp;
	temp.score = _score;
	temp.font_score = new hgeFont("Fonts/font.fnt");
	temp.position = _position;
	temp.show = true;
	temp.fade = 255;
	temp.font_score->SetBlendMode(BLEND_ALPHABLEND);
	
	switch(tempscore)
	{
	case HUMAN_KILL: Total_kills += 1; Total_Score += 10; 
		break;
	case ALIEN1_KILLS: Total_kills += 1; Total_Score += 10;
		break;
	case ALIEN2_KILLS: Total_kills += 1; Total_Score += 20;
		break;
	case ALIEN3_KILLS: Total_kills += 1; Total_Score += 15;
		break;
	case BULLET1_SUSTAINED: hits_sustained += 1; Total_Score -= 5;
		break;
	case BULLET2_SUSTAINED: hits_sustained += 1; Total_Score -= 5;
		break;
	case BULLET3_SUSTAINED: hits_sustained += 1; Total_Score -= 10;
		break;
	case BULLET4_SUSTAINED: hits_sustained += 1; Total_Score -= 10;
		break;
	case BOX_MELEES: Box_destroyed += 1; Total_Score += 20;
		break;
	case ENEMY_MELEES: Melees +=1; Total_Score += 20;
		break;
	case BULLETS_WASTED: Bullets_Wasted += 1; Total_Score -= 2;
		break;
	case BIRD_KILL: Birds_killed += 1; Total_Score += 20;
	}
	vScores.push_back(temp);

}

void UpdateScores(vector<ScoreUp> &vScores)
{
	for (unsigned int i = 0; i < vScores.size(); i++ )
	{
		if (vScores[i].fade > 0)
		{
			vScores[i].position.y -= 1.5f;
			vScores[i].fade -= 2.3f;
			vScores[i].font_score->SetColor(ARGB(vScores[i].fade,225,0,0));
		}
			
		else
		{
			 delete vScores[i].font_score;
			 vScores[i].show = false;
			vScores.erase(vScores.begin() + i);
		}
	}
}

void RenderScores()
{
	for (unsigned int i = 0; i < vScores.size(); i++ )
	{
		if (vScores[i].show)
		{
			vScores[i].font_score->printf(vScores[i].position.x,vScores[i].position.y,0,vScores[i].score);
			
		}
	}
}



void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList)
{
	ePLAYER_STANCE STANCE_AZTEC = Aztec->GetStance();
	ePLAYER_STANCE FACING_AZTEC = Aztec->GetFacing();
	//Bullet Spark Effect

	if ( PLAYERSTATUS == ON_THE_GROUND )
	{
		if ( STANCE_AZTEC == IDLE  && FACING_AZTEC == FACERIGHT)
		{
			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,-1));
		}
		else if (STANCE_AZTEC == RUNNING  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,1));

		}
		else if (STANCE_AZTEC == DUCK  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 78,-1));
		}
		else if (STANCE_AZTEC == LOWMOVE  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,-1));
		}

		else if (STANCE_AZTEC == DUCK  && FACING_AZTEC == FACELEFT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 15, Aztec->vPosition.y + 78,1));
		}

		else if ( STANCE_AZTEC == IDLE  && FACING_AZTEC == FACELEFT )
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 15, Aztec->vPosition.y + 48,1));
		}

		else if (STANCE_AZTEC == RUNNING && FACING_AZTEC == FACELEFT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 15, Aztec->vPosition.y + 48,-1));
		}
	}
	else if (PLAYERSTATUS == ON_THE_OBJECT)
	{
		if ( STANCE_AZTEC == IDLE  && FACING_AZTEC == FACERIGHT)
		{


			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,-1));
		}
		else if (STANCE_AZTEC == RUNNING  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,1));

		}
		else if (STANCE_AZTEC == DUCK  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 78, -1));
		}
		else if (STANCE_AZTEC == LOWMOVE  && FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 78,1));
		}

		else if (STANCE_AZTEC == DUCK  && FACING_AZTEC == FACELEFT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 78, -1));
		}

		else if ( STANCE_AZTEC == IDLE  && FACING_AZTEC == FACELEFT )
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48, -1));
		}

		else if (STANCE_AZTEC == RUNNING && FACING_AZTEC == FACELEFT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 98, Aztec->vPosition.y + 48,1));
		}
	}
	else 
	{
		if (FACING_AZTEC == FACERIGHT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 96, Aztec->vPosition.y + 44,1));
		}

		else if (FACING_AZTEC == FACELEFT)
		{

			ParticleList.push_back(ParticleFactory(GUN_SPARK,Aztec->vPosition.x + 15, Aztec->vPosition.y + 44,1));
		}


	}

}



