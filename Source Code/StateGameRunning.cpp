// #include "StateGameRunning.h"
// #include <hge.h>
// #include "StateGamePaused.h"
// #include "GameStateManager.h"
// #include <hgefont.h>
// #include <hgegui.h>
// extern GameStateManager *Manager ;
// extern HGE *Engine;
// hgeGUI *GUI;
// int x = 0;
// hgeFont *font;
// 
// bool paused = false;
// 
//  
// 
// StateGameRunning::StateGameRunning(void)
// {
// }
// 
// StateGameRunning::~StateGameRunning(void)
// {
// }
// 
// bool StateGameRunning::Init()
// {
// 
// 	GUI = new hgeGUI();
// 	HTEXTURE cur = Engine->Texture_Load("Textures/cur1.png");
// 	HTEXTURE rest = Engine->Texture_Load("Textures/Restart.png");
// 	HTEXTURE res = Engine->Texture_Load("Textures/resume.png");
// 	HTEXTURE ex = Engine->Texture_Load("Textures/exit.png");
// 	hgeSprite *cursor = new hgeSprite(cur,0,0,32,32);
// 	GUI->SetCursor(cursor);
// 	GUI->AddCtrl(new Button(1,100,200,res,res,res));
// 	GUI->AddCtrl(new Button(2,100,260,rest,rest,rest));
// 	GUI->AddCtrl(new Button(3,70,320,ex,ex,ex));
// 	GUI->SetNavMode(HGEGUI_CYCLED | HGEGUI_UPDOWN);
// 
// 	font = new hgeFont("fonts/fontSS.fnt");
// 	font->SetColor(ARGB(255,255,255,255));
// 	return true;
// }
// 
// bool StateGameRunning::Update(float dt)
// {
// 	
// 	if (Engine->Input_KeyDown(HGEK_ESCAPE))
// 	{
// 		paused = true;
// 		
// 	}
// 	if (paused)
// 	{
// 		int id = GUI->Update(Engine->Timer_GetDelta());
// 
// 
// 		if (id == 1)
// 		{
// 			paused = false;
// 		}
// 		else if (id == 2)
// 		{
// 			paused = false;
// 			Manager->SetState(STATE_GAMERUNNING);
// 		}
// 		else if (id == 3)
// 		{
// 			Manager->SetState(STATE_MENU);
// 		}
// 
// 	}
// 	else
// 	{
// 		x++;
// 	}
// 
// 	return false;
// }
// 
// bool StateGameRunning::Render()
// {
// 	if (paused)
// 	{
// 		GUI->Render();
// 	}
// 	else
// 	{
// 		font->printf(100,100,1,"%i",x);
// 	}
// 	
// 	
// 	
// 	
// 	return false;
// }
// 
// bool StateGameRunning::Release()
// {
// 	
// 		x = 0;
// 	
// 	
// 	
// 	return true;
// }
// 
