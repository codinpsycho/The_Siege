#pragma once
#include <hgegui.h>
#include "GameState.h"
#include <hgesprite.h>
#include "sprite.h"
#include "Button.h"
       
class StateGamePaused : public GameState
{
	hgeSprite *cur;
	hgeGUI *GUI;

public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateGamePaused(void);
	~StateGamePaused(void);
};
