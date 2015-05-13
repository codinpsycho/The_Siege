#pragma once
#include "gamestate.h"
#include <hgegui.h>
#include <hgesprite.h>

class StateGameOver : public GameState
{
	hgeGUI *GUI;
	hgeSprite *cursor;
public:

	 bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateGameOver(void);
	~StateGameOver(void);
};
