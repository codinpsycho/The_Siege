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





#include "StateNewGame.h"
#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "MusicPlayer.h"
#include "Timer.h"
#include "sounds.h"
#include "StateGamePaused.h"
#include "GameStateManager.h"
#include <hgefont.h>
#include "sprite.h"
#include "MakeQuad.h"
#include "Protagonist.h"

extern GameStateManager *Manager ;
extern HGE *Engine;

class VTOL
{
public:
	hgeSprite *sprVtol;
	hgeVector vPosition;
	hgeVector vSpeed, vDirection;

	VTOL( ) : vPosition(0,0),vSpeed(68.0f,50.0f),vDirection(1.0f,1.0f) 	{ sprVtol = 0; }
	~VTOL( )					{ delete sprVtol;	 }
	void Init(HTEXTURE hVtex)	{ sprVtol = new hgeSprite(hVtex,0,0,768,256);	   }
	void Render()				{ sprVtol->RenderEx(vPosition.x,vPosition.y,0.0f,1.5,1.5); }
	void Release()				{ delete sprVtol; sprVtol=0;	 }
	float GetUpFace()		    { return vPosition.y; }
	float GetDownFace()		    { return ( vPosition.y + sprVtol->GetHeight() ); }
	float GetLeftFace()		    { return vPosition.x; }
	float GetRightFace()		{ return ( vPosition.x + sprVtol->GetWidth() );  }
	void Move(float dt)			
	{ 
		vPosition.x += (dt*vSpeed.x) * vDirection.x;
		vPosition.y += (dt*vSpeed.y) * vDirection.y;
	}
};


StateNewGame::StateNewGame(void)
{

}

StateNewGame::~StateNewGame(void)
{

}

namespace
{
	VTOL *Vtol14=0;
	hgeFont *font=0;
	MusicPlayer *BackGroundMusic=0, *Dialogs=0, *plane;
	hgeSprite *credits;
	Protagonist *ReAztec,*Nomad,*Prophet,*Psycho,*Jester,*ProArr[5]; 

  HTEXTURE hVtolTex=0,hTexCredits=0,hTexSky=0;
  
  int iEventsOfGame=-3,toggleCredits=1,iCounter=0;
  bool bRenderCredits=false,bFontRenderFlag = false, PauseSoundFlag=false; 
  
  Timer IntroTimer(5000);	
  float fCounter = 0.0f, fAlphaFont=0.0f;
  MakeQuad SkySpr(0,0,2048,1024);
  char ShowInfo[]= "August 4, 2011\n1930 Hours\nIAS Research Team\
\nDr.Helena Rosenthal\nD/O: Dr.Charles Rosenthal\nLocation:\nLingshan Island ( South China Sea )"; 	
  char ShowInfo2[]="3 Days Later\nAugust 7, 2011\n1300 Hours\nSky Chief\nU.S. Special Forces";
  

  char* DialogsHere[]=
  {
	  "Sound/Dialogs/Level 1/comm0.mp2",
	  "Sound/Dialogs/Level 1/comm1.mp2", 
	  "Sound/Dialogs/Level 1/comm2.mp2", 
	  "Sound/Dialogs/Level 1/comm3.mp2", 
	  "Sound/Dialogs/Level 1/comm4.mp2", 
	  "Sound/Dialogs/Level 1/comm5.mp2", 
	  "Sound/Dialogs/Level 1/comm6.mp2",
	  "Sound/Dialogs/Level 1/comm7.mp2", 
	  "Sound/Dialogs/Level 1/comm8.mp2", 
	  "Sound/Dialogs/Level 1/comm9.mp2", 
	  "Sound/Dialogs/Level 1/comm10.mp2", 
	  "Sound/Dialogs/Level 1/comm11.mp3", 
	  "Sound/Dialogs/Level 1/comm12.mp2", 
	  "Sound/Dialogs/Level 1/comm13.mp2", 
	  "Sound/Dialogs/Level 1/comm14.mp3", 
	  "Sound/Dialogs/Level 1/comm15.mp2", 
	  "Sound/Dialogs/Level 1/comm16.mp2", 
	  "Sound/Dialogs/Level 1/comm17.mp2", 
  };

  char *ShowName=0;	
  
}

