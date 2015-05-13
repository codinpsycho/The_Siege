#pragma once
#include "GameState.h"

enum eGameState 
{
	STATE_INTRO, 
	STATE_MENU, 
	STATE_CREDITS, 
	STATE_LEVEL1, 
	STATE_LEVEL2,
	STATE_GAMEPAUSED,
	STATE_GAMEOVER,
	STATE_CONTROLS,
	STATE_NEWGAME,
};

class GameStateManager
{
	GameState* CurrentSate;
	eGameState eState;

	
public:
	void SetState(eGameState eNewState);
	bool Init();
	bool Update(float dt);
	bool Render();
	bool Release();

	GameStateManager(void);
	~GameStateManager(void);
};
