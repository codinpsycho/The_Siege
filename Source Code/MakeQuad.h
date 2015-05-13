#pragma once
#ifndef _RNDR_H_
#define _RNDR_H_

#include <hge.h>
#include <cmath>
#include <string>

class MakeQuad
{
private:
	hgeQuad Quad;
	float height;
	float width;
	float fTileX,fTileY,fScrollX,fScrollY;

public:
	MakeQuad(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
	void SetX(float x);
	void SetY(float y);

	void SetH(float h)					  {  height = h;  Quad.v[2].y	= Quad.v[0].y + height;   Quad.v[3].y	= Quad.v[0].y + height; }
	void SetW(float w)					  {  width = w;	Quad.v[1].x	= Quad.v[0].x + width;  Quad.v[2].x	= Quad.v[0].x + width;  }
	void TranceformX(float x , int dirX)  {  Quad.v[0].x = Quad.v[0].x + (x*dirX);  SetX(Quad.v[0].x);   }     // dirX 1,-1
	void TranceformY(float y, int dirY)	  {	 Quad.v[0].y = Quad.v[0].y + (y*dirY);  SetY(Quad.v[0].y);   }     // dirY 1,-1  
	void scrollX(int c = 1,float sc = 0.1f )     {	fScrollX += sc*c;  setTexture(fScrollX,fScrollY );    }
	void scrollY( int c = 1,float sc = 0.1f)	 {   fScrollY += sc*c;  setTexture(fScrollX, fScrollY);	  }	
	void SetBlend(int b)			 {	 Quad.blend = b;						   }
	void Render(HGE *hge) const		 {	 hge->Gfx_RenderQuad(&Quad);			   }
	void RenderEx(HGE *hge,float x,float y)	 { height=x; width=y;	Render(hge);   }
	void ScaleX(float s, int zoom )  {	 width+= s*zoom;	 SetX(Quad.v[0].x);	   }
	void ScaleY(float s, int zoom )  {   height += s*zoom;   SetY(Quad.v[0].y);	   }
	void setTileU(float Y)			 {   fTileY=Y;  setTexture();				   }
	void setTileV(float X)			 {   fTileX=X;  setTexture();				   }
	void flipX()					 {   width *= -1;  SetX(Quad.v[0].x);		   }
	void flipY()					 {   height *= -1;	SetY(Quad.v[0].y);		   }	
	void resetScroll()				 {   fScrollX=fScrollY=0;					   }	


	void Rotate(float Theta);
	void LoadTexture(HTEXTURE);
	void SetZbuff(float z, int c = -1);     
	void SetCol(int col, int c = -1 );       
	void setTexture( float U=0.0f, float V=0.0f );

};

#endif