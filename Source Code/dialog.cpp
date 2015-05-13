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


#include "Enemy.h"
#include "dialog.h"
#include <cstdlib>

Dialog::Dialog(void)
{

}

Dialog::~Dialog(void)
{

}


const char* strFront[] =
{
	"Sound/Dialogs/Type 1/",
	"Sound/Dialogs/Type 2/",
	"Sound/Dialogs/Type 3/",
	"Sound/Dialogs/Type 4/",
};


const char* strDialogs[] =
{
	"taunt_1.mp2",              // 0
	"taunt_2.mp2",				// 1 
	"taunt_3.mp2",				// 2
	"taunt_4.mp2",				// 3
	"taunt_5.mp2",				// 4

	"command_1.mp2",			// 5
	"command_2.mp2",			// 6
	"command_3.mp2",			// 7
	"command_4.mp2",			// 8

	"compromise_1.mp2",			// 9
	"compromise_2.mp2",			// 10
	"compromise_3.mp2",			// 11

	"status_1.mp2",				// 12
	"status_2.mp2",				// 13
	"status_3.mp2",				// 14

	"warning.mp2",				// 15

	"death_1.mp2",				// 16
	"death_2.mp2",				// 17

	"meleedeath_1.mp2",			// 18
	"meleedeath_2.mp2",			// 19

	"request_1.mp2",			// 20
	"request_2.mp2",			// 21	

	"null.wav",					// 22
};



void Dialog::LoadDialogs( const char* str1, const char* str2[], HGE* Engine)
{
	for( int i=0; i<SIZE; i++ )
	{
		std::string s1 = str1;
		std::string s2 = str2[i];
		std::string s3;
		s3 = s1+s2;
		const char* p = s3.c_str();

		hDialogs[i] = Engine->Effect_Load(p);

		if( !hDialogs[i] )
		{
			MessageBox(0, p, "File Not Found", MB_OKCANCEL|MB_ICONERROR);
		}  
	}

}


void Dialog::Release(HGE* Engine)
{
   for( int i=0; i<SIZE; i++ )	Engine->Effect_Free( hDialogs[i] ); 	
}



HEFFECT Dialog::Speak(eDIALOG_CONTEXT DIA)
{
	int index = 0;
	switch(DIA)
	{
	case TAUNT:   switch(rand()%5)
					  {
						case 0:  index = 0; break;
						case 1:  index = 1; break;
						case 2:  index = 2; break;
						case 3:  index = 3; break;
						case 4:  index = 4; break;
					  }
		 break;	
	case COMMAND:	   switch(rand()%4)
					   {
						case 0:  index = 5; break;
						case 1:  index = 6; break;
						case 2:  index = 7; break;
						case 3:  index = 8; break;
					   } 
		 break;
	case COMPROMISE:  switch(rand()%3)
				      {
					   case 0:  index = 9;  break;
					   case 1:  index = 10; break;
					   case 2:  index = 11; break;
				      }
		 break;
	case STATUS:      switch(rand()%3)
				      {
					   case 0:  index = 12; break;
					   case 1:  index = 13; break;
					   case 2:  index = 14; break;
				      }
		 break;
	case WARN:        index = 15;			break;
	case DEATH:		  switch(rand()%2)
				      {
					   case 0:  index = 16; break;
					   case 1:  index = 17; break;
				      }	
		 break;
	case MELEE_DEATH: switch(rand()%2)
				      {
					   case 0:  index = 18; break;
					   case 1:  index = 19; break;
				      }
		 break;
	case REQUEST:     switch(rand()%2)
				      {
					   case 0:  index = 21; break;
					   case 1:  index = 20; break;
				      }
		 break;
	case SAY_NOTHING:
	default:          index = 22;
	}

  return hDialogs[index];
}


Dialog  EnemyVoice1,EnemyVoice2,EnemyVoice3,EnemyVoice4;


void LoadVoices(HGE* Engine)
{
	EnemyVoice1.LoadDialogs(strFront[0], strDialogs, Engine);
	EnemyVoice2.LoadDialogs(strFront[1], strDialogs, Engine);
	EnemyVoice3.LoadDialogs(strFront[2], strDialogs, Engine);
	EnemyVoice4.LoadDialogs(strFront[3], strDialogs, Engine);
}

void ReleaseVoices(HGE* Engine)
{
	EnemyVoice1.Release(Engine);
	EnemyVoice2.Release(Engine);
	EnemyVoice3.Release(Engine);
	EnemyVoice4.Release(Engine);
}


HTEXTURE EnemySpeaks(const Enemy* enemy,eDIALOG_CONTEXT context)
{
	HTEXTURE ret=0;
	switch(enemy->eENEMY_VOICE)
	{
	case VOICE_TYPE_1: ret = EnemyVoice1.Speak(context);  break;
	case VOICE_TYPE_2: ret = EnemyVoice2.Speak(context);  break;
	case VOICE_TYPE_3: ret = EnemyVoice3.Speak(context);  break;
	case VOICE_TYPE_4: ret = EnemyVoice4.Speak(context);  break;
	}
	return ret;
}

