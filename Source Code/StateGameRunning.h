#pragma once
#include "GameState.h"

class StateGameRunning : public GameState
{
public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateGameRunning(void);
	~StateGameRunning(void);
};
