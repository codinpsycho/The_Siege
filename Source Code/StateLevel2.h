#pragma once
#include "gamestate.h"
#include <hgegui.h>

class StateLevel2 :	public GameState
{
		hgeGUI *GUI;
		hgeSprite *cursor;
		
public:

	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateLevel2(void);
	~StateLevel2(void);
};
