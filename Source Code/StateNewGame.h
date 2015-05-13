#pragma once
#include "gamestate.h"

class StateNewGame : public GameState
{
public:
	StateNewGame(void);
	virtual ~StateNewGame(void);

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();
};