extern ISoundEngine* sound_engine;
bool StateNewGame::Init()
{
	hVtolTex = Engine->Texture_Load("Sprites/vtol.png");
	hTexCredits = Engine->Texture_Load("textures/credits/credits.png");
	hTexSky = Engine->Texture_Load("textures/level1/skychief.png");

   // Memory Allocation
		      Vtol14 = new VTOL;						   Vtol14->Init(hVtolTex);
     BackGroundMusic = Dialogs = plane = 0;
   
		   credits = new hgeSprite(hTexCredits,0,0,786,768);
			  font = new hgeFont("Fonts/font.fnt");    font->SetColor(0xFFFFFFFF);
    	   ReAztec = new Protagonist(); ReAztec->Init(Engine);
			 Nomad = new Protagonist(); Nomad->Init(Engine);
		    Psycho = new Protagonist(); Psycho->Init(Engine);
		   Prophet = new Protagonist();	Prophet->Init(Engine);
		    Jester = new Protagonist();	Jester->Init(Engine);

			ProArr[0] = ReAztec;	ReAztec->vPosition.y = Vtol14->vPosition.y+200.0f;  ReAztec->vPosition.x = Vtol14->vPosition.x+620.0f;
			ProArr[1] = Nomad;  Nomad->vPosition.y = Vtol14->vPosition.y+200.0f;		Nomad->vPosition.x   = Vtol14->vPosition.y+640.0f;
			ProArr[2] = Psycho; Psycho->vPosition.y = Vtol14->vPosition.y+200.0f;		Psycho->vPosition.x  = Vtol14->vPosition.y+640.0f;
			ProArr[3] = Prophet; Prophet->vPosition.y = Vtol14->vPosition.y+200.0f;		Prophet->vPosition.x = Vtol14->vPosition.y+640.0f;
			ProArr[4] = Jester;  Jester->vPosition.y = Vtol14->vPosition.y+200.0f;		Jester->vPosition.x  = Vtol14->vPosition.y+640.0f;
			
			for(int i=0; i<5; i++ )
			{ ProArr[i]->SetFacing(FACELEFT,true);  ProArr[i]->ChangeStance(JUMPING); }
			
				
			for (int i=0; i<5; i++ )
			{
				float num = 50.0f;
				switch(rand()%4)
				{
				case 0:	 num = 35.0f;   break;
				case 1:  num = 50.0f;	break;
				case 2:  num = 65.0f;	break;
				case 3:  num = 35.0f;	break; 
				}
				
				ProArr[i]->SetSpeed( num );
			}
			
	// initializations
	SkySpr.LoadTexture(hTexSky);	
	SkySpr.SetCol( 0x00ffffff );
	bRenderCredits = false;
	PauseSoundFlag = false; 
	toggleCredits = 1;
	plane = 0;
	fCounter = 0.0f;
	fAlphaFont = 0.0f;
	Vtol14->vPosition.y = 150.0f;
	Vtol14->vPosition.x += 1650.0f;
	Vtol14->vDirection.x = -1.0f;
	Vtol14->vDirection.y = 0.0f;
	Dialogs = 0; 
	iEventsOfGame=-3;
	 
	IntroTimer.setstart();
 return true;
}



