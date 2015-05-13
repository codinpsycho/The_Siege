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






#include <hge.h>
#include "sounds.h"
extern HGE* Engine;

const int TOTAL_EFFECTS = 68;
HEFFECT LoadSoundEffects[TOTAL_EFFECTS];


char* Effects[] = 
{
///////////////////////////////////////  Physics  ///////////// index
"Sound/physics/break_rock.wav",                                 // 0
"Sound/physics/break_wood.wav",									// 1			
"Sound/physics/grenade_hit.wav",								// 2		
"Sound/physics/hit_flesh.wav",									// 3
"sound/physics/hit_flesh2.wav",									// 4					
"sound/physics/hit_flesh3.wav",									// 5
"Sound/physics/hit_metal.wav",                                  // 6
"Sound/physics/hit_plastic.wav",								// 7
"Sound/physics/hit_rock.wav",									// 8
"Sound/physics/hit_wood.wav",									// 9		
"Sound/physics/hit_wood_melee.wav",								// 10
"Sound/physics/hit_box_melee.wav",								// 11
"Sound/physics/weapon_hit_ground.wav",							// 12
//////////////////////////////////////// Items /////////////////
"sound/items/ammo_pickup.wav",									// 13
"sound/items/medshot4.wav",										// 14	
"sound/items/wind.wav",											// 15
"sound/items/forest.wav",										// 16
///////////////////////////////////////  Weapons  //////////////
"sound/weapons/bullets_empty.wav",								// 17
"sound/weapons/pistol_fire.wav",								// 18	
"Sound/weapons/ass_fire.wav",									// 19
"sound/weapons/shotgun_fire.wav",								// 20
"sound/weapons/rocket_launcher.wav",							// 21	
"Sound/weapons/explosion.wav",									// 22
"sound/weapons/explosion_big.wav",								// 23
"sound/weapons/weapon_switch.wav",								// 24	

/////////////////////////////////////// Physics  ///////////////
"Sound/physics/hit_rock_melee.wav",								// 25
"Sound/physics/hit_coil.wav",									// 26
"Sound/physics/hit_coil_melee.wav",								// 27
"Sound/physics/break_coil.wav",									// 28

/////////////////////////////////////// Item     ///////////////
"sound/items/melee_al2.wav",									// 29
"sound/items/melee1.wav",										// 30
"sound/items/melee2.wav",										// 31

/////////////////////////////////////// Physics  ///////////////
"Sound/physics/player_hit_ground.wav",							// 32
"Sound/physics/break_wood_melee.wav",                           // 33 
"Sound/physics/break_rock_melee.wav",							// 34
/////////////////////////////////////// Voices   ///////////////
"Sound/Voices/die_alien1.wav",									// 35				
"Sound/Voices/die_alien2.wav",									// 36		
"Sound/Voices/die_alien3.wav",									// 37
"Sound/Voices/player_death_1.mp2",								// 38
"Sound/Voices/player_death_2.mp2",								// 39 
"Sound/Voices/player_effort_grenade.mp2",						// 40
"Sound/Voices/player_effort_jump.mp2",							// 41	
"Sound/Voices/player_pain.mp2",								    // 42
"Sound/physics/player_on_object.wav",							// 43
"Sound/physics/break_coil_melee.wav",							// 44
"sound/items/melee_miss.wav",									// 45
"sound/items/null.wav",										    // 46
"Sound/physics/damage_box.wav",				     				// 47
"sound/items/bird1.wav",										// 48
"sound/items/bird2.wav",										// 49
"Sound/weapons/npc_ass_fire.wav",								// 50
"sound/items/wind.wav",										    // 51
"sound/music/alien_stinger_1.ogg",								// 52
"sound/music/player_stinger_1.ogg",								// 53
"sound/music/player_stinger_2.ogg",								// 54
"Sound/Dialogs/Protagonist/what the hell fast.mp2",				// 55	
"Sound/Dialogs/Protagonist/what the hell slow.mp2",				// 56
"Sound/Dialogs/Protagonist/what the fuh.mp2",					// 57
"Sound/Dialogs/Protagonist/oh shit.mp2",						// 58
"Sound/Dialogs/Protagonist/damn it angry.mp2",					// 59
"Sound/Dialogs/Protagonist/damn it very angry.mp2",				// 60
"sound/music/primordium_stinger.ogg",							// 61
"sound/music/panflute_2.ogg",									// 62
"sound/music/panflute_8.ogg",									// 63	
"Sound/Voices/death_prophet.mp2",							    // 64
"Sound/Voices/death_jester.mp2",								// 65
"Sound/Voices/death_psycho.mp2",								// 66
"Sound/Dialogs/Protagonist/roger that.mp2",						// 67
};


void LoadEffects(HGE* Engine)
{	
  for( int i=0; i < TOTAL_EFFECTS; ++i )
  {
	 LoadSoundEffects[i] = Engine->Effect_Load( Effects[i] );	
	 if( !LoadSoundEffects[i] )  
		 MessageBox(0,Effects[i], "File Missing...",MB_OKCANCEL);
  }	
}

