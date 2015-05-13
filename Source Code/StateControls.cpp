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



#include "StateControls.h"
#include <vector>
#include "sounds.h"
#include <hgesprite.h>
#include <hgeparticle.h>
#include "MusicPlayer.h"
using namespace::std;

enum eParticles { BLACK_SMOKE, BROWN_SMOKE, GREY_SMOKE, HIT_EFFECT, HIT_BLOOD, HIT_FIRE, JUMP_DUST, LAUNCHER_TRAIL, GUN_SPARK, BLAST,GRENADE_BLAST};
hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int direction);
void ProcessSound(vector <SoundInfo> &SoundEffectsList);	
void ShowGunSpark(Protagonist* azControl, vector<hgeParticleSystem*> &ParticleList);
void ManageParticleList(vector<hgeParticleSystem*> &ParticleList);
//Extern Data
extern GameStateManager *Manager ;
extern HGE *Engine;
extern CONDITION PLAYERSTATUS;
extern vector <SoundInfo> SoundEffectsList;
extern vector<hgeParticleSystem*> ParticleList;
extern hgeSprite *GunSparkSprite;
extern HTEXTURE GunSparkTex;
float GROUNDC ;  // the height of ground 
float GRAVITYC ;
static float EscapeVelocityC;
HTEXTURE tex;
hgeSprite *spr;
Protagonist *azControl = 0;
namespace{MusicPlayer *PlayMusicNow;}

StateControls::StateControls(void)
{
}

StateControls::~StateControls(void)
{
}


bool StateControls::Init()
{
	GROUNDC = 465;
	GRAVITYC = 0.20f;
	EscapeVelocityC = 0.0f;
	azControl = new Protagonist;
	azControl->vPosition.x = 1000;
	azControl->vPosition.y = 320;
	azControl->Init(Engine);
	tex = Engine->Texture_Load("sprites/controls.png");
	GunSparkTex = Engine->Texture_Load("Particle Effects/particles.png");
	GunSparkSprite = new hgeSprite(GunSparkTex,64,64,32,32);
	GunSparkSprite->SetBlendMode(BLEND_ALPHAADD );
	spr = new hgeSprite(tex,0,0,1366,768);
	MusicPlayer* LoadMusicPlayer(int i);
	PlayMusicNow = LoadMusicPlayer(1);
	PlayMusicNow->PlayTrack(2,true);

	return true;
}

bool StateControls::Update(float dt)
{
	if (Engine->Input_KeyDown(HGEK_ESCAPE))
	{
		Manager->SetState(STATE_MENU);
		return false;
	}
//////////////////////PLAYER UPDATE
	azControl->Update(Engine,dt);

////////WEAPON SELECTION
	if( Engine->Input_GetKey() == HGEK_1 )  {azControl->SelectAssaultRifle();  SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON)); } 
	if( Engine->Input_GetKey() == HGEK_2 )	{azControl->SelectSideArm(); SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON)); }
	if( Engine->Input_GetKey() == HGEK_3 )  {azControl->SelectShotGun(); SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON)); }
	if( Engine->Input_GetKey() == HGEK_4 )  {azControl->SelectRocketLauncher(); SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON)); }
//////////////////////FIRE WEAPON
	if( Engine->Input_GetKeyState(HGEK_SPACE) )   /// FIRE WEAPON
	{   

		if( azControl->FireWeapon() )
		{
			if( !azControl->pCurrentWeapon->IsEmpty() )
			{
				
				ShowGunSpark( azControl, ParticleList);
				eSOUNDEFFECTS PlayEffect=NULL_SOUND;
				switch( azControl->pCurrentWeapon->GetWeaponID() )
				{
				case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
				case SEMIAUTO:       PlayEffect=FIRE_PISTOL; break;
				case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN; break;	
				case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER; break;
				}
				SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
			}
			else
				SoundEffectsList.push_back(PlaySoundEffect(WEAPON_EMPTY));

		} // end of if block that is operated around the fire call

	}

///////////////JUMP
	ePLAYER_STANCE AztecStance = azControl->GetStance();
	if( AztecStance != JUMPING && Engine->Input_GetKeyState(HGEK_UP) )
	{
		EscapeVelocityC = -6.6f;
		PLAYERSTATUS = IN_THE_AIR;
		azControl->vPosition.y += EscapeVelocityC;
		azControl->ChangeStance(JUMPING);
		SoundEffectsList.push_back(PlaySoundEffect(PLAYER_JUMP));

	}	

	else if( PLAYERSTATUS == IN_THE_AIR )	// Freely Suspended Player Under The Action Of Gravity
	{
		azControl->vPosition.y+=EscapeVelocityC;
		EscapeVelocityC += GRAVITYC;        

		if( azControl->GetDownFace()+3.0f >= GROUNDC-5.0f && EscapeVelocityC > 0  )
		{
			PLAYERSTATUS = ON_THE_GROUND;
			azControl->ChangeStance(IDLE);	
			
			
			SoundEffectsList.push_back(PlaySoundEffect(PLAYER_HITS_GROUND));
		}

	}

	/////////////////////////////PARTICLE EFFECTS
	for (unsigned  int i=0; i<ParticleList.size(); i++ )
	{
		  ParticleList[i]->Update(dt);
	}
	ManageParticleList(ParticleList);	
	ProcessSound(SoundEffectsList);	
		
	return false;
}

bool StateControls::Render()
{
	spr->Render(0,0);
	azControl->Render();
	for (unsigned int i = 0 ; i < ParticleList.size(); i++ )
	{
		if (ParticleList[i])
		{
			ParticleList[i]->Render();
		}
	}	
	return true;
}


bool StateControls::Release()
{
	azControl->Release(Engine);
	delete azControl;
	azControl = 0;
	delete spr; spr = 0;
	Engine->Texture_Free(tex);
	
	PlayMusicNow->Stop();
	delete PlayMusicNow;

	return true;
}