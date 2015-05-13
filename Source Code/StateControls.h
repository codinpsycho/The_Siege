#pragma once
#include "GameState.h"
#include "Protagonist.h"
#include "GameStateManager.h"
#include "StateMenu.h"



class StateControls : public GameState
{
public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateControls(void);
	~StateControls(void);
};