void ReleaseEffects(HGE* Engine)
{
	for( int i=0; i < TOTAL_EFFECTS; ++i )	 Engine->Effect_Free( LoadSoundEffects[i] );	
}




SoundInfo PlaySoundEffect(eSOUNDEFFECTS EFFECT, int pan, bool loop )
{
 	int index=0; int vol;
    
	  switch(EFFECT)
	  {
	    case HIT_ROCK:    index=8; vol=15;  break;
		case HIT_WOOD:    index=9; vol=15;  break;
		case HIT_COIL:    index=26; vol=15; break;
		case HIT_METAL:   index=6; vol=15;  break; 
		case BREAK_WOOD:  index=1; vol=30;  break; 
		case BREAK_ROCK:  index=0; vol=30;  break;
		case BREAK_COIL:  index=28; vol=30;     break;
		case MELEE_WOOD_BOX:  index=10; vol=30; break;
		case MELEE_STEEL_BOX: index=11; vol=30; break;
		case MELEE_ROCK:	  index=25; vol=30; break;
		case MELEE_COIL:	  index=27; vol=30; break;
		case GRENADE_EXPLOSION:    index=23; vol=50; break;
		case LAUNCHER_EXPLOSION:   index=22; vol=70; break;
		case ROCKET_LAUNCHER:      index=21; vol=70; break;
		case MELEE_AZTEC_1:        index=30; vol=40; break;
		case MELEE_AZTEC_2:        index=31; vol=40; break;
		case MELEE_ALIEN2:         index=29; vol=40; break;
		case DIE_ALIEN1:           index=35; vol=15; break;		   		
		case DIE_ALIEN2:		   index=36; vol=15; break;			
		case DIE_ALIEN3:		   index=37; vol=15; break;	
		case FIRE_ASSAULT_RIFLE:   index=19; vol=15; break; 
		case FIRE_PISTOL:          index=18; vol=15; break;
		case FIRE_SHOTGUN:         index=20; vol=20; break;
		case SWITCH_WEAPON:        index=24; vol=50; break;
		case PICK_AMMO:            index=13; vol=50; break;
		case PICK_HEALTH:		   index=14; vol=50; break;
		case HIT_FLESH_HUMAN:      index=3;  vol=50; break; 
		case HIT_FLESH_ALIEN:      index=4;  vol=50; break; 
		case DROP_WEAPON:          index=12; vol=50; break;
		case GRENADE_BOUNCE:       index=2;  vol=70; break;
		case PLAYER_HITS_GROUND:   index=32;  vol=70; break;
		case BREAK_WOOD_MELEE:      index=33;  vol=30; break; 
		case BREAK_ROCK_MELEE:      index=34;  vol=30; break;
		case PLAYER_DEATH_LONG:     index=38;  vol=60; break;
		case PLAYER_DEATH_SHORT:    index=39;  vol=60; break;
		case PLAYER_THROW_GRENADE:  index=40;  vol=100; break;
		case PLAYER_JUMP:			index=41;  vol=100; break;				
		case PLAYER_PAIN: 		    index=42;  vol=100; break;
		case WEAPON_EMPTY:          index=17;  vol=40; break; 
		case PLAYER_HITS_OBJECT:    index=43;  vol=50; break;
		case BREAK_COIL_MELEE:      index=44;  vol=30; break;
		case MELEE_MISS:			index=45;  vol=50; break;
		case NULL_SOUND:			index=46;  vol=10; break;
		case DAMAGE_BOX:			index=47;  vol=45; break;
		case BIRD_CHIRRUP1:         index=48;  vol=50; break;
		case BIRD_CHIRRUP2:         index=49;  vol=50; break;  
		case NPC_ASSAULT_FIRE:      index=50;  vol=12; break;   
		case WIND:					index=51;  vol=50; break;
		case STINGER_1:				index=52;  vol=50; break;
		case STINGER_2:				index=53;  vol=90; break;
		case STINGER_3:				index=54;  vol=90; break;
		case WHAT_THE_HELL_FAST:	index=55;  vol=90; break;
		case WHAT_THE_HELL_SLOW:    index=56;  vol=100; break;
		case WHAT_THE_FUH:			index=57;  vol=90; break;
		case OH_SHIT:				index=58;  vol=90; break;
		case DAMN_IT_NORMAL:		index=59;  vol=90; break;	
		case DAMN_IT_ANGRY:			index=60;  vol=90; break;
		case PRIMORDIUM_STINGER:    index=61;  vol=90; break;
		case FLUTE_STINGER_1:	    index=62;  vol=90; break;
		case FLUTE_STINGER_2:		index=63;  vol=90; break;
		case DEATH_PROPHET:			index=64;  vol=90; break;
		case DEATH_JESTER:			index=65;  vol=90; break;
		case DEATH_PSYCHO:			index=66;  vol=90; break;
		case ROGER_THAT:			index=67;  vol=90; break;
	  }

return SoundInfo(LoadSoundEffects[index],vol,loop);
}