bool StateNewGame::Release()
{
	
	// Deallocate Memory
	ReAztec->Release(Engine);
	Psycho->Release(Engine);
	Nomad->Release(Engine);
	Prophet->Release(Engine);
	Jester->Release(Engine);
	Vtol14->Release();
	
	delete ReAztec;   ReAztec=0;
	delete Nomad;   Nomad=0;
	delete Psycho;  Psycho=0;
	delete Prophet; Prophet=0;
	delete Jester;  Jester=0;
	
	delete credits; credits=0;

	delete Vtol14; Vtol14=0;
	delete font; font=0;

	if(BackGroundMusic) { BackGroundMusic->Stop();  delete BackGroundMusic; BackGroundMusic=0; }
	if(Dialogs)			{ Dialogs->Stop();			delete Dialogs;			Dialogs=0;		   }
	if(plane)			{ plane->Stop();			delete plane;			plane=0;		   }
	
	// Release Textures
	Engine->Texture_Free(hTexCredits);
	Engine->Texture_Free(hVtolTex);
	Engine->Texture_Free(hTexSky);
 return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
const float X=10.0f ,Y=550.0f,CONSTANT=10.0F;

bool StateNewGame::Render()
{ 
	if( iEventsOfGame == 6  )
	{
		font->printf(550,350,0,"15 Minutes Later");
		return false;
	}
	else 
	if( iEventsOfGame >= 0 && iEventsOfGame <= 1 )		
	{	
		font->printf(X,Y,0,ShowInfo);
	}

	SkySpr.Render(Engine);
	if(iEventsOfGame==5)	for(int i=0; i<5; i++)	ProArr[i]->Render();	
	if( iEventsOfGame >= 3 )  Vtol14->Render();
	if( iEventsOfGame == 3 && Vtol14->vPosition.x < 370 && Vtol14->vPosition.x > 150 )  font->printf(X,Y,0,ShowInfo2);
	if( ShowName ) font->printf(X+480,730,0,ShowName);
	
	if( bRenderCredits ) 
	{
	if (toggleCredits == 3 ) credits->Render(525,150); // 300 ,350
	else
	if (toggleCredits == 4)  credits->Render(525,70); // 300 ,350
	else 
	    credits->Render(525,350);
	}

	

 return false;
}

void ProcessIntroStates();
void DisplayCredits(int);


bool StateNewGame::Update(float dt)
{ 
	if(IntroTimer.TimeOver() && bRenderCredits == true )
	{
		bRenderCredits = false; IntroTimer.setstart();
	}

	if(Engine->Input_GetKey() == HGEK_ESCAPE)
	{	
		Manager->SetState( STATE_LEVEL1 ); 	
		iEventsOfGame =100;
		return false;    	
	}
	else 
	if( Engine->Input_GetKey() == HGEK_PERIOD )
	{ 
		if(Dialogs) {  int tk = Dialogs->GetTrack(); if( tk > 1 && tk < Dialogs->GetTracks()-1 ) Dialogs->PlayTrack(tk+1); }
		if(BackGroundMusic) BackGroundMusic->SetPlayPosition( BackGroundMusic->GetPlayPosition()+1000 );
		if(plane) plane->SetPlayPosition( plane->GetPlayPosition()+1000 );
	}
	
	if (iEventsOfGame == 7)
	{
		Manager->SetState( STATE_LEVEL1 );
		return false;
	}

	if(iEventsOfGame < 6)
	  SkySpr.scrollX(1,0.1*dt);
		
	if(BackGroundMusic) 
	{	
		if( !BackGroundMusic->IsPlaying() )  
		{ 
			BackGroundMusic->Stop(); 
			delete BackGroundMusic; BackGroundMusic=0; 
		}
	}
	
	    ProcessIntroStates(); 


		if( iEventsOfGame > 5)  	{		return false;   	}
		else
		if( iEventsOfGame == 4 && PauseSoundFlag ) 
		{
			if(Engine->Input_GetKeyState(HGEK_ENTER)) 
			{
				Dialogs->Resume(); 
				PauseSoundFlag = false; 
				Dialogs->PlayTrack(1);
			}
			else return false; 
		}
		if( iEventsOfGame == 0 && fAlphaFont < 255.0f ) 	{	fAlphaFont+=0.5;	 font->SetColor( ARGB( fAlphaFont,255,255,255 ) );		}
		else 
		if( iEventsOfGame == 1 && fAlphaFont > 0.0f )		{	fAlphaFont -= 0.5;   font->SetColor( ARGB( fAlphaFont,255,255,255 ) );		}
		else 
		if( iEventsOfGame == 2 && fCounter < 254.0f ) 		{ 	fCounter += 0.5f;	SkySpr.SetCol( ARGB(fCounter,255,255,255) );			}
		else
		if( iEventsOfGame == 3 )				
		{ 	 
			if(Vtol14)
			{
				if(Vtol14->vPosition.x < 100.0f ) Vtol14->vDirection.x = 0.0f;	
				Vtol14->Move(dt);		
			}
			
			if( IntroTimer.TimeOver() && toggleCredits == 1 )	
			{	
				DisplayCredits(toggleCredits);	IntroTimer.setstart(); 	bRenderCredits = true; toggleCredits=2; 
			} 

		}

		if( Vtol14->vPosition.x < 1100.0f  )
		{
			if( IntroTimer.TimeOver() && toggleCredits == 2 )	
			{	
				DisplayCredits(toggleCredits);	IntroTimer.setstart(); 	bRenderCredits = true; toggleCredits=3; 
			} 
			

			if(BackGroundMusic)
			{
				if(!BackGroundMusic->IsPlaying())
				{ 
					delete BackGroundMusic; BackGroundMusic=0;
				}
			}

			if(Dialogs)
			{
				Dialogs->PlayList();	
				int trk = Dialogs->GetTrack();

				switch(trk)
				{
				case 2:  case 5:  case 6:  case 10: case 12: case 14: case 15: case 17: 
				case 3:  ShowName = "Prophet Speaking"; 
					  break;
				case 4: 
				case 7:  ShowName = "Psycho Speaking"; break;
				case 1:  
				case 8:  
				case 9:  ShowName = "Jester Speaking"; 
					  break;
			    case 13: 
				case 16: ShowName = "Pilot Speaking"; 
				default: ShowName = 0; 
				}

				if(trk == 0 && !Dialogs->IsPlaying()  )
				{
					ShowName = "You Are Codenamed Nomad, Press Enter To Respond"; 
					PauseSoundFlag = true; 
					Dialogs = new MusicPlayer(sound_engine,DialogsHere,18); 
					Dialogs->PlayTrack(1);
					Dialogs->Pause();
				}
				else 
				if(trk == 11 && !BackGroundMusic )
				{
				   BackGroundMusic = new MusicPlayer(sound_engine); 
				   BackGroundMusic->Play("Sound/music/motivational_halo_jump.ogg");
				   BackGroundMusic->SetVolume(1.0f);
				}
				
				if(!Dialogs->IsPlaying()) { Dialogs->Stop(); delete Dialogs; Dialogs = 0; ShowName = 0; }

				if( trk > 11 && BackGroundMusic )
				{
					if( IntroTimer.TimeOver() && toggleCredits == 3 && BackGroundMusic->GetPlayPosition() > 5000 )	
					{	
						DisplayCredits(toggleCredits);	IntroTimer.setstart(); 	bRenderCredits = true; toggleCredits=4; 
					} 
				}
			}
		}
		
		if(iEventsOfGame == 5)	
		{
			for(int i=0; i<iCounter; i++ )
			{
				ProArr[i]->MainAnimation->Update(dt);
			  float sp = ProArr[i]->GetSpeed();
			    if(sp < 0.6f ) sp = 0.0f;
				ProArr[i]->SetSpeed(sp-0.1f);
				ProArr[i]->vPosition.x +=  -1 * sp * dt;		
				ProArr[i]->vPosition.y +=  150 * dt;
			}
			if(IntroTimer.TimeOver()){ iCounter++; IntroTimer.setstart();}
			if(iCounter>5)	iCounter = 5;	
		}

		if(plane){	if( plane->GetVolume() < 0.70f)  plane->SetVolume( plane->GetVolume()+0.001f );		}

 return false;
}



void ProcessIntroStates()
{
	if(iEventsOfGame == -3 )
	{
		BackGroundMusic = new MusicPlayer(sound_engine);    
		BackGroundMusic->Play("Sound/Dialogs/Level 1/intro.mp3");
		iEventsOfGame = -2;
	}
	else 
	if( iEventsOfGame == -2 && BackGroundMusic )
	{		
		if( BackGroundMusic->GetPlayPosition() > 3000 )	  
		{   
			iEventsOfGame = -1;  
			plane = new MusicPlayer(sound_engine);
			plane->Play("sound/music/primordium_stinger.ogg");
		}
	}
	else
	if( iEventsOfGame == -1 && BackGroundMusic )
	{		
		if( BackGroundMusic->GetPlayPosition() > 13000 )	iEventsOfGame = 0;				      
	}
	else
	if( iEventsOfGame == 0 && BackGroundMusic )
	{		
		if( BackGroundMusic->GetPlayPosition() > 35000 )	iEventsOfGame = 1;				      
	}
	else
	if( iEventsOfGame == 1 && BackGroundMusic )
	{	 
		if( BackGroundMusic->GetPlayPosition() > 55000 )  {    iEventsOfGame = 2; font->SetColor(0xff000000);	}	   
	}
	else
	if( iEventsOfGame == 2 && fCounter >= 245.0f )
	{   
		iEventsOfGame = 3;   SkySpr.SetCol( 0xffffffff );  
		plane	= new MusicPlayer(sound_engine);   
	    plane->Play("Sound/items/plane.mp3"); 
		plane->SetVolume(0.0f); 
		plane->Loop(true);
	}
	else 
	if( iEventsOfGame == 3 && Vtol14->vDirection.x == 0 && Vtol14->vDirection.y == 0 && !BackGroundMusic)
	{												
		iEventsOfGame = 4;  Dialogs = new MusicPlayer(sound_engine);  Dialogs->Play(DialogsHere[0]);	
	}
	else 
	if( iEventsOfGame == 4 && !Dialogs )
	{
		iEventsOfGame = 5; IntroTimer.setEndTime(1500);
	}
	else 
	if( iEventsOfGame == 5 && !Dialogs && Jester->vPosition.y > 770.0f )
	{
		iEventsOfGame = 6;  IntroTimer.setEndTime(5000); IntroTimer.setstart();  font->SetScale(1.4f); font->SetColor(0xffffffff);
	}
	else 
	if( iEventsOfGame == 6 )
	{
		if( IntroTimer.TimeOver() )
			iEventsOfGame = 7;
	}
}	


void DisplayCredits(int ToggleCredits)
{
   switch(ToggleCredits)
   {
   case 1:  credits->SetTextureRect(0,0,300,150);   break;  // game mechanics presentation
   case 2:  credits->SetTextureRect(300,0,300,350); break;  // a shanker & ishkaran game
   case 3:  credits->SetTextureRect(0,150,300,100); break;  // the siege
   default: bRenderCredits = false;
   }
}
