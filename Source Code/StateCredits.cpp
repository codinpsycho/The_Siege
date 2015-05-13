
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






#include "StateCredits.h"
#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>
#include "sprite.h"
#include "GameStateManager.h"
#include "Button.h"

extern GameStateManager *Manager;
extern HGE *Engine;
extern hgeFont *font;
hgeSprite *creditback,*screen1,*screen2,*gpSpr;
bool bShowIsh ;
bool bShowShanker ;
float renderY;
HTEXTURE ish ;
HTEXTURE sh;
HTEXTURE iphoto,shPhoto;
HTEXTURE hSc1Tex,hSc2Tex,gpTex ;
extern HTEXTURE cur;
HEFFECT creditmusic;

StateCredits::StateCredits(void)
{
}

StateCredits::~StateCredits(void)
{
}


bool StateCredits::Init()
{
	bShowIsh = false;
	bShowShanker = false;

	hSc1Tex = Engine->Texture_Load("Textures/credits/credits1.png");
	hSc2Tex = Engine->Texture_Load("Textures/credits/credits2.png");
	gpTex = Engine->Texture_Load("Textures/credits/gp.png");

	screen1 = new hgeSprite(hSc1Tex,0,0,1366,768);
	screen2 = new hgeSprite(hSc2Tex,0,0,1366,768);
	  gpSpr = new hgeSprite(gpTex,0,0,324,46);

	renderY = 768;
	creditmusic = Engine->Effect_Load("sound/music/credits.ogg");
	Engine->Effect_PlayEx(creditmusic,100,0,1,true);
	creditback = 0;

	//Init gui
	GUI = new hgeGUI();
	//sets cursor
	cur = Engine->Texture_Load("Textures/Main Menu/cur1.png");
	cursor = new hgeSprite(cur,0,0,32,32);
	GUI->SetCursor(cursor);
	//loads textures
    ish = Engine->Texture_Load("Textures/credits/ish.png");
	sh = Engine->Texture_Load("Textures/credits/shanker.png");
	iphoto = Engine->Texture_Load("Textures/credits/ishphoto.jpg");
	shPhoto = Engine->Texture_Load("Textures/credits/shphoto.jpg");
	//Loads Buttons
	GUI->AddCtrl(new Button(1,650,60,ish,ish,ish));
	GUI->AddCtrl(new Button(2,1050,60,sh,sh,sh));

	GUI->SetNavMode( HGEGUI_CYCLED | HGEGUI_LEFTRIGHT );
	GUI->SetFocus(1);
	
	//Loads our Photos
	ishPhoto = new hgeSprite(iphoto,0,0,597,598);
	shankerPhoto = new hgeSprite(shPhoto,0,0,598,598);

	return true;
}

bool StateCredits::Update(float dt)
{
	int id = GUI->Update(dt);
	if ( renderY > -768  )
		renderY -= 0.5;
	else
	{
		renderY = -768;
	}
	
	if (Engine->Input_KeyDown(HGEK_ESCAPE))
	{
		GUI->Leave();
		Manager->SetState(STATE_MENU);  return false;
	}

	

	if (id == 1)
	{
		bShowShanker = false;
		bShowIsh = true;
	}

	else if (id == 2)
	{
		bShowIsh = false;
		bShowShanker = true;
	}



	return false;
}


bool StateCredits::Render()
{
	
	screen1->Render(10,renderY);
	screen2->Render(10,screen1->GetHeight()+renderY);
	
	gpSpr->Render(800,10);	

	if (bShowIsh)
	{
		
		ishPhoto->Render(660,130);
	}

	else if (bShowShanker)
	{
		shankerPhoto->Render(660,130);
	}

	GUI->Render();

	return false;
}


bool StateCredits::Release()
{
	delete screen1; screen1=0;
	delete screen2; screen2=0;
	creditback = 0;
	GUI->Leave();
	delete GUI;
	GUI = 0;
	delete cursor;
	cursor = 0;
	delete ishPhoto;
	ishPhoto = 0;
	delete shankerPhoto;
	shankerPhoto = 0;
	delete gpSpr;
	gpSpr=0;

	//Frees Textures
	Engine->Texture_Free(ish);
	Engine->Texture_Free(sh);
	Engine->Texture_Free(iphoto);
	Engine->Texture_Free(shPhoto);
	Engine->Texture_Free(hSc1Tex);
	Engine->Texture_Free(hSc2Tex);
	Engine->Texture_Free(cur);
	Engine->Texture_Free(gpTex);
	Engine->Effect_Free(creditmusic);
	return true;
}
