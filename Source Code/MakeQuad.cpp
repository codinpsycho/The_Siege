#include "MakeQuad.h"
#include "windows.h"
#include "string"

MakeQuad::MakeQuad(float x, float y, float w, float h)
{
	height = h;
	width = w;
	SetX(x);
	SetY(y);
	SetBlend(BLEND_DEFAULT);
	SetZbuff(0.5);	
	SetCol(0xFFFFFFFF);		
	fTileX = 1.0f;
	fTileY = 1.0f;
}

void MakeQuad::SetX(float x)
{
	Quad.v[0].x	= x;
	Quad.v[1].x	= Quad.v[0].x + width;
	Quad.v[2].x	= Quad.v[0].x + width;
	Quad.v[3].x	= Quad.v[0].x;
}

void MakeQuad::SetY(float y)
{
	Quad.v[0].y	= y;
	Quad.v[1].y	= Quad.v[0].y;
	Quad.v[2].y	= Quad.v[0].y + height;
	Quad.v[3].y	= Quad.v[0].y + height;
}


void MakeQuad::Rotate(float Theta)
{
	for ( int i=0; i<4; i++ )
	{
		Quad.v[i].x = ( (Quad.v[i].x) * cos(Theta) ) - ( Quad.v[i].y * sin(Theta) );
		Quad.v[i].y = ( (Quad.v[i].x) * sin(Theta) ) + ( Quad.v[i].y * cos(Theta) );
	}
}

void MakeQuad::LoadTexture(HTEXTURE hTex)
{	
	Quad.tex = hTex;
	setTexture();
}


void MakeQuad::SetCol(int col, int c )       
{    
	if( c != -1  && ( c >= 0 && c < 4 ) )  {  Quad.v[c].col = col; return;  }
	for( int i=0; i<4; i++ ) Quad.v[i].col = col;    	
}


void MakeQuad::SetZbuff(float z, int c )     
{    
	if ( c != -1 && ( c >= 0 && c < 4 ))   { Quad.v[c].z = z; return;  }
	for( int i=0; i<4; i++ ) Quad.v[i].z = z;    
}


void MakeQuad::setTexture( float U, float V )
{
	Quad.v[0].tx = U;				Quad.v[0].ty = V;
	Quad.v[1].tx = U+fTileX;		Quad.v[1].ty = V;
	Quad.v[2].tx = U+fTileX;		Quad.v[2].ty = V+fTileY;
	Quad.v[3].tx = U;				Quad.v[3].ty = V+fTileY;
}