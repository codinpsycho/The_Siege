#ifndef _SOUND_EFFECTS_H_
#define _SOUND_EFFECTS_H_

#include <vector>
#include <hge.h>
using std::vector;

enum eSOUNDEFFECTS
{
	HIT_ROCK,  
	HIT_WOOD,  
	HIT_COIL,  
	HIT_METAL, 
	BREAK_WOOD,
	BREAK_ROCK,
	BREAK_COIL,
	MELEE_WOOD_BOX, 
	MELEE_STEEL_BOX, 
	MELEE_ROCK, 
	MELEE_COIL,
	GRENADE_EXPLOSION,
	LAUNCHER_EXPLOSION, 
	ROCKET_LAUNCHER, 
	MELEE_AZTEC_1,
	MELEE_AZTEC_2, 
	MELEE_ALIEN2,
	DIE_ALIEN1,
	DIE_ALIEN2,
	DIE_ALIEN3, 
	FIRE_ASSAULT_RIFLE,
	FIRE_PISTOL, 
	FIRE_SHOTGUN, 
	SWITCH_WEAPON, 
	PICK_AMMO,
	PICK_HEALTH, 
	HIT_FLESH_HUMAN, 
	HIT_FLESH_ALIEN, 
	DROP_WEAPON,
	GRENADE_BOUNCE,
	PLAYER_HITS_GROUND,
	BREAK_WOOD_MELEE,
	BREAK_ROCK_MELEE,
	PLAYER_DEATH_LONG,
	PLAYER_DEATH_SHORT,
	PLAYER_THROW_GRENADE,
	PLAYER_JUMP,
	PLAYER_PAIN, 	
	MELEE_MISS,
	MAXIMUM_GAME,
	WEAPON_EMPTY,
	PLAYER_HITS_OBJECT,
	BREAK_COIL_MELEE,
	NULL_SOUND,
	DAMAGE_BOX,
	BIRD_CHIRRUP1,
	BIRD_CHIRRUP2,
	NPC_ASSAULT_FIRE,
	WIND,
	STINGER_1,
	STINGER_2,
	STINGER_3,
	WHAT_THE_HELL_FAST,
	WHAT_THE_HELL_SLOW,
	WHAT_THE_FUH,
	OH_SHIT,
	DAMN_IT_NORMAL,
	DAMN_IT_ANGRY,
	PRIMORDIUM_STINGER,
	FLUTE_STINGER_1,
	FLUTE_STINGER_2,
	DEATH_PROPHET,
	DEATH_JESTER,
	DEATH_PSYCHO,
	ROGER_THAT,
};


struct SoundInfo
{
public:
  HEFFECT hEffect;	
  eSOUNDEFFECTS eType;	
  int iVolume;
  int iPan;
  bool bLoop;
  SoundInfo(HEFFECT hEff , int vol=100, bool loop = false)   {   hEffect = hEff; iVolume = vol; bLoop = loop;  }
};


SoundInfo PlaySoundEffect(eSOUNDEFFECTS EFFECT, int pan = 0 , bool loop= false);
/*
void ProcessSound(vector <SoundInfo> &EffectsList, HGE* Engine)
{
	for(unsigned int i=0; i<EffectsList.size(); i++)
	{
		Engine->Effect_PlayEx( EffectsList[i].hEffect ,EffectsList[i].iVolume );
	}
	while(!EffectsList.empty()) EffectsList.pop_back();
}
*/
#endif