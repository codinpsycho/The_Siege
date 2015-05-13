#pragma once
#ifndef __SND_SYS_TEM_H_
#define __SND_SYS_TEM_H_

#include <irrklang.h>
#include <string>

using namespace irrklang;
class MusicPlayer
{ 			 
public: 
	MusicPlayer::MusicPlayer( ISoundEngine* Ptr, char** lst=0, unsigned int trks=0 );
   ~MusicPlayer(void);
    void LoadPlayList( char** lst, unsigned int trks );
	void PlayList();
	void PlayTrack(unsigned int pt,bool lop = false);
	void Play(const char* str,bool lop = false);
	void Pause();
	void Resume();
	void Stop();
	void RaiseVolume();
	void LowerVolume();
	void Loop(bool);
	
	bool IsFinished(); 
	unsigned int GetPlayLength();
	unsigned int GetPlayPosition();
	void SetPlayPosition( unsigned int );
	float GetVolume();
	float GetPan();
	void SetPan(float);
	void SetVolume(float);	
	const char*GetTrackName();
	unsigned int GetTrack();
	unsigned int GetTracks();
	void SetNext(unsigned int);
	void SetTrack(unsigned int n);
	void CycleList(bool);
	bool IsPlaying();
private:
	//if a list is to be played 
	bool bPlayList;
	unsigned int iTrackNum,iTotalTracks,nextTrack;
    char** List;
	bool bCycle;
	
	std::string str;
	float volume;
	ISound* pSoundTrack; 
	ISoundEngine* engine;	
};  



#endif



