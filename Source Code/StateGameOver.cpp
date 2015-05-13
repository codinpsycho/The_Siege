#include "StateGameOver.h"
#include "GameStateManager.h"
#include <hge.h>
#include "Button.h"
#include <hgesprite.h>
#include <hgefont.h>


extern HGE *Engine;
extern GameStateManager *Manager;
extern hgeFont *font;
hgeSprite *back;
extern int Total_Score,Total_kills;				//Variables for Scoring and stats
extern int Birds_killed, hits_sustained, Box_destroyed,Melees, Bullets_Wasted; //

extern HTEXTURE cur;
HTEXTURE backtex ;
HTEXTURE quit;
HTEXTURE cont;
HEFFECT govermusic;

StateGameOver::StateGameOver(void)
{
}

StateGameOver::~StateGameOver(void)
{
}


bool StateGameOver::Init()
{
	//Init GUI
	GUI = new hgeGUI();
	//Loads Textures
	cur = Engine->Texture_Load("Textures/Game Over/cur1.png");
	backtex = Engine->Texture_Load("Textures/Game Over/gameover.png");
	quit = Engine->Texture_Load("Textures/Game Over/quit.png");
	cont = Engine->Texture_Load("Textures/Game Over/continue.png");

	back = new hgeSprite(backtex,0,0,1366,768);

	govermusic = Engine->Effect_Load("sound/music/gameover.ogg");
	Engine->Effect_PlayEx(govermusic,100,0,1,true);
	//Sets Cursor
	cursor = new hgeSprite(cur,0,0,32,32);
	cursor->SetTexture(backtex);
	cursor->SetTexture(cur);
	GUI->SetCursor(cursor);

	GUI->AddCtrl(new Button(1,100,670,quit,quit,quit));
	GUI->AddCtrl(new Button(2,100,710,cont,cont,cont));

	GUI->SetNavMode(HGEGUI_CYCLED | HGEGUI_UPDOWN);
	font = new hgeFont("Fonts/font.fnt");	//Init Font
	
		



	return true;
}

extern int THIS_IS_LEVEL_NUMBER;
extern bool bGameIsInTheFinalStage;
bool bLOAD_END=false;

bool StateGameOver::Update(float dt)
{
	int id = GUI->Update(dt);
	
	if (id == 1)
	{
		if( THIS_IS_LEVEL_NUMBER == 1)
		{
			Manager->SetState(STATE_LEVEL1);
		}
		else 
		if( THIS_IS_LEVEL_NUMBER == 2)
		{
			if(bGameIsInTheFinalStage) { bLOAD_END = true; bGameIsInTheFinalStage=false;}
			Manager->SetState(STATE_LEVEL2);
		}
	}
	else if (id == 2)
	{
		Manager->SetState(STATE_MENU);
	}
	

	return false;
}


bool StateGameOver::Render()
{
	back->Render(0,0);
	GUI->Render();
	////////Display Stats
	font->SetScale(1.5f);
	font->SetColor(0xffff0000);
	font->printf(1120,30,0,"S");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1144,30,0,"TATS");
	font->SetScale(1.0f);
	font->SetColor(0xffff0000);
	font->printf(1048,100,0,"T");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1060,100,0,"otal Kills                     %d", Total_kills);
	font->SetColor(0xffff0000);
	font->printf(1048,180,0,"M");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1069,180,0,"elee Kills                     %d", Melees);
	font->SetColor(0xffff0000);
	font->printf(1048,260,0,"H");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1060,260,0,"its Sustained              %d", hits_sustained);
	font->SetColor(0xffff0000);
	font->printf(1048,340,0,"B");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1060,340,0,"oxes Destroyed         %d", Box_destroyed);
	font->SetColor(0xffff0000);
	font->printf(1048,420,0,"B");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1060,420,0,"ird Kills                         %d",Birds_killed);
	font->SetColor(0xffff0000);
	font->printf(1048,500,0,"F");
	font->SetColor(ARGB(255,255,255,255));
	font->printf(1060,500,0,"inal                                %d", Total_Score);
	return false;
}


bool StateGameOver::Release()
{
	delete GUI;
	GUI = 0;
	delete back;
	back = 0;
	delete cursor; 
	cursor = 0;
	delete font;
	font = 0;

	Engine->Texture_Free(cur);
	Engine->Texture_Free(backtex);
	Engine->Texture_Free(cont);
	Engine->Texture_Free(quit);
	Engine->Effect_Free(govermusic);
	return true;
}
