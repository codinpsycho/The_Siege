#pragma once
#include "GameState.h"
#include <hgegui.h>
#include "Button.h"
#include "sprite.h"



class StateMenu : public GameState
{
	hgeSprite *cursor;
	hgeGUI *GUI;
	

public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateMenu(void);
	~StateMenu(void);
};
