/* GAME MEACHANICS PRESENTATION ----> THE SIEGE
FOR EDUCATIONL PURPOSE ONLY
GAME PROGRAMMERS ----> ISHKARAN SINGH (AsS^Ss!n)
SHANKER SHARMA (KING SEAN)
COTACT---->
ISHKARAN SINGH : ishkaran.fearme@gmail.com
ishkaran.singh@hotmail.com
SHANKER SHARMA : igamer_1990@yahoo.com

GAME MECHANICS : gamemechanics.studio@gmail.com

THIS IS GAME MECHANICS FIRST GAME AND WE ARE STILL IN LEARNING PROCESS
JUST TRYING TO PROVE OUR INTENSE PASSION AND ZEAL TOWARDS GAME PROGRAMMING AND CREATING
QUALITY AND CREATIVE GAMES.
*/





#include "sprite.h"

 extern HGE * Engine;



//Constructors
sprite::sprite(void)
{
	for (int i = 0 ;i < 4 ; i ++)
	{
		//sets the z-buffer
		quad.v[i].z = 0;
		//sets the color of each buffer
		quad.v[i].col = ARGB(255,255,255,255);
	}
	cordinates.x = quad.v[0].x;
	cordinates.y = quad.v[0].y;
	dir.x = 1;
	dir.y = 1;
	velocity.x = .2f;
	velocity.y = .2f;
	
}

sprite::~sprite(void)
{
	for (int i = 0; i < 4 ; i ++)
	{
		//sets the z-buffer
		quad.v[i].z = 0;
		//sets the color of each buffer
		quad.v[i].col = ARGB(255,0,0,0);
	}

}

sprite::sprite(float x, float y, float width, float height)
{
	for (int i = 0 ;i < 4 ; i ++)
	{
		//sets the z-buffer
		quad.v[i].z = 0.5;
		//sets the color of each buffer
		quad.v[i].col = ARGB(255,255,255,255);
	}
	
	
	//sets the desired values to vertices
	quad.v[0].x = x;
	quad.v[0].y = y;
	quad.v[1].x = x + width;
	quad.v[1].y = y;
	quad.v[2].x = x + width;
	quad.v[2].y = y + height;
	quad.v[3].x = x;
	quad.v[3].y = y + height;
	fWidth = width;
	fHeight = height;
	cordinates.x = quad.v[0].x;
	cordinates.y = quad.v[0].y;
	dir.x = 1;
	dir.y = 1;
	velocity.x = .2f;
	velocity.y = .2f;
	


}


//Function to render the quad
void sprite::Render(float x1,float y1)
{
	cordinates.x = x1;
	cordinates.y = y1;
	update();

	Engine->Gfx_RenderQuad( &quad );
}


//MOvement of the sprite
void sprite::moveX(float dt)
{
	cordinates.x += dir.x * (velocity.x*dt);
	update();
}

void sprite::moveY(float dt)
{
	cordinates.y+=dir.y * (velocity.y*dt);
	update();
}

//updates all the cordinates
void sprite::update()
{
	fWidth = Engine->Texture_GetWidth(quad.tex);
	fHeight = Engine->Texture_GetHeight(quad.tex);
	quad.v[0].x = cordinates.x; quad.v[0].y = cordinates.y;
	quad.v[1].x = quad.v[0].x + fWidth;
	quad.v[1].y = quad.v[0].y;
	quad.v[2].x = quad.v[0].x + fWidth;
	quad.v[2].y = quad.v[0].y + fHeight;
	quad.v[3].x = quad.v[0].x;
	quad.v[3].y = quad.v[0].y + fHeight;

}


void sprite::setDirX(int d)
{
	if (d > 0)
	{
		dir.x = 1;
	}
	else if (d < 0)
	{
		dir.x = -1;
	}
	else dir.x = 0;
}


void sprite::setDirY(int d)
{
	if (d > 0)
	{
		dir.y = 1;
	}
	else if (d < 0)
	{
		dir.y = -1;
	}
	else dir.y = 0;
}
//Loads the texture from hard disk
/*
void sprite::LoadTexture(char* texture)
{
	quad.tex = Engine->Texture_Load(texture);
	
	
	
	quad.blend = BLEND_DEFAULT;

	quad.v[0].tx = 0; quad.v[0].ty = 0; 
	quad.v[1].tx = 1; quad.v[1].ty = 0; 
	quad.v[2].tx = 1; quad.v[2].ty = 1; 
	quad.v[3].tx = 0; quad.v[3].ty = 1;

	update();
}
*/

void sprite::LoadTexture(HTEXTURE texture)
{
	quad.tex = texture;

	quad.blend = BLEND_DEFAULT;

	quad.v[0].tx = 0; quad.v[0].ty = 0; 
	quad.v[1].tx = 1; quad.v[1].ty = 0; 
	quad.v[2].tx = 1; quad.v[2].ty = 1; 
	quad.v[3].tx = 0; quad.v[3].ty = 1;

	update();
}

void sprite::flipX()
{
	quad.v[1].tx = -quad.v[1].tx;
	quad.v[2].tx = -quad.v[2].tx;
	quad.v[0].tx *= -1;
	quad.v[3].tx *= -1;

}

void sprite::flipY()
{
	
	 quad.v[2].ty *= -1;
	 quad.v[3].ty *= -1;
	 quad.v[0].ty *= -1; 
	 quad.v[1].ty *= -1; 
	
	
}

