#ifndef  _DIALOG_H_
#define  _DIALOG_H_
#pragma once

#include <string>
#include <hge.h>

enum eVOICE_TYPE
{
  VOICE_TYPE_1,
  VOICE_TYPE_2,
  VOICE_TYPE_3,
  VOICE_TYPE_4
};

enum eDIALOG_CONTEXT
{
	COMMAND,
	TAUNT,
	REQUEST,
	WARN,
	COMPROMISE,
	DEATH,
	MELEE_DEATH,
	STATUS,
	SAY_NOTHING,
};

struct InfoDialog
{
	HEFFECT hDialog;
	eDIALOG_CONTEXT eContext;
	InfoDialog()									 {     hDialog=0; eContext=SAY_NOTHING;		}
	InfoDialog(HEFFECT hEff, eDIALOG_CONTEXT con)    {	   hDialog = hEff;  eContext = con; 	}
};

class Dialog
{
public:
	 Dialog(void);
	~Dialog(void);

	 void LoadDialogs(const char* str1, const char* str2[], HGE* Engine ); 
	 void Release(HGE* Engine);
     HEFFECT Speak(eDIALOG_CONTEXT);

enum {SIZE=23};
HTEXTURE hDialogs[SIZE];
std::string directory;
};


void LoadVoices(HGE* Engine);
void ReleaseVoices(HGE* Engine);

#endif