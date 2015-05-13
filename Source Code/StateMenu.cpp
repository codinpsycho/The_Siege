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

#include "StateMenu.h"
#include <hge.h>
#include <hgesprite.h>

#include "GameStateManager.h"

hgeSprite *menuback;


extern GameStateManager *Manager ;
extern HGE *Engine;

HTEXTURE mb ;
extern HTEXTURE cur ;
HTEXTURE newg;
HTEXTURE Exit ;
HTEXTURE credits;
HTEXTURE controls;
HEFFECT music;


StateMenu::StateMenu(void)
{
}

StateMenu::~StateMenu(void)
{
}


bool StateMenu::Init()
{
	
	credits = Engine->Texture_Load("Textures/Main Menu/credits.png");
	Exit = Engine->Texture_Load("Textures/Main Menu/exit.png");
	newg = Engine->Texture_Load("Textures/Main Menu/newg.png");
	cur = Engine->Texture_Load("Textures/Main Menu/cur1.png");
	mb = Engine->Texture_Load("Textures/Main Menu/menuback1.png");
	controls = Engine->Texture_Load("Textures/Main Menu/controls.png");
	
	music = Engine->Effect_Load("sound/music/main_menu.ogg");
	menuback = new hgeSprite(mb,0,0,1366,768);

	
	Engine->Effect_PlayEx(music,100,0,1,true);

	

	GUI = new hgeGUI();
	cursor = new hgeSprite(cur,0,0,32,32);
	
	GUI->SetCursor(cursor);
	GUI->AddCtrl( new Button(1,50,150,newg,newg,newg) );
	GUI->AddCtrl(new Button(2,98,215,controls,controls,controls) );
	GUI->AddCtrl( new Button(3,85,270,credits,credits,credits) );
	GUI->AddCtrl( new Button(4,65,320,Exit,Exit,Exit) );
	
	
	GUI->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	GUI->SetFocus(1);
	
	return true;
}


bool StateMenu::Update(float dt)
{
	int id = GUI->Update(dt);

	if (id == 1)  {  GUI->Leave(); Manager->SetState(STATE_NEWGAME);  return false;  }

	else if (id == 3)
	{ GUI->Leave(); Manager->SetState(STATE_CREDITS);  return false; }

	else if (id == 4)
	{
		GUI->Leave();
		return true;
	}
	else if ( id == 2 )
	{
		GUI->Leave();
		Manager->SetState(STATE_CONTROLS);
		return false;
	}



	return false;
}

bool StateMenu::Render()
{

 	menuback->Render(0,0);
	
	GUI->Render();


	return false;
}

bool StateMenu::Release()
{
	delete GUI;
	GUI = 0;
	delete menuback;
	menuback = 0;
	delete cursor;
	cursor = 0;

	Engine->Texture_Free(mb);
	Engine->Texture_Free(cur);
	Engine->Texture_Free(newg);
	Engine->Texture_Free(Exit);
	Engine->Texture_Free(credits);
	Engine->Effect_Free(music);
	return true;
}
