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





#include <hge.h>
#include "GameStateManager.h"
#include <hgevector.h>
#include "sprite.h"
#include "Timer.h"
#include <hgeparticle.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <hgeanim.h>
#include "TileMap.h"
#include "LevelObjects.h"
#include <vector>
#include "dialog.h"
#include <irrKlang.h>



using namespace irrklang;
HGE *Engine = NULL;
ISoundEngine* sound_engine = createIrrKlangDevice();
GameStateManager *Manager = NULL;
float dt;

float elapsed = 0;
/////////////////////Variables for Score and Stats
int Total_Score,Total_kills;
int Birds_killed, hits_sustained, Box_destroyed,Melees, Bullets_Wasted,Kills_row,Melees_row;
//////////////////////////////////////////////////


bool Update()
{
	dt = Engine->Timer_GetDelta();
	return Manager->Update(dt);
}


bool Render()
{	
	Engine->Gfx_BeginScene();
	Engine->Gfx_Clear(ARGB(255,0,0,0));

	Manager->Render();

	Engine->Gfx_EndScene();
	return false;
}


void ReleaseEffects(HGE* Engine);
void LoadEffects(HGE* Engine);

bool FocusGain()
{
		sound_engine->setAllSoundsPaused(false);
		Engine->Channel_ResumeAll();
		return false;
}

bool FocusLost()
{
		sound_engine->setAllSoundsPaused(true);
		Engine->Channel_PauseAll();
		return false;
}

void Init()
{	
	Manager = new GameStateManager;
	Manager->Init();
	LoadEffects(Engine);
    LoadVoices(Engine);

	extern int THIS_IS_LEVEL_NUMBER;
	extern bool bGameIsInTheFinalStage;
	Manager -> SetState( STATE_INTRO );
	//Manager -> SetState( STATE_LEVEL2 );
}

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	Engine = hgeCreate(HGE_VERSION);
	Engine->System_SetState(HGE_SHOWSPLASH,true);
	Engine->System_SetState(HGE_RENDERFUNC,Render);
	Engine->System_SetState(HGE_FRAMEFUNC,Update);
	Engine->System_SetState(HGE_FOCUSLOSTFUNC,FocusLost);
	Engine->System_SetState(HGE_FOCUSGAINFUNC,FocusGain);
	Engine->System_SetState(HGE_WINDOWED,true);
	Engine->System_SetState(HGE_SCREENWIDTH, 1366 );
	Engine->System_SetState( HGE_SCREENHEIGHT, 768 );
	Engine->System_SetState( HGE_USESOUND, true );
	Engine->System_SetState(HGE_FPS,HGEFPS_VSYNC);

	if (Engine->System_Initiate())
	{	
		Init();
		Engine->System_Start();
	}	
	else
	{
		MessageBox(0,"loading fail ","Error",MB_OKCANCEL);
	}
	
	ReleaseVoices(Engine);
	ReleaseEffects(Engine);
    Manager->Release();
	Engine->System_Shutdown();
	Engine->Release();
	sound_engine->drop();
	return 0;
}