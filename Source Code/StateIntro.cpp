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





#include "StateIntro.h"
#include "MusicPlayer.h"
#include "Timer.h"

#define SCREENWIDTH 1366
#define SCREENHEIGHT 768

extern HGE *Engine;
extern GameStateManager *Manager;
hgeDistortionMesh *DistortMesh;
extern ISoundEngine* sound_engine;
//Textures
HTEXTURE intro;
HTEXTURE gm ;
HTEXTURE ed,matureTex; 

HEFFECT test;


hgeSprite *i, *matureSpr ;
hgeSprite *g;
hgeSprite *e;
float fScaleX;
float fScaleY;
float fScaleX1;
float fScaleY1;
float fScaleY2;
float fScaleX2;
float fAlpha2;
float fAlpha1;
float fAlpha3;
bool bShowName;
bool bShowgm;
bool bShowED;
MusicPlayer *SEffects;
float t;
StateIntro::StateIntro(void)
{
}

StateIntro::~StateIntro(void)
{
}


float timer;

bool StateIntro::Init()
{
	DistortMesh = 0;
	bShowName = false;
	bShowgm = false;
	bShowED = true;
	t = 0.0f;
	//Load Textures
	intro = Engine->Texture_Load("Textures/Intro/Intro.png");
	gm = Engine->Texture_Load("Textures/Intro/gmp.png");
	ed = Engine->Texture_Load("Textures/Intro/edu.png");
	matureTex = Engine->Texture_Load("Textures/Intro/mature.png");

	//Initialize Distortion mesh
	DistortMesh = new hgeDistortionMesh(16,16);
	DistortMesh->SetTexture(gm);
	DistortMesh->SetTextureRect(0,0,491,154);
	DistortMesh->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_ZWRITE);
	DistortMesh->Clear(0xFF000000);
	static char* play[]={ "sound/items/introGm.mp3","sound/items/maximum_game.mp2"};
	SEffects=new MusicPlayer(sound_engine,play,2);
		
	//Initialize Sprites
	i = new hgeSprite(intro,0,0,276,71);
	i->SetHotSpot(i->GetWidth()/2,i->GetHeight()/2);	
	
	g = new hgeSprite(gm,0,0,491,154); 

	g->SetHotSpot(g->GetWidth()/2, g->GetHeight()/2);
	
	e = new hgeSprite(ed,0,0,510,58);  e->SetHotSpot(e->GetWidth()/2,e->GetHeight()/2);
	
	matureSpr = new hgeSprite(matureTex,0,0,300,179);
	matureSpr->SetHotSpot(matureSpr->GetWidth()/2,matureSpr->GetHeight()/2);
	//Scale and Alpha Variables
	fScaleX = 1;
	fScaleY = 1;
	fScaleX1 = 1;
	fScaleY1 = 1;
	fScaleX2 = 1;
	fScaleY2 = 1;
	fAlpha1 = 175;
	fAlpha2 = 255;
	fAlpha3 = 255;

	//Engine->Effect_Play(test);
	return true;
}


bool StateIntro::Render()
{
	if (bShowED)
	{
		e->SetColor(ARGB(fAlpha3,255,255,255));
		matureSpr->SetColor(ARGB(fAlpha3,255,255,255));

		matureSpr->Render(SCREENWIDTH/2,SCREENHEIGHT/2);
		e->RenderEx(SCREENWIDTH/2,275, 0, 0.6,0.6);
	}
	if (bShowgm)
	{
		for( int i = 1; i < 15; i++ )
			for( int j = 1; j < 15; j++ )
			{	DistortMesh->SetColor(i,j,ARGB(fAlpha2,0,0,0));		}
			t += .01f;
		DistortMesh->Render( ( SCREENWIDTH/2 ) - ( g->GetWidth()/2 ), (SCREENHEIGHT/2) - (g->GetHeight()/2) );  //(SCREENWIDTH/2,SCREENHEIGHT/2);
	}
	else if (bShowName)
	{
		i->SetColor(ARGB(fAlpha1,255,255,255));
		i->RenderEx(SCREENWIDTH/2,SCREENHEIGHT/2,0,fScaleX1,fScaleY1);
	}
	
	return false;
}

bool StateIntro::Release()
{
	delete i; i = 0;
	delete g; g = 0;
	delete e; e = 0;
	delete DistortMesh; DistortMesh = 0;
	
	SEffects->Stop();
	delete SEffects;

	Engine->Texture_Free(ed);
	Engine->Texture_Free(gm);
	Engine->Texture_Free(intro);
	return true;
}



Timer TimeFreeze(5000),Gap(500);
bool PlaySoundFlagIntro = false;
int SelectCase = 1;


bool StateIntro::Update(float dt)
{

	if (Engine->Input_GetKeyState(HGEK_ESCAPE))
	{
		Manager->SetState( STATE_MENU ); return false;
	}
	
	if( TimeFreeze.TimeOver() )
	{
		 
		++SelectCase;
		if(SelectCase == 3) PlaySoundFlagIntro=false;
		TimeFreeze.setstart();
	}

	switch(SelectCase)
	{
	case 1:  
			bShowED = true;  bShowName = bShowgm = false;
			break;
	case 2:
			bShowgm = true; bShowED = bShowName = false;
			SEffects->PlayList();
			if(!PlaySoundFlagIntro)
			{ 
				PlaySoundFlagIntro=true; SEffects->PlayTrack(0);  TimeFreeze.setEndTime(6500); TimeFreeze.setstart(); 
			}
			if ( TimeFreeze.GetTime() > 2200 && TimeFreeze.GetTime() < 3600 )
			{
				for( int i = 1; i < 15; i++ )
					for( int j = 1; j < 15; j++ )
					{
						int col = 0;
						DistortMesh->SetDisplacement(j,i,cosf(t*5+j/2)*2,0,HGEDISP_NODE);
					}
					t += .15f;
			}

			break;
	case 3:
  		  bShowName = true;  bShowED = bShowgm = false; 
		  if(!PlaySoundFlagIntro) { SEffects->Play("sound/items/TheSiege.mp3"); PlaySoundFlagIntro=true; }
		  break;
	
	default:   if(SEffects->IsFinished());
				Manager->SetState( STATE_MENU ); return false;
	}

		
 return false;
}
