#pragma once
#include "gamestate.h"
#include <hgegui.h>
#include <hgesprite.h>

class StateCredits : public GameState
{
	hgeGUI *GUI;
	hgeSprite *cursor;
	hgeSprite *ishPhoto;
	hgeSprite *shankerPhoto;

public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateCredits(void);
	~StateCredits(void);
};
