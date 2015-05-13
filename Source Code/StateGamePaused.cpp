#include "StateGamePaused.h"
#include <hge.h>
#include "GameStateManager.h"


extern GameStateManager *Manager ;
extern HGE *Engine;
hgeSprite *PauseBack;

StateGamePaused::StateGamePaused(void)
{
}

StateGamePaused::~StateGamePaused(void)
{
}



bool StateGamePaused::Init()
{

	HTEXTURE cur = Engine->Texture_Load("Textures/cur1.png");
	HTEXTURE rest = Engine->Texture_Load("Textures/Restart.png");
	HTEXTURE ex = Engine->Texture_Load("Textures/exit.png");
	HTEXTURE pb = Engine->Texture_Load("Textures/pauseback.png");
	PauseBack = new hgeSprite(pb,0,0,1024,768);
	hgeSprite *cursor = new hgeSprite(cur,0,0,32,32);
	GUI = new hgeGUI();
	GUI->SetCursor(cursor);
	
	GUI->AddCtrl(new Button(1,200,260,rest,rest,rest));
	GUI->AddCtrl(new Button(2,370,320,ex,ex,ex));
	GUI->SetNavMode(HGEGUI_CYCLED | HGEGUI_UPDOWN);

	return true;
}

bool StateGamePaused::Update(float dt)
{
	
	if ( Engine->Input_KeyDown( HGEK_ESCAPE ) )
	{
		Manager->SetState( STATE_LEVEL1 );
		return false;
	}



	int id = GUI->Update(Engine->Timer_GetDelta());
	if (id == 3) // exit
	{
		
		Manager->SetState(STATE_MENU);
	}
	else if ( id == 1)  // resume
	{
		
		Manager->SetState(STATE_LEVEL1);
	}
	

	return false;
}
  
bool StateGamePaused::Render()
{

	GUI->Render();
	
	
	return false;
}


bool StateGamePaused::Release()
{
	
	return true;
}
