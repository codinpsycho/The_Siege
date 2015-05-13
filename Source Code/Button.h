#pragma once

#include "hge.h"
#include "hgegui.h"
extern HGE *Engine;


class Button : public hgeGUIObject
{
	hgeSprite *sprNormal;
	hgeSprite *sprMouseOver;
	hgeSprite *sprMouseDown;
	HEFFECT over;
	HEFFECT click;

public:

	Button(void);
	Button(int id,float x,float y,HTEXTURE Normal,HTEXTURE texMO, HTEXTURE MouseDown);
	virtual void Render();
	virtual void Update(float dt);
	virtual void Enter();
	virtual void Leave();
	virtual bool IsDone();
	virtual void Focus(bool bFocused);
	virtual void MouseOver(bool bOver);
	virtual bool MouseLButton(bool bDown);
	virtual bool KeyClick(int key, int chr);

	~Button(void);
};
