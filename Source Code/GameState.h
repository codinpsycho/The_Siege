#pragma once

class GameState
{
	
public:
	GameState(void);

	virtual bool Init() =0;
	virtual bool Update(float dt) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;

	~GameState(void);
};