float sprite::retDownFace()  { return quad.v[0].y + fHeight; }
float sprite::retUpFace()    { return quad.v[0].y; }
float sprite::retLeftFace()  { return quad.v[0].x; }
float sprite::retRightFace() { return quad.v[0].x + fWidth; }

void sprite::setSpeedX(float s)
{
	velocity.x = s;
}

void sprite::setSpeedY(float s)
{
	velocity.y = s;
}

void sprite::setX(float x) { cordinates.x = x; update();}
void sprite::setY(float y) { cordinates.y = y; update();}





void sprite::scaleX(float sx)
{
	fWidth*= sx;
	update();
}

void sprite::scaleY(float sy)
{
	fHeight*= sy;
	update();
}

void sprite::tileX(float t)
{
	quad.v[1].tx = t;
	quad.v[2].tx = t;

}

void sprite::tileY(float t)
{
	quad.v[2].ty = t;
	quad.v[3].ty = t;

}
int sprite::setColorVertex(int a,int r,int g,int b,int v)
{
	if (v < 0  || v > 3 || !(a>=0 && a<=255 && r>=0 && r<=255 && g>=0 && g<=255 && b>=0 && b<=255))
	{
		return 0;
	}
	else
		quad.v[v].col = ARGB(a,r,g,b);
	return 0;
}

int sprite::setColor(int a,int r,int g,int b)
{
	if (a>=0 && a<=255 && r>=0 && r<=255 && g>=0 && g<=255 && b>=0 && b<=255 )
	{

		for (int i = 0 ;i < 4 ; i ++)
		{

			//sets the color of each buffer
			quad.v[i].col = ARGB(a,r,g,b);
		}
		return 0;
	}
	else return 0;
	
}

void sprite::scrollY(float speed,float dir)
{
	

	quad.v[0].tx = 0; quad.v[0].ty += speed*dir; 
	quad.v[1].tx = 1; quad.v[1].ty += speed*dir; 
	quad.v[2].tx = 1; quad.v[2].ty += speed*dir; 
	quad.v[3].tx = 0; quad.v[3].ty += speed*dir;

}

void sprite::scrollX(float speed,float dir)
{
	

	quad.v[0].tx += speed*dir; quad.v[0].ty = 0; 
	quad.v[1].tx += speed*dir; quad.v[1].ty = 0;
	quad.v[2].tx += speed*dir; quad.v[2].ty = 1; 
	quad.v[3].tx += speed*dir; quad.v[3].ty = 1;

}

void sprite::CurrentVertices(float &x , float &y, float &width, float &height)
{
	x = quad.v[0].x;
	y = quad.v[0].y;
	width = quad.v[1].x - x;
	height = quad.v[2].y - y;
}

void sprite::RotateClockwise()
{
	

	for ( int i = 0; i < 4; i++)
	{
		if( quad.v[i].tx == 0 && quad.v[i].ty == 0 )
		{
			quad.v[i].tx = 0; 
			quad.v[i].ty = 1;
			continue;
		}
		if( quad.v[i].tx == 1 && quad.v[i].ty == 0 )
		{
			quad.v[i].tx = 0; 
			quad.v[i].ty = 0;
			continue;
		}

		if( quad.v[i].tx == 1 && quad.v[i].ty == 1 )
		{
			quad.v[i].tx = 1; 
			quad.v[i].ty = 0;
			continue;
		}

		if( quad.v[i].tx == 0 && quad.v[i].ty == 1 )
		{
			quad.v[i].tx = 1; 
			quad.v[i].ty = 1;
			continue;
		}

	}

}
void sprite::RotateCounterClockwise()
{
	

	for ( int i = 0; i < 4; i++)
	{
		if( quad.v[i].tx == 0 && quad.v[i].ty == 0 )
		{
			quad.v[i].tx = 1; 
			quad.v[i].ty = 0;
			continue;
		}
		if( quad.v[i].tx == 1 && quad.v[i].ty == 0 )
		{
			quad.v[i].tx = 1; 
			quad.v[i].ty = 1;
			continue;
		}

		if( quad.v[i].tx == 1 && quad.v[i].ty == 1 )
		{
			quad.v[i].tx = 0; 
			quad.v[i].ty = 1;
			continue;
		}

		if( quad.v[i].tx == 0 && quad.v[i].ty == 1 )
		{
			quad.v[i].tx = 0; 
			quad.v[i].ty = 0;
			continue;
		}

	}

}


void sprite::makeBlacWhite(int shade)
{

	for (int i = 0 ;i < 4 ; i ++)
	{

		//sets the color of each buffer
		quad.v[i].col = ARGB(255,shade,shade,shade);
	}

}

hgeVector sprite::getPosition()
{
	return cordinates;
}

hgeVector sprite::getDir()
{
	return dir;
}

hgeVector sprite:: getVelocity()
{
	return velocity;
}

void sprite::setDir(hgeVector v)
{
	dir = v;
}

void sprite::setVelocity(hgeVector v)
{
	velocity = v;
}

void sprite::setCordinates(hgeVector v)
{
	cordinates = v;
	update();
}

void sprite::setWidth(float width)
{
	fWidth = width;
}

void sprite::setHeight(float height)
{
	fHeight = height;
}

void sprite::SetZ(float _z)
{
	for (int i = 0 ;i < 4 ; i ++)
	{
		//sets the z-buffer
		quad.v[i].z = _z;
		
	}
}
	


