#include "Button.h"

bool bMouseOver = false;
Button::Button(void)
{
}

Button::~Button(void)
{
	delete sprNormal; sprNormal = 0;
	delete sprMouseOver; sprMouseOver = 0;
	delete sprMouseDown; sprMouseDown = 0;
}


Button::Button(int _id, float x, float y,HTEXTURE Normal,HTEXTURE texMO, HTEXTURE MouseDown)
{
	id = _id;
	bStatic = false;
	bEnabled = true;
	bVisible = true;
	over = Engine->Effect_Load("sound/items/over.wav");
 	click = Engine->Effect_Load("sound/items/click.wav");
	
	
	rect.Set(x , y, x + hge->Texture_GetWidth(Normal,true), y + hge->Texture_GetHeight(Normal,true));
	sprNormal = new hgeSprite( Normal, 0 , 0 ,hge->Texture_GetWidth(Normal,true) , hge->Texture_GetHeight(Normal,true));
	sprMouseOver = new hgeSprite(texMO,0,0,hge->Texture_GetWidth(texMO,true),hge->Texture_GetHeight(texMO,true));
	sprMouseDown = new hgeSprite(MouseDown,0,0,hge->Texture_GetWidth(MouseDown,true),hge->Texture_GetHeight(MouseDown,true));
 

}
bool flag=false;
//Renders the Button
void Button::Render()
{
	
	sprNormal->Render( rect.x1 , rect.y1 );
}

void Button::Update(float dt)
{
	//Do your Animation here
}

//Tis is called when the control recieves focus
void Button::Focus(bool bFocused)
{
	if (bFocused)
	{
		sprNormal->SetColor(ARGB(255,150,150,150));
		Engine->Effect_Play(over);
		flag = true;
	}
	else
	{	
		sprNormal->SetColor(0xffffffff); 
		flag=false;
	}
}

// This method is called when the GUI
// is about to appear on the screen
void Button::Enter()
{

}


// This method is called when the GUI
// is about to disappear from the screen
void Button::Leave()
{

}

bool Button::IsDone()
{
	return false;
}

bool Button::MouseLButton(bool bDown)
{
	if (bDown)
	{
		gui->SetFocus(id);
		Engine->Effect_Play(click);
	}
	else
	{
		Focus(false);
		return true;

	}

	return false;
}

void Button::MouseOver(bool bOver)
{
	if (bOver)
	{
		gui->SetFocus(id);
	}
}

bool Button::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER )
	{
		MouseLButton(true);
		return MouseLButton(false);
	}

	return false;
}



