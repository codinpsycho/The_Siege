#include "GameStateManager.h"
#include "StateIntro.h"
#include "StateMenu.h"
#include "StateLevel1.h"
#include "StateLevel2.h"
#include "StateGamePaused.h"
#include "StateCredits.h"
#include "StateGameOver.h"
#include "StateControls.h"
#include "StateNewGame.h"


void GameStateManager::SetState(eGameState eNewState)
{
	if ( CurrentSate )
	{
		CurrentSate->Release();
		delete CurrentSate;
		CurrentSate = 0;
	}

	switch (eNewState)
	{
	case STATE_INTRO:
		{
			CurrentSate = new StateIntro;
			CurrentSate->Init();
			break;
		}

	case STATE_MENU:
		{
			CurrentSate = new StateMenu;
			CurrentSate->Init();
			break;
		}

	case STATE_CREDITS:
		{
			CurrentSate = new StateCredits;
			CurrentSate->Init();
			break;
		}

	case STATE_LEVEL1:
		{
			CurrentSate = new StateLevel1;
			CurrentSate->Init();
			break;
		}

	case STATE_LEVEL2:
		{
			CurrentSate = new StateLevel2;
			CurrentSate->Init();
			break;
		}

	case STATE_GAMEPAUSED:
		{
			CurrentSate = new StateGamePaused;
			CurrentSate->Init();
			break;
		}

	case STATE_GAMEOVER:
		{
			CurrentSate = new StateGameOver;
			CurrentSate->Init();
			break;
		}
	case STATE_CONTROLS:
		{
			CurrentSate = new StateControls;
			CurrentSate->Init();
			break;
		}
	case STATE_NEWGAME:
		{
			CurrentSate = new StateNewGame;
			CurrentSate->Init();
			break;
		}

	}
	
}


bool GameStateManager::Init()
{
	CurrentSate = 0;

	return true;

}

bool GameStateManager::Update(float dt)
{
	bool ret = false;

	if (CurrentSate)
	{
		ret = CurrentSate->Update(dt);
	}

	return ret;

}

bool GameStateManager::Render()
{
	bool ret = false;

	if (CurrentSate)
	{
		CurrentSate->Render();
	}

	return ret;

}


bool GameStateManager::Release()
{
	bool ret = false;

	if (CurrentSate)
	{
		CurrentSate->Release();
		delete CurrentSate;
		CurrentSate = 0;

	}
	return ret;
}



GameStateManager::GameStateManager(void)
{
}

GameStateManager::~GameStateManager(void)
{
}
