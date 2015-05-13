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





#include "MusicPlayer.h"

MusicPlayer::MusicPlayer( ISoundEngine* Ptr, char** lst, unsigned int trks )
{
	bPlayList =  ( lst == 0 ) ?	false : true;
	iTotalTracks = trks;
	pSoundTrack = 0;
	List = lst;
	iTrackNum = 0;
	volume = 1.0f;
	engine = Ptr;
	nextTrack = 0;
	bCycle = false;
}

MusicPlayer::~MusicPlayer()
{	
	if( pSoundTrack ) 	pSoundTrack->drop();
}

void MusicPlayer::PlayTrack(unsigned int pt,bool lop)		  
{	 
	if(!List) return;  
	if( pt >= iTotalTracks ) return;
	Play(List[pt],lop);   
	nextTrack = iTrackNum = pt;   
	++nextTrack;
	if(bPlayList) SetNext(iTrackNum+1);
}

void MusicPlayer::Play(const char* s, bool lop)				  
{  
	if( pSoundTrack != 0 )	   {	pSoundTrack->stop();  pSoundTrack->drop();   }
	pSoundTrack = engine->play2D(s,lop,false,true); 
	if(pSoundTrack)
	pSoundTrack->setVolume(volume);
	str = s;  
}

void MusicPlayer::LoadPlayList( char** lst, unsigned int trks )
{
	bPlayList = true;
	iTotalTracks = trks;
	List = lst;
	iTrackNum = 0;
	nextTrack = 0;
}

void MusicPlayer::PlayList()
{
	if( !List || !bPlayList || !pSoundTrack ) return;

	if( pSoundTrack->isFinished() )
	{
		if(!pSoundTrack)
		pSoundTrack->stop();
		if(nextTrack < iTotalTracks)
		{ Play( List[nextTrack] ); }
		iTrackNum = nextTrack;
		++nextTrack;
		if( nextTrack >= iTotalTracks )  
		{	
			nextTrack = 0;
			if( bCycle == false ) bPlayList = false;
		}
	}
}

void MusicPlayer::Stop()							  
{	
	if( pSoundTrack == 0 ) return;
	pSoundTrack->stop(); 
	pSoundTrack->drop();	
	pSoundTrack=0;    
}

bool MusicPlayer::IsFinished()						  
{ 
	if(pSoundTrack==0) return true;
	return pSoundTrack->isFinished();		
} 

void MusicPlayer::SetTrack(unsigned int n)   { 	 if( n >= 0 && n < iTotalTracks )	iTrackNum = n;   }
void MusicPlayer::RaiseVolume()  {  volume += 0.01f;  if(volume > 1.0f) volume=1.0f;  pSoundTrack->setVolume(volume);  }
void MusicPlayer::LowerVolume()  {  volume -= 0.01f;  if(volume < 0.0f) volume=0.0f;  pSoundTrack->setVolume(volume);  }
void MusicPlayer::Loop(bool lp)						  { if(pSoundTrack) pSoundTrack->setIsLooped(lp);								  }
void MusicPlayer::Pause()							  { if(pSoundTrack) pSoundTrack->setIsPaused(true);					    	  }
void MusicPlayer::Resume()							  { if(pSoundTrack) pSoundTrack->setIsPaused(false);							  }
void MusicPlayer::SetNext(unsigned int n)		      { if( n >= 0 && n < iTotalTracks ) nextTrack = n;              }
unsigned int MusicPlayer::GetPlayLength()			  { return pSoundTrack->getPlayLength();	} 
unsigned int MusicPlayer::GetPlayPosition()			  { return pSoundTrack->getPlayPosition();	}   
float MusicPlayer::GetVolume()						  { return volume;							}		
float MusicPlayer::GetPan()							  { return pSoundTrack->getPan();			}	

void MusicPlayer::SetPlayPosition( unsigned int ui )  { if(pSoundTrack) pSoundTrack->setPlayPosition(ui);		}
void MusicPlayer::SetVolume(float v)				  { volume = v; if(pSoundTrack) pSoundTrack->setVolume(volume);	}	
void MusicPlayer::SetPan(float pan)					  { if(pSoundTrack) pSoundTrack->setPan(pan);				}	
const char*MusicPlayer::GetTrackName()				  { return str.c_str();						}
unsigned int MusicPlayer::GetTrack()				  { return iTrackNum;						}	
unsigned int MusicPlayer::GetTracks()				  { return iTotalTracks;					}	
void MusicPlayer::CycleList(bool b)			          { bCycle = b; }
bool MusicPlayer::IsPlaying()									  
{
	if(pSoundTrack == 0) return false;
	return !pSoundTrack->isFinished();
}


char* Level_1_Music[]=
{
	"Sound/music/l1_track_0.ogg",
	"Sound/music/stop.ogg",
	"Sound/music/l1_track_1.ogg",
	"Sound/music/stop.ogg",
	"Sound/music/l1_track_2.ogg",
};

char* Level_2_Music[]=
{
	"Sound/music/l2_track_0.ogg",
	"Sound/music/stop.ogg",
	"Sound/music/l2_track_1.ogg",
	"Sound/music/stop.ogg",
	"Sound/music/l2_track_2.ogg",
	"Sound/music/stop.ogg",
	"Sound/music/l2_track_3.ogg",
};

char* KeyMusic[] =
{
	"Sound/music/reactor_2_main.ogg",
	"Sound/music/resolution.ogg",
	"Sound/music/warrior_reveal.ogg",
	"Sound/music/motivational_halo_jump.ogg",
	"Sound/music/pyrrhic_victory_orch.ogg",
	"Sound/music/rising spear.ogg",
};



MusicPlayer* LoadMusicPlayer(int i)
{
	MusicPlayer* ptr;
	extern ISoundEngine* sound_engine;
	switch(i)
	{
	case 1:	 ptr = new MusicPlayer(sound_engine,Level_1_Music,5); break;
	case 2:	 ptr = new MusicPlayer(sound_engine,Level_2_Music,6); break;
	default: ptr = new MusicPlayer(sound_engine,KeyMusic,6);
	}

  return ptr;		
}

