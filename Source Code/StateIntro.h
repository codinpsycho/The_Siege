#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include <hge.h>
#include <hgesprite.h>
#include <hgedistort.h>
#include <math.h>


class StateIntro : public GameState
{
public:
	
	virtual bool Init();
	virtual bool Update(float dt);
	virtual bool Render();
	virtual bool Release();

	StateIntro(void);
	~StateIntro(void);
};
