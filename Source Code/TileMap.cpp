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




#include "TileMap.h"
#include <fstream>
#include "LevelObjects.h"
#include <vector>
using  namespace std;


TileMap::TileMap(void)
{
}


void TileMap::Read(const char* text)
{
	file = text;

	ifstream in;
	in.open(file);

	while (!in.eof())
	{
		char ch[128];

		in >> ch;	//reads a word

		if (strcmp(ch,"fTileWidth") == 0)
		{
			in >> ch;	//reads fTileWidth value
			fTileWidth = atof(ch);
		}

		else if (strcmp(ch,"fTileHeight") == 0)
		{
			in >> ch;
			fTileHeight = atof(ch);
		}


		else if (strcmp(ch,"fImageWidth") == 0)
		{
			in >> ch;
			fImageWidth = atof(ch);
		}

		else if (strcmp(ch,"fImageWidth") == 0)
		{
			in >> ch;
			fImageHeight = atof(ch);
		}

		else if (strcmp(ch,"iTileXCount") == 0)
		{
			in >> ch;
			iTileXCount = atoi(ch);
		}

		else if (strcmp(ch,"iTileYCount") == 0)
		{
			in >> ch;
			iTileYCount = atoi(ch);
		}
		else if (strcmp(ch,"iHeight1") == 0)
		{
			in >> ch;
			iHeight1 = atoi(ch);
		}
		else if (strcmp(ch,"iHeight2") == 0)
		{
			in >> ch;
			iHeight2 = atoi(ch);
		}
		else if (strcmp(ch,"iHeight3") == 0)
		{
			in >> ch;
			iHeight3 = atoi(ch);
		}
		else if (strcmp(ch,"iHeight4") == 0)
		{
			in >> ch;
			iHeight4 = atoi(ch);
		}

		else if (strcmp(ch,"iExtraSpace") == 0)
		{
			in >> ch;
			iExtraSpace = atoi(ch);
		}

		else if (strcmp(ch,"iGiveExtraSpace") == 0)
		{
			in >> ch;
			iGiveExtraSpace = atoi(ch);
		}

		else if (strcmp(ch,"iCollidable") == 0)
		{
			in >> ch;
			iCollidable = atoi(ch);
		}

		else if (strcmp(ch,"iDestructable") == 0)
		{
			in >> ch;
			iDestructable = atoi(ch);
		}






		else if(strcmp(ch,"data") == 0)
		{
			data = new int[iTileXCount*iTileYCount];

			for (int i = 0 ; i < iTileXCount*iTileYCount ; i++)
			{
				in >> ch;
				data[i] = atoi(ch);

			}

		}
	}

	in.close();

}

void TileMap::CreateLevel()
{

	for ( int i = 0; i < iTileXCount*iTileYCount; i++ )
	{


		if (data[i] != 0 && data[i] != 10)
		{
			SetXY(data[i]);
			SetHeight(data[i]);
			tile->SetTextureRect(rectX, rectY, fTileWidth,fTileHeight );
			
				LevelObjects obj(data[i],tile->GetTexture(),rectX,rectY,fTileWidth,fTileHeight,xPos,yPos,iCollidable,iDestructable);
				Objects.push_back(obj);
			
		}

		if (data[i] == 10)
		{
			xPos += iExtraSpace;
		}
		else
			xPos += fTileWidth;
	}
	delete data;
	data = 0;

}

void TileMap::Render()
{
	for (int i = 0 ; i < Objects.size();i++)
	{
		Objects[i].Render();

	}

}

void TileMap::Move(float speed,float dir)
{

	for (int i = 0 ; i < Objects.size();i++)
	{
		Objects[i].ShiftPosX(speed,dir);

	}

}




void TileMap::SetPos(int x, int y)
{
	xPos = x;
	yPos = y;
}

void TileMap::SetTileImage(HTEXTURE tex)
{
	tile = new hgeSprite(tex,0,0,fTileWidth,fTileHeight);
}

void TileMap::setTileShift(float shift)
{
	fTileShift = shift;

}

TileMap::~TileMap(void)
{
}


void TileMap::SetXY(int index)
{
	int i = 0;
	int tempX = index;
	int tempY = 0;
	while (tempX*fTileWidth > fImageWidth )
	{
		tempX -= fImageWidth/fTileWidth;
		tempY += fTileHeight;

	}

	rectX = (tempX-1)*fTileWidth;
	rectY = tempY;
}

void TileMap::SetHeight(int index)
{
	if (index == 1)
	{
		yPos = iHeight1;
	}

	else if (index == 2)
	{
		yPos = iHeight2;
	}
	else if (index == 3)
	{
		yPos = iHeight3;
	}
	else if (index == 4)
	{
		yPos = iHeight4;
	}
}

void TileMap::Release()
{
	/*
	for ( int i = 0 ; i < Objects.size() ; i++)
	{
		Objects.erase(Objects.begin() + i);
	}
	*/
	while(!Objects.empty())
	{
		LevelObjects* ob = &(Objects.back());
		ob->Release();
		Objects.pop_back();
	}

}




