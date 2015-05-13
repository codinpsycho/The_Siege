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


#include "StateLevel1.h"
#include <hge.h>
#include "StateGamePaused.h"
#include "GameStateManager.h"
#include <hgefont.h>
#include <hgegui.h>
#include "TileMap.h"
#include "sprite.h"
#include "Timer.h"
#include "Protagonist.h"
#include "LevelObjects.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <hgeparticle.h>
#include "sounds.h"
#include "MusicPlayer.h"
#include "TileMap2.h"
#include <fstream>
const int SIZEOBJTOO = 38; 
IDFIRST LoadTheseObjectsToo[SIZEOBJTOO] = 
{
	TREE_DESTROYED,TREE_DESTROYED, SMALLGRASS,SMALLGRASS,ROCKS,LARGE_GRASS,LARGE_GRASS,LARGE_GRASS,LARGE_GRASS,GRAVELS,GRAVELS,GRAVELS,ROCKS,ROCKS,MEDIUM_GRASS,MEDIUM_GRASS,BUSHES,SMALLGRASS,SMALLGRASS,
	GRAVELS,TREE,TREE,TREE,TREE,TREE_DESTROYED,TREE_DESTROYED,TREE_DESTROYED,TREE_DESTROYED,TREE,TREE,TREE,TREE,BUSH,BUSH,BUSH,CAR,BUSHES,MEDIUM_GRASS 
};

enum eScores;
float speakerX=50.0f,speakerY=670.0f;
/////Structure declaration for Score
struct ScoreUp;
/////////////////// Function Prototypes ////////////////////////////////////////////////////////////////////////////////////////////
void ManageParticleList( vector<hgeParticleSystem*> &ParticleList );
void RenderLeaves( vector<Leaf> &Leaves );
void UpdateLeaves( vector<Leaf> &Leaves );
void CreateEffect( Bullet* bul, LevelObjects &Box, std::vector< hgeParticleSystem* > &ParticleList );
void CreateEffect( Bullet* bul, std::vector< hgeParticleSystem* > &ParticleList );
void CreateEffect( Protagonist* Aztec,std::vector< hgeParticleSystem* > &ParticleList, eParticles id = JUMP_DUST, Enemy* enm = 0);
void AddLeaf( vector<Leaf> &Leaves );
void UpdateCloud(vector<Cloud> &Clouds, float dt);
void RenderCloud(vector<Cloud> &Clouds);
hgeParticleSystem* ParticleFactory(eParticles id, float x, float y, int direction);
Bullet* createBullet( Protagonist* masterChief, HTEXTURE hTex, HGE* Engine,std::vector< Bullet* > &vInGameBullets );
void Move( std::vector<Bullet*> &Bul, float dt, HGE* );
void AddBird(std::vector<Bird> &Birds, int type);
void UpdateBirds(std::vector<Bird> &Birds, float dt);
void RenderBirds(std::vector<Bird> Birds);
bool JumpAndCollision(float dt, const int GROUND );      // Jump And Object
bool checkBulletCollision(std::vector<LevelObjects>&);  // check all the bullets in the scene
bool MovePlayerOnEarth( float dt );								   // Move Player Left or Right
void ManageEnemy(float dt, int level,Protagonist*);				   // manage Enemies;
bool checkBulletCollision(std::vector<Enemy*>&);
void RenderHUD();
void UpdateHUD();
void GenerateBonus(LevelObjects&Lov, const int i);
Bullet* createEnemyBullet(Enemy* enemy, HTEXTURE hTex, HGE* Engine,std::vector< Bullet* > &vInGameBullets);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T > void PopList(std::vector< T >  &List);
void EffectOfExplosionOnEnemies(const float, const int );
void EffectOfExplosionOnProtagonist( const float center, const int BlastRadius );
void ProcessSound(vector <SoundInfo> &EffectsList);
template<class T>  
void RenderObjects(std::vector<T*> &Bul);
void MaintainGrenades(std::vector< Grenade*> &GrenadeList);
bool HorizontalCollisionDetection( Protagonist &Pro, LevelObjects &BoxObject );
inline bool VerticalCollisionDetection( Protagonist &Pro, LevelObjects &BoxObject, float );
void GiveWeapon( Enemy* enm );
WeaponObject* createWeaponObject( eWEAPONS wId,int x, int y );
Grenade* createGrenade( Protagonist* Azt, HTEXTURE hTex );
void MoveGrenade( Grenade* grenade, float dt, const int );
void checkExistance();
void BulletCollisionPro(  );
MusicPlayer* LoadMusicPlayer(int i);
void InitHud();
void ReleaseHud();
void RenderHud();
void AddScore(hgeVector _position, char* _score, enum eScores);
void UpdateScores(vector<ScoreUp> &vScores);
void RenderScores();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////Global variables for Scoring
extern int Total_Score,Total_kills;
extern  int Birds_killed, hits_sustained, Box_destroyed,Melees, Bullets_Wasted;

/////////////////////////////////////
//Extern Game Engine Pointer and Game State Manager
extern GameStateManager *Manager ;
extern HGE *Engine;
extern ISoundEngine* sound_engine;
// constants
const int SCREENWIDTH = 1366;     
const int SCREENHEIGHT = 768;

////Tile Map Objects
TileMap *GrassSprite;
TileMap *BoxSprite;
TileMap *MixSprite;
// Particle Effect Variables
hgeParticleSystem * NewParticleEffect;
hgeSprite *ParSprite,*blastSprite=0,*GrenadeBlastSprite=0;
hgeSprite *GunSparkSprite;
hgeSprite *FireHitSprite;
hgeSprite *FeatherSprite;

hgeSprite *Health;
hgeSprite *CurWeapon;
hgeSprite *LostShip;
hgeSprite *SolarGun;
hgeFont *font;

Protagonist *Jester=0, *Psycho=0, *Prophet=0;

// layers
 sprite sky(0,0,SCREENWIDTH,615);
 sprite mountains(0,462,SCREENWIDTH,153);
 sprite ground1(0,615,256,219);
 sprite grass(0,715,425,96);

const int xPos = 30;  //Starting Position for Tile Map Objects
float fAlpha;
bool bShowInfo = true;  
bool paused = false;
Timer Spawn(1000);

// texture

HTEXTURE healthTex;
HTEXTURE DamageBoxTex;
HTEXTURE groundtex ;
HTEXTURE boxtex;
HTEXTURE mixtex;
HTEXTURE cur;
HTEXTURE rest;
HTEXTURE res;
HTEXTURE ex;
HTEXTURE hTexEnemy;
HTEXTURE hTexBullets;
HTEXTURE ParTex;
HTEXTURE GunSparkTex;
HTEXTURE FireHitTex;
HTEXTURE hLeafTex;
HTEXTURE blast;
HTEXTURE texBirds;
HTEXTURE cloud;
HTEXTURE Objects;
HTEXTURE LStex;
HTEXTURE hCallOutTex;
HTEXTURE hSpeakerTex;
HTEXTURE hLevelOneTex;
HTEXTURE SpriteSheetObj2;
HTEXTURE L1_SkyTex,L1_GroundTex,L1_MountsTex,PauseMenuTex;
HTEXTURE Fallingtex,Feathertex;


hgeSprite *LevelOneSpr,*PauseMenuSpr;
char*pStrTexEnemy = "Sprites\\Enemy.png";
char*pStrBullets = "Sprites\\SiegeObjects.png";  // thats where bullets are found

//////////////////////////////////// Variables Globally Used Variables
hgeSprite *CallOutSpr = 0;
hgeSprite *sprGrenade;
// Aztec - protagonist 
Protagonist *Aztec = 0;
const float GROUND = 620.0f;  // the height of ground 
const float GRAVITY = 0.20f;
static float EscapeVelocity = 0.0f; 
float fDistanceCovered;
MusicPlayer *KeyMusicPlayer,*GameLevelMusic;
int EnemyCounterEnding; // this counts the number of enemies generated in the end of this level
static bool flagPlay = true; 
/////////////////////////////////////////// Flags
bool RightSideCollision = false;
bool LeftSideCollision  = false;
bool HorizontalCollision = false;
bool VerticalCollision   = false;
bool WeaponCollision = false;
bool grenadeflag = false;
bool bMeleeFlag = false;
bool bDisplayBonusMessage=false;
bool bActivateShotgun = false;
bool bActivateLauncher = false;
bool bAwareSquadFlag = false;
bool bProphetTransmission = false;
static bool GOD_MODE_FLAG = false;
CONDITION PLAYERSTATUS = ON_THE_GROUND;
HTEXTURE hDeadAzztecTex,hDeadEnemiesTex;
Enemy* pSpecialEnemy=0;
Grenade* pSpecialGrenade=0;

/////////////////////////////////////////////////
//float center;
bool bEnding, bMove, bLostShipPassed;
float LSX ;
float fBoundX;
bool bGameOver;
Timer GameOver(1500),HoldOn(15000);
/////////////////////////////////////////////////

//std::vector< Enemy*  > vIdleStateEnemies;
std::vector< Enemy*  > pDeadBodies;        // list of pointers to dead bodies of enemies 
std::vector< Enemy*  > pGameEnemyList;     // list of pointers to enemy
std::vector< Bullet* > vInGameBullets;     // list of pointers to bullets
std::vector< WeaponObject* > vWeaponList;  // list of weapon objects to be rendered
std::vector<Grenade*> GrenadeList;
std::vector< hgeParticleSystem* > ParticleList; // list of particle effects in the scene
std::vector< hgeParticleSystem* > LauncherEffectParticleList; 
vector< Leaf > Leaves;
std::vector<Cloud> vClouds;
std::vector<Bonus*> vBonus;
std::vector<Bird> vBirds;
std::vector<ObjectLevel*> vListOfObjects;
vector <SoundInfo> SoundEffectsList;
vector <InfoDialog> EnemyDialogsList;
vector<ObjectLevel*> ObjLevList;	
vector<ScoreUp> vScores;
static MusicPlayer *DialogLevelOne;
static int iLevelOneEvents=0;

StateLevel1::StateLevel1(void)
{

}

StateLevel1::~StateLevel1(void)
{

}

#define SIEGE_LEVEL_1 1 
float fAngleSpeaker=0;
int THIS_IS_LEVEL_NUMBER = 0;
extern bool LevelStartFlag ;

static char* Diags_Misc[]=
{
	"Sound/Dialogs/Level 1/prophet.mp3",
	"Sound/Dialogs/Level 1/nomad.mp2",
	"Sound/Dialogs/Level 1/major_0.mp2",
	"Sound/Dialogs/Level 1/prophet is gone.mp3",
	"Sound/Dialogs/Level 1/major_1.mp2",
	"Sound/Dialogs/Level 1/major_2.mp2",
};

static char* str[] = 
{
 "Sound/Dialogs/Level 1/island_0.mp3",
 "Sound/Dialogs/Level 1/island_1.mp3",
 "Sound/Dialogs/Level 1/island_2.mp3"
};

char* conv_level_end[]=
{
	"Sound/Dialogs/Protagonist/what the hell slow.mp2",	// 0
	"Sound/Dialogs/Level 1/end_com_0.mp2",// 1
	"Sound/Dialogs/Level 1/end_com_1.mp2",// 2
	"Sound/Dialogs/Level 1/end_com_2.mp2",// 3
	"Sound/Dialogs/Level 1/end_com_3.mp2",// 4
	"Sound/Dialogs/Level 1/end_com_4.mp2",// 5
	"Sound/Dialogs/Level 1/end_com_5.mp2",// 6
	"Sound/Dialogs/Level 1/end_com_6.mp2",// 7
	"Sound/Dialogs/Level 1/end_com_7.mp2",// 8
	"Sound/Dialogs/Level 1/end_com_8.mp2",// 9
	"Sound/Dialogs/Level 1/end_com_9.mp2",// 10
	"Sound/Dialogs/Level 1/end_com_10.mp2",// 11
	"Sound/Dialogs/Level 1/end_com_11.mp3",// 12
	"Sound/Dialogs/Level 1/end_com_12.mp2",// 13
	"Sound/Dialogs/Level 1/end_com_13.mp3",// 14
	"Sound/Dialogs/Level 1/end_com_14.mp2",// 15
	"Sound/Dialogs/Level 1/end_com_15.mp2",// 16
};

char* finale[]=
{
	"Sound/Dialogs/Level 1/final_0.mp2", // 0
	"Sound/Dialogs/Level 1/final_1.mp2", // 1
	"Sound/Dialogs/Level 1/final_2.mp2", // 2
	"Sound/Dialogs/Level 1/split.mp3",   // 3
	"Sound/Dialogs/Level 1/final_3.mp2", // 4 
	"Sound/Dialogs/Level 1/final_4.mp2", // 5
};

char *newyork[] = 
{
	"sound/music/panflute_2.ogg",
	"sound/music/epic.mp3",
};

static bool bAztecIsSpeaking = false;
static hgeSprite *AztecSpeaks = 0, *DeadAzztec=0,*DeadEnemies=0;
Protagonist *ptrPro[3];



static Timer DeathTimer(2000);
//static bool GoToGameOverState = false;

bool StateLevel1::Init()
{	
	THIS_IS_LEVEL_NUMBER = SIEGE_LEVEL_1;
	#undef SIEGE_LEVEL_1;
	GameOver.reset();
	fBoundX = 350.0f;
	LSX = 1400.0f;
	fDistanceCovered = 0.0f;
	fAlpha = 255;
	fAngleSpeaker=0;
	bActivateShotgun = false;
	bActivateLauncher = false;
	bGameOver = false;
	bEnding = false;
	bMove = true;
	bShowInfo = true;
	flagPlay = true;
	bProphetTransmission =  false;
	bLostShipPassed = false;
	bAwareSquadFlag = false;
	bDisplayBonusMessage = false;
	EnemyCounterEnding=0; 
	pSpecialEnemy=0;
	pSpecialGrenade=0;
	iLevelOneEvents=0;

	//Initializes scoring variables
	Total_kills = Total_Score = Birds_killed = hits_sustained = Box_destroyed = Melees = 0;
	//////////////

	//Loads Level1 Objects Sprite Sheets and all Textures
    HoldOn.setstart();
///////////////////////////////////////////////////////////////////////////////////////
	hTexEnemy = Engine->Texture_Load(pStrTexEnemy);
	hTexBullets = Engine->Texture_Load(pStrBullets);
	/////Sprite sheet for falling birds
	Fallingtex = Engine->Texture_Load("sprites/falling.png");
	///////
	healthTex = Engine->Texture_Load("Textures/Level1/health.png");
///////////////////////////////////////////////////////////////////////////////////////

	// level-1  specifics
	LStex = Engine->Texture_Load("Textures/Level1/LostShip.png");
	groundtex = Engine->Texture_Load("Textures/Level1/grassprite.png");
	   boxtex = Engine->Texture_Load("Textures/Level1/boxesprite.png");
	   mixtex = Engine->Texture_Load("Textures/Level1/mixsprite.png");

		
		
		L1_GroundTex = Engine->Texture_Load("Textures/Level1/ground2.png");
		L1_MountsTex = Engine->Texture_Load("Textures/Level1/backmountains.png");
		L1_SkyTex = Engine->Texture_Load("Textures/Level1/sky6.png");

		ground1.LoadTexture(L1_GroundTex);
		mountains.LoadTexture(L1_MountsTex);
		sky.LoadTexture(L1_SkyTex);

		cloud = Engine->Texture_Load("Textures/Level1/cloud.png");
		SpriteSheetObj2 = Engine->Texture_Load("Sprites/SiegeObjects2.png");
		hSpeakerTex = Engine->Texture_Load("Sprites/speaker.png");
		if(!hSpeakerTex)  MessageBox(0,"/Sprites/speaker.png","File Not Found",MB_OK);
////////////////////////////////////////////////////////////////////////////////////////////////
		  cur = Engine->Texture_Load("Textures/Game Paused/cur1.png");
		 rest = Engine->Texture_Load("Textures/Game Paused/Restart.png");
		  res = Engine->Texture_Load("Textures/Game Paused/resume.png");
		   ex = Engine->Texture_Load("Textures/Game Paused/exit.png");
 DamageBoxTex = Engine->Texture_Load("Textures/Level1/damagebox.png");
  hCallOutTex = Engine->Texture_Load("Textures/Level1/callout.png");
		Feathertex = Engine->Texture_Load("Particle Effects/feather.png");
	   ParTex = Engine->Texture_Load("Particle Effects/particles.png");
  GunSparkTex = Engine->Texture_Load("Particle Effects/particles.png");
   FireHitTex = Engine->Texture_Load("Particle Effects/particles.png");
     hLeafTex = Engine->Texture_Load("Textures/Level1/leaf.png");
	    
	
      Objects = Engine->Texture_Load("Textures/Level1/level1obj.png");
        blast = Engine->Texture_Load("Sprites/particles.png");
	  texBirds = Engine->Texture_Load("Sprites/bird.png");
	  hLevelOneTex = Engine->Texture_Load("Textures/Level1/level1.png");	
	    hDeadAzztecTex = Engine->Texture_Load("Textures/Level1/deadaztec.png");
		hDeadEnemiesTex = Engine->Texture_Load("Textures/Level1/deadenemies.png");
		PauseMenuTex = Engine->Texture_Load("Textures/Game Paused/blur.png");	
////////////////////////////////////////////////////////////////////////////////////////////////
	 
//////////INIT Lost Ship and hud
		/// level 1	  
	  //Init Sprites needed for Particle Effects 
	  PauseMenuSpr = new hgeSprite (PauseMenuTex,0,0,1366,768);
	  font = new hgeFont("Fonts/font.fnt");	//Init Font
	  ParSprite = new hgeSprite(ParTex,0,96,32,32);
	  GunSparkSprite = new hgeSprite(GunSparkTex,64,64,32,32);
	  FireHitSprite = new hgeSprite(FireHitTex,64,64,32,32);
		
		
	  DeadAzztec = new hgeSprite(hDeadAzztecTex,0,0,114,32 );
	  DeadEnemies = new hgeSprite(hDeadEnemiesTex,0,0,256,52 );
	
	  ParSprite->SetHotSpot(16,16);
	  GunSparkSprite->SetBlendMode(BLEND_ALPHAADD );
	  FireHitSprite->SetBlendMode(BLEND_ALPHAADD);
	  
	  
	  /////////////////////////////////////////////
	  GUI = new hgeGUI();
	  //Sets Cursor
	  cursor = new hgeSprite(cur,0,0,32,32);
	  //Allocates memory to tile map pointers
	  GrassSprite = new TileMap();
	  MixSprite = new TileMap();
	  BoxSprite = new TileMap();
	  
	  LevelOneSpr = new hgeSprite(hLevelOneTex,0,0,1366.0f,768.0f);
	  LostShip    = new hgeSprite(LStex,0,0,800,232);
	  sprGrenade  = new hgeSprite(Objects,270,100,30,20);
	  Health	  = new hgeSprite(healthTex,0,0,20,20);
	  CurWeapon   = new hgeSprite(Objects,0,0,360,200);
	  SolarGun	  = new hgeSprite(hTexBullets,90,0,75,40);
	  blastSprite = new hgeSprite(blast,32,0,32,32);
	  GrenadeBlastSprite = new hgeSprite(blast,32,0,32,32);	 
	  CallOutSpr = new hgeSprite(hCallOutTex,0,0,158,46);
	  FeatherSprite = new hgeSprite(Feathertex,0,0,32,32);
	  AztecSpeaks = new hgeSprite( hSpeakerTex,0,0,80,75 );
	  
	  AztecSpeaks->SetHotSpot( AztecSpeaks->GetWidth()/2 , AztecSpeaks->GetHeight()/2 );
	

	  GrenadeBlastSprite->SetBlendMode(BLEND_ALPHAADD);
	  blastSprite->SetHotSpot(16,16);
	
	//Initializes Tile Map Objects
	  GrassSprite->Read("GrassTile.txt");
	GrassSprite->SetPos(xPos,720);
	GrassSprite->SetTileImage(groundtex);
	
	//Converts DATA into LevelObjects 
	GrassSprite->CreateLevel();
	BoxSprite->Read("BoxTile.txt");
	BoxSprite->SetPos(xPos,470);
	BoxSprite->SetTileImage(boxtex);
	
	//Converts DATA into LevelObjects 
	BoxSprite->CreateLevel();
	MixSprite->Read("MixTile.txt");
	MixSprite->SetTileImage(mixtex);
	MixSprite->SetPos(xPos,0);
	
	//Converts DATA into LevelObjects 
	MixSprite->CreateLevel();

	/////////////////////////////////////////////////////////////////////  set identity
	for (unsigned int i = 0 ; i < MixSprite->Objects.size() ; i++)
	{
		int id = MixSprite->Objects[i].GetId();

		switch (id)
		{
		case 1: MixSprite->Objects[i].SetId(5);
			break;
		case 2: MixSprite->Objects[i].SetId(6);
			break;
		case 3: MixSprite->Objects[i].SetId(7);
			break;
		case 4: MixSprite->Objects[i].SetId(8);
			break;
		}

	}

	//Init GUI  
	GUI->SetCursor(cursor);
	
	//Adds Buttons to Pause Menu
	GUI->AddCtrl(new Button(1,100,200,res,res,res));
	GUI->AddCtrl(new Button(2,100,240,rest,rest,rest));
	GUI->AddCtrl(new Button(3,70,280,ex,ex,ex));
	GUI->SetNavMode(HGEGUI_CYCLED | HGEGUI_UPDOWN);
	

	for(unsigned  h=0; h<MixSprite->Objects.size(); h++ )
	{
		if(MixSprite->Objects[h].GetId() == 7 || MixSprite->Objects[h].GetId() == 8)
			MixSprite->Objects[h].SetCollidable(false);
	}

	for(unsigned int h=0; h<BoxSprite->Objects.size(); h++ )
	{
		BoxSprite->Objects[h].SetCollidable(true);
	}
		
	
	//////  Initialization Required For Player
	for(int k=0; k<3; k++)
	{
		ptrPro[k] = new Protagonist;
		ptrPro[k]->Init(Engine);
		ptrPro[k]->vPosition.x = 20 +k*10 ;
		ptrPro[k]->vPosition.y = 480;
	}

	 Psycho = ptrPro[2];
	Prophet = ptrPro[1];
	 Jester = ptrPro[0];
		

	Aztec = new Protagonist;
	Aztec->Init(Engine);
	Aztec->vPosition.x = 20;
	Aztec->vPosition.y = 480;
	Aztec->ShotGun.SetAmmo( Aztec->ShotGun.GetAmmo() - 5 );
	Aztec->RocketLauncher.SetAmmo( Aztec->RocketLauncher.GetAmmo() - 5 );
	HorizontalCollision = false;
	VerticalCollision = false;
	EscapeVelocity = 0.0f;	
	PLAYERSTATUS=ON_THE_GROUND;
	RightSideCollision = false;
	LeftSideCollision  = false;
	WeaponCollision = false;
	grenadeflag = false;
	bMeleeFlag = false;
	
	
	if( !hTexBullets || !hTexEnemy ) 
		MessageBox(0,pStrBullets,"Error Loading Texture",MB_OK|MB_ICONERROR);

	for (unsigned int i = 0 ; i < BoxSprite->Objects.size() ; i++ )
	{
		switch (BoxSprite->Objects[i].GetId())
		{
		case 1: BoxSprite->Objects[i].SetHealth(100);
			break;
		case 2: BoxSprite->Objects[i].SetHealth(140);
			break;
		case 3: BoxSprite->Objects[i].SetHealth(180);
			break;
		case 4: BoxSprite->Objects[i].SetHealth(180);
			break;
		}

	}

	for (unsigned int i = 0 ; i < MixSprite->Objects.size() ; i++ )
	{
		switch (MixSprite->Objects[i].GetId())
		{
		case 5: MixSprite->Objects[i].SetHealth(230);
			break;
		case 6: MixSprite->Objects[i].SetHealth(210);
			break;

		}
	}

	LoadObjects(vListOfObjects,LoadTheseObjectsToo,47,GROUND,SpriteSheetObj2);
	
	DialogLevelOne = 0;
	KeyMusicPlayer = LoadMusicPlayer(1010);
	GameLevelMusic =  LoadMusicPlayer(1);
	InitHud();
	iLevelOneEvents=0;
	GOD_MODE_FLAG = false;	
	//GoToGameOverState = false;

	return true;
}

void ManageTileMapping(); 
void ProcessBonus(); 
void GenerateItems()
{
	float x1 = LSX + LostShip->GetWidth();

	ptrPro[2]->vPosition.x = x1-250;
	ptrPro[1]->vPosition.x = x1+250;	
	ptrPro[0]->vPosition.x = x1-100;


	Psycho->SetFacing(FACERIGHT,true);
	Prophet->SetFacing(FACELEFT,true);
	Jester->SetFacing(FACELEFT,true);

	ptrPro[0]->vPosition.y = ptrPro[1]->vPosition.y = ptrPro[2]->vPosition.y = 480;


	Bonus* arrBon[9] = 
	{
		new Bonus(AMMO_SHOTGUN,hgeVector (x1-200,GROUND-17.0f) ),
		new Bonus(AMMO_LAUNCHER,hgeVector (x1,GROUND-17.0f) ),
		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1-400,GROUND-17.0f) ),
		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1-500,GROUND-17.0f) ),
		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1-600,GROUND-17.0f) ),
		new Bonus(AMMO_GRENADE,hgeVector (x1+200,GROUND-10.0f) ),
		new Bonus(AMMO_GRENADE,hgeVector (x1+230,GROUND-10.0f) ),
		new Bonus(MEDIKIT,hgeVector (x1-300,GROUND-17.0f) ),
		new Bonus(MEDIKIT,hgeVector (x1-250,GROUND-17.0f) )
	};

	for(int i=0; i<9; i++)
		arrBon[i]->Init(hTexBullets);

	for(int l=0; l<9; l++)
		vBonus.push_back(arrBon[l]);


}


////////////////////////////////////////////////////////////// UPDATE FUNCTION
bool UpdateScene(float dt);

bool StateLevel1::Update(float dt)
{
 	if( fAngleSpeaker > 7000000000.0f && !bAztecIsSpeaking ) fAngleSpeaker = 0.0f; 	else if(bAztecIsSpeaking) 
 		fAngleSpeaker+=0.05f;
 
 	if(iLevelOneEvents < 11)
 	if (Engine->Input_KeyDown(HGEK_ESCAPE))
 	{
 		if (!paused)  
 		{ 
 			paused = true; 
 			Engine->Channel_PauseAll(); 
 			if(KeyMusicPlayer)
 			{
 			 KeyMusicPlayer->PlayTrack(5,true);
 			 KeyMusicPlayer->SetVolume(0.75);
 			 }
 			if(GameLevelMusic) GameLevelMusic->Pause();
			if(DialogLevelOne) DialogLevelOne->Pause();
 		}
 		else 
 		{ 
 			paused = false;  
 			KeyMusicPlayer->Stop();
 			Engine->Channel_ResumeAll(); 
 			if(DialogLevelOne) DialogLevelOne->Resume();
 			if(GameLevelMusic) GameLevelMusic->Resume();
 		}
 	}
 	if (paused)
 	{	
 		int id = GUI->Update(dt);				// Updates GUI
 
 		if (id == 1)      
 		{ 
 			paused = false;	
 			Engine->Channel_ResumeAll();      
 			KeyMusicPlayer->Stop();	
 			if(DialogLevelOne) DialogLevelOne->Resume();
 			if(GameLevelMusic) GameLevelMusic->Resume();
 		}
 		else if (id == 2)  
 		{ 
 			paused = false;   
 			Engine->Channel_ResumeAll();      
 			Manager->SetState(STATE_LEVEL1);   
 		}
 		else if (id == 3)  
 		{ 
 			paused = false;   
 			Engine->Channel_ResumeAll();      
 			Manager->SetState(STATE_MENU);	 
 		}
 
 	}
 	else    // all of the Game Logic here
 	{
 		void ProcessLevelOneEvents();
 
 		ProcessLevelOneEvents();
 
 		if( iLevelOneEvents < 5 && GameLevelMusic)
 		{
 			if( GameLevelMusic->GetVolume() > 0.40f )
 			{
 				GameLevelMusic->SetVolume(0.33f);
 			}
 		}
 
 
		if(iLevelOneEvents == 11)	
 		{
 			if( Engine->Input_GetKey() == HGEK_ESCAPE || Engine->Input_GetKey() == HGEK_ENTER ) 
 			{ 
 				Manager->SetState(STATE_LEVEL2); 
 			}
 			return false;
 		}
 		else
 		if(iLevelOneEvents == 1 || iLevelOneEvents == 2)
 		{
 			UpdateScene(dt);
 			return false;
 		}
 		else 
 			if(iLevelOneEvents == 3)
 			{
 				return false;
 			}
 			else 
 				if ( iLevelOneEvents == 5 )
 				{
 					void UpdateDeltaForce(float dt);
 					UpdateDeltaForce(dt);
 					if(GameLevelMusic){	GameLevelMusic->PlayList();	if(GameLevelMusic->IsFinished()) { delete GameLevelMusic; GameLevelMusic=0; } }
 				}
 				else 
 					if ( iLevelOneEvents == 6 )
 					{
 							void UpdateDeltaForce(float dt);
 							 UpdateDeltaForce(dt);
 
 					if(GameLevelMusic){	GameLevelMusic->PlayList();	if(GameLevelMusic->IsFinished()) { delete GameLevelMusic; GameLevelMusic=0; } }	
 
 							if(DialogLevelOne)
 							{
 									DialogLevelOne->PlayList();
 
 									if( DialogLevelOne->IsPlaying() )
									{
 										bAztecIsSpeaking = true;
 										Protagonist* Proptr=0;
 										int trk = DialogLevelOne->GetTrack();
 										
 										if( Engine->Input_GetKey()==HGEK_PERIOD )
 										{
 											if( trk < DialogLevelOne->GetTracks()-1 )
 											{
 												DialogLevelOne->PlayTrack(trk+1);
 												if(GameLevelMusic) GameLevelMusic->SetPlayPosition(GameLevelMusic->GetPlayPosition()+5000);
 											}
									}	
 
 										switch(trk)
 										{
 										case 0: Proptr = Aztec; break;
 										case 1: case 2: case 5: case 6: case 8: case 10: case 16: 
 											Proptr = Prophet; break;  
 										case 3: case 4: case 12: case 14:  Proptr = Jester; break;  
 										case 7: case 9: case 11: case 13: case 15: Proptr = Psycho; break;
 										default: bAztecIsSpeaking = false;
 										}
 										speakerY = Proptr->GetUpFace();
 										speakerX = Proptr->GetLeftFace() + 60.0f;
 										if( trk == 1 ||  trk == 4 || trk == 5 )  
 										{  
 											Psycho->SetFacing(FACERIGHT,false); 
 											if( Jester->GetStance() == IDLE )
 											Jester->SetFacing(FACERIGHT,false);
 										}
 									}
 									else
									{
 										bAztecIsSpeaking = false;
 										DialogLevelOne->Stop();
 										delete DialogLevelOne;
 										DialogLevelOne=0;
 									}
 							}
 					}
 					else
 					if( iLevelOneEvents == 7 )
 					{
 						if( EnemyCounterEnding < 20 )
 						{
							if(Spawn.TimerEnd())
 							{
 								Enemy* emm=0; 
 								float x = -120.0f;
 								switch(rand()%3)
 								{
 								case 0: x -= 15.0f; break;
 								case 1: x -= 30.0f; break;
 								case 2: x -= 45.0f; break;
 								}
 								emm = new Enemy(HUMAN,FACERIGHT,RUNNING,hgeVector(x,485.0f),hgeVector(1.0f, 0.0f) );
 								emm->Init(Engine,hTexEnemy,hSpeakerTex);
 								pGameEnemyList.push_back(emm);
 								++EnemyCounterEnding;
 							}
 						}
 							void HandleDeltaSuad(float dt);
 							HandleDeltaSuad(dt);
 
 							if( DialogLevelOne && bAwareSquadFlag )	
 							{
 									int trk = DialogLevelOne->GetTrack();
 
 									if( DialogLevelOne->IsPlaying() )
 									{
 										Protagonist* Poptr = 0;
 										switch(trk)
 										{
 										case 0: Poptr=Prophet;  bAztecIsSpeaking = true; break;
 										case 1: case 2: case 4:	bAztecIsSpeaking = true;  Poptr = Jester;break;
 										case 5: Poptr = Psycho; bAztecIsSpeaking = true;	break;
 										default: bAztecIsSpeaking = false;
 										}
 										
 										if(Poptr)
 										{
 										speakerX = Poptr->GetLeftFace()+60;
 										speakerY = Poptr->GetUpFace();
 										}
 									}else bAztecIsSpeaking = false;
 
 									if( DialogLevelOne->GetTrack() == 0 && DialogLevelOne->IsFinished() )
 									{
 										string str1 =  DialogLevelOne->GetTrackName();
 										string str2 =  finale[0];
 										if(str1 == str2)
 										{
 											GameLevelMusic = new MusicPlayer(sound_engine); 	
 											GameLevelMusic->Play("sound/music/airfield_intro.mp3");
 										}
 									}
 
 									DialogLevelOne->PlayList();	
 
 									if( !DialogLevelOne->IsPlaying() && ( !GameLevelMusic || !GameLevelMusic->IsPlaying() ) && !pSpecialEnemy  )  
 									{
 										bAztecIsSpeaking=false;
 										DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne = 0;
 										pSpecialEnemy = new Enemy( HUMAN, FACELEFT, RUNNING, hgeVector(1366,485), hgeVector(-1,0) );
 										pSpecialEnemy->Init(Engine,hTexEnemy,hSpeakerTex);
 										GameLevelMusic = new MusicPlayer(sound_engine);
 										GameLevelMusic->Play("sound/music/the_siege_intro.mp3");
 									}
 
 									if(DialogLevelOne)	
 									{
 										if( !DialogLevelOne->IsPlaying() ) bAztecIsSpeaking=false;
									}
 							}
 											
 						 	if(GameLevelMusic) 
 							{
 								if(!GameLevelMusic->IsPlaying())	
 								{ GameLevelMusic->Stop(); delete GameLevelMusic;  GameLevelMusic=0; }
 							}
						
 							if( DialogLevelOne  && Prophet->IsDead() )
 							{
 								if( !DialogLevelOne->IsPlaying() )  
 								{	
 									DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne=0; 
 								}
 							}
 					}
 					else
 					if( iLevelOneEvents == 8 )
 					{
 						if(DialogLevelOne)
 						{
 							DialogLevelOne->PlayList();
 							if(!DialogLevelOne->IsPlaying())
 							{
 							  DialogLevelOne->Stop();
 							  delete DialogLevelOne; DialogLevelOne=0;
 							}
 						}
 					}
 					else if (iLevelOneEvents==10)
					{
 						if(GameLevelMusic) 
 						{
 							if(GameLevelMusic->IsFinished())
 							{
 								GameLevelMusic->Stop(); delete GameLevelMusic; GameLevelMusic=0; 
 							}
 						}
 					}
 						
 
 		if(GameLevelMusic && iLevelOneEvents < 9)
 		{
 			GameLevelMusic->PlayList();
 			if( GameLevelMusic->IsFinished() )
 			{
 			  delete GameLevelMusic; GameLevelMusic=0;			
 			}
 		}
 		
 		if( iLevelOneEvents == 4 && bProphetTransmission==false && fDistanceCovered > 350.0f && fDistanceCovered <357.0f )
 		{
 			bProphetTransmission=true;
 			speakerX = 50.0f; speakerY=650.0f;
 			
 			if(!DialogLevelOne)
 			{ 
 				DialogLevelOne = new MusicPlayer(sound_engine); DialogLevelOne->Play(Diags_Misc[0]); 
 				bAztecIsSpeaking = true;
 			}
 		}
 
 		if(  iLevelOneEvents == 4 && DialogLevelOne && bProphetTransmission )
 		{ 
 			if(!DialogLevelOne->IsPlaying()) 
 			{ 
 				DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne = 0; SoundEffectsList.push_back(PlaySoundEffect(ROGER_THAT)); 
 				bAztecIsSpeaking = false;	
 			}  
 		}
 
 		// Update Protagonist
 		Aztec->Update(Engine,dt);  
 		// Get Protagonist's Current Stance
 		const ePLAYER_STANCE STANCE_AZTEC = Aztec->GetStance();
 		const ePLAYER_STANCE FACING_AZTEC = Aztec->GetFacing();
 		RightSideCollision = LeftSideCollision = false;
 		
 		
 		if( !Aztec->IsDead() )
 		{
 			if( Engine->Input_GetKey() == HGEK_1 && Aztec->pCurrentWeapon->GetWeaponID() != ASSAULTRIFLE )  
 			{ 
 				Aztec->SelectAssaultRifle();   SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
 			}else 
 				if( Engine->Input_GetKey() == HGEK_2 && Aztec->pCurrentWeapon->GetWeaponID() != SEMIAUTO )	
 				{ 
 					Aztec->SelectSideArm();        SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
 				}else
 					if( bActivateShotgun && Engine->Input_GetKey() == HGEK_3 && Aztec->pCurrentWeapon->GetWeaponID() != SHOTGUN )  
 					{ 
 						Aztec->SelectShotGun();        SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
 					}else
 						if( bActivateLauncher && Engine->Input_GetKey() == HGEK_4 && Aztec->pCurrentWeapon->GetWeaponID() != ROCKETLAUNCHER )  
 						{
 							Aztec->SelectRocketLauncher(); SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
 						}
 		}
 			
 			if( LSX < 251 && iLevelOneEvents <= 7 )
 			{
 				bMove = false;
 				fBoundX = 725.0f;
 			}
 
 			if ( fDistanceCovered > 760.0f && bEnding == false )
 			{
				bEnding = true;
 
 					for( int l=0; l<BoxSprite->Objects.size(); l++ )
 					{
 						if( BoxSprite->Objects[l].GetLeftFace() >= SCREENWIDTH )
 						{
 							BoxSprite->Objects[l].Die();
 							BoxSprite->Objects[l].Release();
 							BoxSprite->Objects.erase( BoxSprite->Objects.begin()+l );
 							if( l != 0 && l != BoxSprite->Objects.size()-1 ) l--;
 						}
 					}
 
 					for( int t=0; t<MixSprite->Objects.size(); t++ )
 					{
 						if( MixSprite->Objects[t].GetLeftFace() >= SCREENWIDTH && MixSprite->Objects[t].GetId() != 7 && MixSprite->Objects[t].GetId() != 8 )
 						{
 							MixSprite->Objects[t].Die();
 							MixSprite->Objects[t].Release();
 							MixSprite->Objects.erase( MixSprite->Objects.begin()+t );
 							if( t != 0 && t != MixSprite->Objects.size()-1 ) t--;
 						}
 					}				
 					
 					void GenerateItems(); GenerateItems();
 			}
 
 
 			#define LEVEL 1
 			
 			UpdateCloud(vClouds,dt);
 			UpdateLeaves(Leaves);
 			UpdateBirds(vBirds,dt);
 			
 			MovePlayerOnEarth( dt );						  // Move Player	
 			JumpAndCollision( dt,GROUND );					  // player jumps	
 			Move( vInGameBullets, dt,Engine );				  // update bullets
 			checkBulletCollision( MixSprite->Objects ) ;	  // with Box Sprites
 			checkBulletCollision( BoxSprite->Objects);		  // with Box Sprites
 			checkBulletCollision( pGameEnemyList );			  // with Box Enemies
 			BulletCollisionPro(  );
 			
 			ManageEnemy( dt,LEVEL,Aztec );								  // this function performs enemy management and handles enemy A.I. 	
 			checkExistance();
 			MaintainGrenades(GrenadeList);
 			UpdateScores(vScores);
 			/////
 
 			if( Engine->Input_GetKeyState(HGEK_SPACE) && !Aztec->IsDead() )   /// FIRE WEAPON
 			{   
 				bool bWeaponisEmpty = Aztec->pCurrentWeapon->IsEmpty();
 				if( Aztec->FireWeapon() )
 				{
 					if( !bWeaponisEmpty )
 					{
 						createBullet(Aztec, hTexBullets, Engine, vInGameBullets); 
 						void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList);
 
 						ShowGunSpark( Aztec, ParticleList );
 						eSOUNDEFFECTS PlayEffect = NULL_SOUND;
 						switch( Aztec->pCurrentWeapon->GetWeaponID() )
 						{
 						 case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
 						 case SEMIAUTO:       PlayEffect=FIRE_PISTOL;		break;
 						 case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN;		break;	
 						 case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER;	break;
 						}
 						SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
 					}
 					else
 						SoundEffectsList.push_back( PlaySoundEffect(WEAPON_EMPTY) );
 			   } // end of if block that is operated around the fire call
 			}
 
 			/////////////////////////////////////////////////////////////////////////
 
 		   for (unsigned  int i=0; i<ParticleList.size(); i++ )  ParticleList[i]->Update(dt);		   
 		   ManageParticleList(ParticleList);	
 		  
 
 		   for (unsigned  int i=0; i<LauncherEffectParticleList.size(); i++ )  
 		   {	
 			   LauncherEffectParticleList[i]->Update(dt);
 
 			   for(int l=0; l< vInGameBullets.size(); l++ )
 			   {
 				   if(vInGameBullets[l]->GetId() == ROCKETLAUNCHER_BULLET )
 				   {
 					   if( vInGameBullets[l]->part == LauncherEffectParticleList[i] )
 					   {
 						   LauncherEffectParticleList[i]->MoveTo(vInGameBullets[l]->vPosition.x,vInGameBullets[l]->vPosition.y);						
					   }
 				   }
 			   }
 		   }
 
 		   for (unsigned  int po=0; po<LauncherEffectParticleList.size(); po++ )
 		   {
 			   if(LauncherEffectParticleList[po]->GetParticlesAlive() <= 0 )
 			   {
 				   LauncherEffectParticleList[po]->Stop();
 				   delete LauncherEffectParticleList[po];
 				   LauncherEffectParticleList.erase( LauncherEffectParticleList.begin() + po );
 			   }
 		   }
 
 
      	   ProcessSound(SoundEffectsList);
 
 		   for (int z=0; z<EnemyDialogsList.size(); z++)	
 			   Engine->Effect_PlayEx(EnemyDialogsList[z].hDialog,50);
 		   
 		   while(!EnemyDialogsList.empty())  EnemyDialogsList.pop_back();
 
 
 			if( Engine->Input_GetKeyState(HGEK_HOME) )
 			{
 				if( Engine->Input_GetKey() == (HGEK_G) )
 				{
 					GOD_MODE_FLAG = (GOD_MODE_FLAG)?(false):(true);
 				}
 			}
 
 			if(GOD_MODE_FLAG) 
 			{
 				if(Aztec->GetHealth() < 99 )	Aztec->SetHealth(100);
 				Aztec->SetDead(false);
 				if( Aztec->GetStance() == DEATH ) Aztec->ChangeStance(IDLE);
 			}
 		
			 ManageTileMapping();
 			  ProcessBonus();
 			
 			  if( Aztec->IsDead() && Aztec->IsPlaying() )
 			  {
 				  DeathTimer.setstart();
 			  }
 			  else 
 				if ( Aztec->IsDead() && !Aztec->IsPlaying() && DeathTimer.TimeOver() )  	
 				{	
 					Manager->SetState(STATE_GAMEOVER);		
 				}
 		
 	      } // end of else
 
 	return false;
}

inline float turnPositive(float p ) 
{   if(p < 0) p *= -1;   return p; }

void HandleDeltaSuad(float dt)
{
	Jester->MainAnimation->Update(dt);
	Psycho->MainAnimation->Update(dt);
	Prophet->MainAnimation->Update(dt);
	
	if(Prophet->IsDead()) return;

	for( int i=0; i<pGameEnemyList.size(); i++ )
	{	
		if( pGameEnemyList[i]->GetStance() == IDLE && pGameEnemyList[i]->vPosition.x < 20.0f && !pGameEnemyList[i]->IsDead() )
		{
			pGameEnemyList[i]->ChangeStance(RUNNING); 
			if( pGameEnemyList[i]->GetRightFace() < 50 )
			pGameEnemyList[i]->Move(dt);
		}
	}		
		

	if( Prophet->GetStance() == RUNNING && Prophet->vPosition.x > Psycho->vPosition.x+25.0f  )
	{ 
		Prophet->vDirection.x = -1; Prophet->Move(dt); 
	}

	if( pGameEnemyList.size() > 0  )
	{
		Enemy* enm =  pGameEnemyList.back();

		int countEb=0,countAb=0;

		for( int i=0; i < vInGameBullets.size(); i++ )
		{
			eBULLETID id = vInGameBullets[i]->GetId();
			switch(id)
			{
			case ASSAULTRIFLE_BULLET:
			case SEMIAUTO_BULLET:
			case SHOTGUN_BULLET:
			case ROCKETLAUNCHER_BULLET:  ++countAb; break;
			case ENEMYBULLET_TYPE1:
			case ENEMYBULLET_TYPE2:
			case ENEMYBULLET_TYPE3:
			case ENEMYBULLET_TYPE4: ++countEb; 
			}
		}

		if( enm->GetRightFace() > 40.0f || countEb )
		{
			if( bAwareSquadFlag == false && DialogLevelOne )
			{
				bAwareSquadFlag = true;
				DialogLevelOne->PlayTrack(0);
				if(GameLevelMusic) { delete GameLevelMusic; }
				//GameLevelMusic = new MusicPlayer(sound_engine); 	GameLevelMusic->Play("sound/music/airfield_intro.mp3");
			}
			
			if(DialogLevelOne) if(DialogLevelOne->GetTrack() == 0) return;

			Jester->SetFacing(FACELEFT,true);
			Prophet->SetFacing(FACELEFT,true);
			 Psycho->SetFacing(FACELEFT,true);

			Jester->ChangeStance(DUCK);
			Psycho->ChangeStance(IDLE);
				
			if( Prophet->vPosition.x > Psycho->vPosition.x+25.0f )
			{
				Prophet->ChangeStance(RUNNING);	
				if(!Prophet->MainAnimation->IsPlaying()) { Prophet->ChangeStance(IDLE); Prophet->ChangeStance(RUNNING);	}
			}
			else { Prophet->ChangeStance(IDLE); }
			
			Jester->pCurrentWeapon->SetFiringRate(160);
			Psycho->pCurrentWeapon->SetFiringRate(140);
			Prophet->pCurrentWeapon->SetFiringRate(130);

			if( Prophet->pCurrentWeapon->GetAmmo() < 10 ) Prophet->pCurrentWeapon->SetAmmo(160);
			 if( Psycho->pCurrentWeapon->GetAmmo() < 10 ) Psycho->pCurrentWeapon->SetAmmo(160);
			 if( Jester->pCurrentWeapon->GetAmmo() < 10 ) Jester->pCurrentWeapon->SetAmmo(160);
			
			if(!pSpecialGrenade)
			for(int l=0; l<3; l++ ) 
			if( ptrPro[l]->FireWeapon() )
			{
					createBullet(ptrPro[l], hTexBullets, Engine, vInGameBullets); 
					void ShowGunSpark(Protagonist* , vector<hgeParticleSystem*> &ParticleList);

					ShowGunSpark( ptrPro[l], ParticleList );
					eSOUNDEFFECTS PlayEffect = NULL_SOUND;
					switch( ptrPro[l]->pCurrentWeapon->GetWeaponID() )
					{
					case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
					case SEMIAUTO:       PlayEffect=FIRE_PISTOL;		break;
					case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN;		break;	
					case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER;	break;
					}
					SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
			}
		}	
	}

	if( pSpecialEnemy )
	{
		if( pSpecialEnemy->vPosition.x > 1240.0f )
		{
			pSpecialEnemy->SetFacing(FACELEFT);
			pSpecialEnemy->vDirection.x = -1.0f;
			pSpecialEnemy->ChangeStance(RUNNING);
			if(!pSpecialEnemy->anim->IsPlaying()){pSpecialEnemy->ChangeStance(IDLE);pSpecialEnemy->ChangeStance(RUNNING);} 
			pSpecialEnemy->Move(dt);
			pSpecialEnemy->anim->Update(dt);
		}
		else 
		{
			pSpecialEnemy->ChangeStance(IDLE);
			Grenade* createGrenade(Enemy* , HTEXTURE );
			Grenade* gred = createGrenade(pSpecialEnemy,hTexBullets);
			gred->vSpeed.y  += 100.0f;
			gred->vSpeed.x  = turnPositive( pSpecialEnemy->vPosition.x - Jester->vPosition.x );
			pSpecialGrenade = gred;
			/*if( enemy->GetFacing() == FACERIGHT )*/
			GrenadeList.push_back(gred);
			SoundEffectsList.push_back (PlaySoundEffect(ROCKET_LAUNCHER));
			pGameEnemyList.push_back(pSpecialEnemy);
			void CreateEnemyLauncherSpark(Enemy* );
			CreateEnemyLauncherSpark(pSpecialEnemy);
			pSpecialEnemy = 0;
			DialogLevelOne = new MusicPlayer(sound_engine);
			DialogLevelOne->Play("Sound/Dialogs/Level 1/alldead.mp2");
			return;
			}
		}

	}



void ManageTileMapping()
{
   for( int i=0; i<BoxSprite->Objects.size(); i++ )
   {
	  	if( BoxSprite->Objects[i].GetRightFace() < 0.0f )
		{
			BoxSprite->Objects[i].Release();
			BoxSprite->Objects.erase( BoxSprite->Objects.begin()+i );
			if( i != 0 && i != BoxSprite->Objects.size()-1 ) i--;
		}
   }

   for( int i=0; i<MixSprite->Objects.size(); i++ )
   {
	   if( MixSprite->Objects[i].GetRightFace() < 0.0f )
	   {
		   MixSprite->Objects[i].Release();
		   MixSprite->Objects.erase( MixSprite->Objects.begin()+i );
		   if( i != 0 && i != MixSprite->Objects.size()-1 ) i--;
	   }
   }
}


bool StateLevel1::Render()
{
 		if(iLevelOneEvents == 0) return false;
 		else
 		if(iLevelOneEvents == 11)	
 		{
 			float fts = font->GetScale();
 			font->printf(580,370,0,"Mission Complete");
 			font->SetScale(0.8);
 			font->printf(580,700,0,"Press Enter To Continue");
 			font->SetScale(fts);
 			return false;
 		}
 		else
 		if(iLevelOneEvents == 1 || iLevelOneEvents == 2)
 		{
 			bool RenderScene();
 			RenderScene();
 		    if (paused)	{	PauseMenuSpr->Render(0,0);	GUI->Render();	}
 			return false;
 		}
 		else 
 			if (iLevelOneEvents == 3)
 			{
 				LevelOneSpr->Render(0,0);
 				if (paused)	{	GUI->Render();	}
 				return false;
 			}
 			
 		//Game Render Follows
			
 		sky.Render(0,0);
 		RenderCloud(vClouds);
 		mountains.Render(0,464);
 		RenderBirds(vBirds);
 		RenderObjects(vListOfObjects); //
 		if (bEnding)    {  	 LostShip->Render(LSX,385);	   }
		
 		ground1.Render(0,615);
 		ground1.Render(256,615);
 		ground1.Render(512,615);
 		ground1.Render(768,615);
 		ground1.Render(1024,615);
 		ground1.Render(1280,615);
 		
 		for (unsigned  int i=0; i<LauncherEffectParticleList.size(); i++ )  
 		LauncherEffectParticleList[i]->Render();
		
 		GrassSprite->Render();
 		RenderObjects(pDeadBodies);
 		MixSprite->Render();
 		BoxSprite->Render();
 		RenderObjects(pGameEnemyList); if(pSpecialEnemy) pSpecialEnemy->Render();
 		RenderObjects(vInGameBullets); 
		
 		if(iLevelOneEvents >= 5)
 		{
 			float LZ = LSX+LostShip->GetWidth();
 			font->SetColor(0xff000000);	
 			DeadEnemies->Render(LZ+50,GROUND-52 );
 			if( iLevelOneEvents < 7 )
 			{
 			Psycho->vPosition.x = LZ-150.0f;
 			Prophet->vPosition.x = LZ+20.0f;
 			}
 			
 			Jester->Render();
 			CallOutSpr->RenderEx(Jester->vPosition.x+15,Jester->GetDownFace()+28,0.0f,0.68,0.8);
 			font->printf(Jester->vPosition.x+23,Jester->GetDownFace()+31,0,"Jester");	
 
 			Psycho->Render();
 			CallOutSpr->RenderEx(Psycho->vPosition.x,Psycho->GetDownFace()+8,0.0f,0.68,0.8);
 			font->printf(Psycho->vPosition.x+5,Psycho->GetDownFace()+12,0,"Psycho");
 			
 			Prophet->Render();
 			CallOutSpr->RenderEx(Prophet->vPosition.x+15,Prophet->GetDownFace()+8,0.0f,0.75,0.8);
 			font->printf(Prophet->vPosition.x+23,Prophet->GetDownFace()+12,0,"Prophet");
 	
 			DeadAzztec->Render(LZ-125,GROUND-32 );		
 		}
 
 		Aztec->Render();
 		RenderObjects(GrenadeList);	
 		RenderObjects(vBonus);
 		RenderLeaves(Leaves);
 		RenderHud();
 		RenderScores();
 		for (unsigned int i = 0 ; i < ParticleList.size(); i++ )
 			if (ParticleList[i])  ParticleList[i]->Render();
 
 		if(bAztecIsSpeaking)
 		{
 			AztecSpeaks->RenderEx(speakerX,speakerY,fAngleSpeaker,0.6,0.6);
 		}
 		
 		if(bDisplayBonusMessage)
 		{
 			float scl = font->GetScale();
 			font->SetScale(0.8f);
 			font->SetColor(0xff000000);
 			CallOutSpr->RenderEx(487,717,0.0f,2.0f,0.8f); 
 			font->printf(500,724,0,"Press \"Enter\" To Pick Up The Item");
 			font->SetScale(scl);
 		}
 
 		/////////Render Starting Info ////////////
 
 		if (bShowInfo)	
 		{
 			if (fAlpha <= 0)
 			{
 				bShowInfo = false;
 			}
 			else
 			{
 				font->SetScale(1.5);  fAlpha -= 0.65f; 
 				font->SetColor(ARGB(fAlpha,80,180,10)); 
 				font->SetScale(3.0f);                           
 				font->printf(410,250,0,"\"Get To Aztec\"");
 				font->SetScale(1.15f);
 				font->printf(420,330,0,"Location : \"Lingshan Islands\" (Korea)");
 			}
 		}
		////////////Displaying SCORE
		font->SetColor(ARGB(200,255,255,255));
		font->SetScale(1.5f);
		font->printf(10,10,0,"SCORE : %d",Total_Score);
		font->SetScale(1.0f);
		////////////////////////////////////////////
 //////////////////////////Displays Pause Menu when pressed ESC 	
 		if (paused)
 		{
 			PauseMenuSpr->Render(0,0);
 			//Displays Pause Menu
 			GUI->Render();
 		}
 

		return false;

}

void UpdateDeltaForce(float dt)
{
	if(Prophet->vPosition.x < 1100.0f )	
	{
		if( ptrPro[0]->vPosition.x > 980.0f )		
		{	
			if(!Jester->MainAnimation->IsPlaying())
			{
				ptrPro[0]->ChangeStance(IDLE);
			}	
			ptrPro[0]->ChangeStance(RUNNING);
			ptrPro[0]->SetFacing(FACELEFT,true);
			ptrPro[0]->Move(dt);
			ptrPro[0]->MainAnimation->Update(dt);
		}
		else 
			ptrPro[0]->ChangeStance(IDLE);
	}
	
	if(pGameEnemyList.size()!=0  && Psycho->vPosition.x < 1220.0f )
	{
		Enemy* En =pGameEnemyList.front();

		if( En->GetRightFace() < 0 )
		{
			En->Die();
			En->Release();
			pGameEnemyList.erase(pGameEnemyList.begin());
			return; 
		}
		
		
		
		if(En->vPosition.x  > Prophet->vPosition.x ) Prophet->SetFacing(FACERIGHT,true);
		if(En->vPosition.x  < Psycho->vPosition.x ) Psycho->SetFacing(FACELEFT,true);

		Prophet->pCurrentWeapon->SetFiringRate(120.0f);
		Psycho->pCurrentWeapon->SetFiringRate(120.0f);
		
		if(Prophet->FireWeapon())
		{
				createBullet(Prophet, hTexBullets, Engine, vInGameBullets); 
				void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList);

				ShowGunSpark( Prophet, ParticleList );
				eSOUNDEFFECTS PlayEffect = NULL_SOUND;
				switch( Prophet->pCurrentWeapon->GetWeaponID() )
				{
				case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
				case SEMIAUTO:       PlayEffect=FIRE_PISTOL;		break;
				case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN;		break;	
				case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER;	break;
				}
				SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
		}
			
		if(Psycho->FireWeapon())
		{
			createBullet(Psycho, hTexBullets, Engine, vInGameBullets); 
			void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList);

			ShowGunSpark( Psycho, ParticleList );
			eSOUNDEFFECTS PlayEffect = NULL_SOUND;
			switch( Psycho->pCurrentWeapon->GetWeaponID() )
			{
			case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
			case SEMIAUTO:       PlayEffect=FIRE_PISTOL;		break;
			case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN;		break;	
			case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER;	break;
			}
			SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
		}
	}

}

void EmptyLists();
bool StateLevel1::Release()
{  
	EmptyLists();
	ReleaseHud();
	Engine->Channel_StopAll();
	GUI->Leave();
	for(int i=0; i<3;i++) 
	ptrPro[i]->Release(Engine);
	GrassSprite->Release();
	BoxSprite->Release();
	MixSprite->Release();
	Aztec->Release(Engine);
	if(KeyMusicPlayer)	KeyMusicPlayer->Stop();
	if(GameLevelMusic)	GameLevelMusic-> Stop();
	if(DialogLevelOne)	DialogLevelOne->Stop();

	delete sprGrenade;			sprGrenade=0;  
	delete Health;				Health=0;	  
	delete CurWeapon;			CurWeapon=0;
	delete blastSprite;			blastSprite=0;
	delete GrenadeBlastSprite;  GrenadeBlastSprite=0;
	delete DialogLevelOne;		DialogLevelOne=0;
	delete KeyMusicPlayer;		KeyMusicPlayer=0;
	delete GameLevelMusic;		GameLevelMusic=0;
	delete PauseMenuSpr;		PauseMenuSpr=0;
	delete ptrPro[0];			ptrPro[0]=0;
	delete ptrPro[1];			ptrPro[1]=0;
	delete ptrPro[2];			ptrPro[2]=0;	Prophet = Jester = Psycho = 0;
	delete DeadAzztec;			DeadAzztec=0;
	delete DeadEnemies;			DeadEnemies=0;
	delete LevelOneSpr;			LevelOneSpr=0; 
	delete GUI; 				GUI =  0;
	delete cursor;				cursor = 0; 
	delete GrassSprite;			GrassSprite = 0;
	delete BoxSprite ;			BoxSprite = 0;
	delete MixSprite;			MixSprite = 0;
	delete font;				font = 0;
	delete Aztec;				Aztec = 0; 
	delete ParSprite;			ParSprite = 0;
	delete GunSparkSprite;		GunSparkSprite = 0;
	delete FireHitSprite;		FireHitSprite = 0;
	delete LostShip;			LostShip = 0;
	delete SolarGun;			SolarGun = 0;
	delete CallOutSpr;			CallOutSpr = 0;	
///////////////////////////////////////////////////////////////
	Engine->Texture_Free( healthTex );				healthTex=0;
	Engine->Texture_Free( hTexEnemy );				hTexEnemy=0;
	Engine->Texture_Free( blast );					blast=0;
	Engine->Texture_Free( hCallOutTex );			hCallOutTex=0;
	Engine->Texture_Free( groundtex );				groundtex=0;
	Engine->Texture_Free( boxtex );					boxtex=0;
	Engine->Texture_Free( mixtex );					mixtex=0;
	Engine->Texture_Free( cur );					cur=0;
	Engine->Texture_Free( rest );					rest=0;					
	Engine->Texture_Free( res );					res=0;
	Engine->Texture_Free( ex );						ex=0;
	Engine->Texture_Free(DamageBoxTex);				DamageBoxTex=0;	
	Engine->Texture_Free(texBirds);					texBirds=0;
	Engine->Texture_Free(cloud);					cloud=0;
	Engine->Texture_Free(hTexBullets);				hTexBullets=0;
	Engine->Texture_Free(hLeafTex);					hLeafTex=0;
	Engine->Texture_Free(Objects);					Objects=0;
	Engine->Texture_Free(ParTex);					ParTex=0;
	Engine->Texture_Free(GunSparkTex);				GunSparkTex=0;
	Engine->Texture_Free(FireHitTex);				FireHitTex=0;
	Engine->Texture_Free(LStex);					LStex=0;
	Engine->Texture_Free(hSpeakerTex);				hSpeakerTex=0;
	Engine->Texture_Free(SpriteSheetObj2);			SpriteSheetObj2=0;
	Engine->Texture_Free(hLevelOneTex);				hLevelOneTex=0;
	Engine->Texture_Free(hDeadAzztecTex);			hDeadAzztecTex=0;
	Engine->Texture_Free(hDeadEnemiesTex);			hDeadEnemiesTex=0;
	Engine->Texture_Free(L1_GroundTex);				L1_GroundTex=0;
	Engine->Texture_Free(L1_SkyTex);				L1_SkyTex=0;
	Engine->Texture_Free(L1_MountsTex);				L1_MountsTex=0;
	Engine->Texture_Free(PauseMenuTex);				PauseMenuTex=0;
	Engine->Texture_Free(Fallingtex);				Fallingtex = 0;
	
	return true;
}



///////////////////////////////////////////////// COLLISION DETECTION ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,class Any>
bool ObjectCollision(T &Ob1, Any &Ob2, float abs,float ht)   // could be helpful with bullets
{

	if ( !Ob1.IsDead() && !Ob2.IsDead() ) 
		if ( Ob2.GetRightFace() > (Ob1.GetLeftFace()+abs) && Ob2.GetLeftFace() < (Ob1.GetRightFace()-abs) )   // for X axis
		{ 
		 	if ( Ob2.GetUpFace()+ht < Ob1.GetDownFace()   && Ob2.GetDownFace() > Ob1.GetUpFace()+ht )	      // for Y axis
			{	
				return true;
			}
		}
   	return false;
}

bool HorizontalCollisionDetection(Protagonist &Pro, LevelObjects &BoxObject )
{	
	const float fAbs = 45.0f; 
	   if( Pro.GetRightFace()-fAbs > BoxObject.GetLeftFace() && Pro.GetLeftFace()+fAbs < BoxObject.GetRightFace()  )
		return true;	
		
  return false;	
}

inline bool VerticalCollisionDetection(Protagonist &Pro, LevelObjects &BoxObject, float negation )
{
  const float fAbs = 45.0f; 
  if( Pro.GetDownFace() > (BoxObject.GetUpFace()+negation) && Pro.GetDownFace() < (BoxObject.GetUpFace()+15+negation) )   
	   if( Pro.GetRightFace()-fAbs > BoxObject.GetLeftFace() && Pro.GetLeftFace()+fAbs < BoxObject.GetRightFace()  )
	  return true;
  return false; 
}

//////////////////////////////////// IMPLEMENT JUMP AND VERTICAL COLLISION AND ALLOW PLAYER TO STAND OVER OBJECTS ////////////////
void SetBoxWidth( LevelObjects& object, float &Right, float &Left );

bool CheckMelee(Protagonist* Aztec, TileMap* Sprite )
{
	float aztec_face = ( Aztec->GetFacing() == FACERIGHT )? (Aztec->GetRightFace()-10.0f) : (aztec_face = Aztec->GetLeftFace()+10.0f);

		for( unsigned int n = 0; n < Sprite->Objects.size(); n++ )
		{
			if( !Sprite->Objects[n].IsCollidable() ) continue;
			float BoxLeft  = Sprite->Objects[n].GetLeftFace();  	float BoxRight = Sprite->Objects[n].GetRightFace();
			eSOUNDEFFECTS PlayEffect=NULL_SOUND;
			SetBoxWidth( Sprite->Objects[n],BoxRight,BoxLeft );	
			if ( BoxLeft <= aztec_face && aztec_face <= BoxRight )  // collision detected
			{		
				Sprite->Objects[n].DecreaseHealth(35);

				if (  ( Sprite->Objects[n].GetHealth() <= 50 ) && ( Sprite->Objects[n].GetId() == 1 || Sprite->Objects[n].GetId() == 2 )  )
				{
						Sprite->Objects[n].SetImage(DamageBoxTex);
						if(!Sprite->Objects[n].bDamageFlag)
						SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			

						if ( Aztec->GetFacing() == FACELEFT )
						{
							Sprite->Objects[n].Spr->SetFlip(true,false,false); 
							if(!Sprite->Objects[n].bDamageFlag)
							SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			
						}		
					Sprite->Objects[n].bDamageFlag = true;
				}

				switch(Sprite->Objects[n].GetId())
				{
				case 1: PlayEffect=MELEE_WOOD_BOX; break;
				case 2: PlayEffect=(Sprite->Objects[n].GetHealth()>50) ? MELEE_STEEL_BOX : MELEE_WOOD_BOX ; break;
				case 3: 
				case 4: PlayEffect=MELEE_ROCK; break;
				case 5:
				case 6: PlayEffect=MELEE_COIL; break;
				}
				SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );

				if( Sprite->Objects[n].GetHealth() <= 0 )
				{
				
					eParticles par = GREY_SMOKE; ;
					float dir=0.0f,x,y;
					AddScore(hgeVector(Sprite->Objects[n].GetLeftFace() + 20, Sprite->Objects[n].GetUpFace()), "+20",BOX_MELEES);
					switch( Sprite->Objects[n].GetId() )
					{
					case 1:   
					case 2:   par = BROWN_SMOKE; break;
					case 3:   
					case 4:   par = GREY_SMOKE;  break; 
					case 5:
					case 6:   par = BLACK_SMOKE; break;  
					}

					switch(Sprite->Objects[n].GetId())
					{
					case 1: PlayEffect=BREAK_WOOD_MELEE; break;
					case 2: PlayEffect=BREAK_WOOD_MELEE; break;
					case 3: 
					case 4: PlayEffect=BREAK_ROCK_MELEE; break;
					case 5:
					case 6: PlayEffect=BREAK_COIL_MELEE; break;
					}
					GenerateBonus( Sprite->Objects[n], THIS_IS_LEVEL_NUMBER );
					x = Sprite->Objects[n].GetRightFace() - Sprite->Objects[n].GetLeftFace();
					y = Sprite->Objects[n].GetDownFace() - Sprite->Objects[n].GetUpFace();
					x/=2.0f; x += Sprite->Objects[n].GetLeftFace();  y /= 2.0f; y += Sprite->Objects[n].GetUpFace();
					ParticleList.push_back ( ParticleFactory(par,x,y-20.0f,dir) );
					ParticleList.push_back ( ParticleFactory(par,x,y+15.0f,dir) );
					Sprite->Objects.erase(Sprite->Objects.begin() + n );
					SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
				}
				return true;
			}			
		}

  return false;
}

//////////////////////////////////////////  MOVE THE PLAYER ON THE GROUND ////////////////////////////////////////////////
bool JumpAndCollision(float dt, const int GROUND )
{
	ePLAYER_STANCE AztecStance =  Aztec->GetStance();  // get the stance

if( AztecStance != JUMPING && Engine->Input_KeyDown(HGEK_B) && !Aztec->IsDead())
  	{
 		EscapeVelocity = -6.6f;
 		PLAYERSTATUS = IN_THE_AIR;
 		Aztec->vPosition.y += EscapeVelocity;
		Aztec->ChangeStance(JUMPING);
		SoundEffectsList.push_back(PlaySoundEffect(PLAYER_JUMP));

}	
	if( PLAYERSTATUS == IN_THE_AIR )	// Freely Suspended Player Under The Action Of Gravity
 	{
 		Aztec->vPosition.y+=EscapeVelocity;
 		EscapeVelocity += GRAVITY;        
 
 		if( Aztec->GetDownFace()+3.0f >= GROUND-5.0f )
 		{
 			PLAYERSTATUS = ON_THE_GROUND;
 			CreateEffect(Aztec,ParticleList);
 			Aztec->ChangeStance(IDLE);	
 			EscapeVelocity = 0.0f;
 			if(THIS_IS_LEVEL_NUMBER==1)
 			Aztec->vPosition.y=480.0f; 
 			else 
 			Aztec->vPosition.y=565.0f; 	
 			SoundEffectsList.push_back(PlaySoundEffect(PLAYER_HITS_GROUND));
 		}
 		else
 			if( EscapeVelocity > 0 && VerticalCollision == true )     // Downward Motion
 			{
 				PLAYERSTATUS = ON_THE_OBJECT;
 				Aztec->ChangeStance(IDLE);		
 				CreateEffect(Aztec,ParticleList);
 				SoundEffectsList.push_back( PlaySoundEffect(PLAYER_HITS_OBJECT) );
 			}
 
 			std::vector< LevelObjects* >  OnScreenObjects;  // maintain a queue of objects visible on screen
 
 			for (unsigned  int s=0; s < BoxSprite->Objects.size(); s++ )
 			{	
 				LevelObjects *LevOb = &BoxSprite->Objects[s];	
 				if( LevOb->GetRightFace() > -10 && LevOb->GetLeftFace() < 1400 && !LevOb->IsDead() )
 				{
 					OnScreenObjects.push_back(LevOb);	
 				}
 			}
 
 			if(THIS_IS_LEVEL_NUMBER == 1)
			{
 				for (unsigned int s=0; s < MixSprite->Objects.size(); s++ )
 				{		
 					LevelObjects *LevOb = &MixSprite->Objects[s];	
 					if( LevOb->GetRightFace() > -10 && LevOb->GetLeftFace() < 1400 && !LevOb->IsDead() && LevOb->GetId() != 7 && LevOb->GetId() != 8 )
 					{
 						OnScreenObjects.push_back(LevOb);	
 					}
 				}
 			}
 
 			bool flag = false;
 
			for (unsigned int i=0; i<OnScreenObjects.size(); i++ )
 			{
 				float UpFace = OnScreenObjects[i]->GetUpFace();
 				   if( OnScreenObjects[i]->GetId() == 5 ) UpFace+=62;
 				else UpFace -= 10.0f;
 				float RightFace = OnScreenObjects[i]->GetRightFace();
 				float LeftFace = OnScreenObjects[i]->GetLeftFace();
 
 				if( Aztec->GetDownFace() > UpFace )  
 					if( (Aztec->GetLeftFace()+45) < RightFace && (Aztec->GetRightFace()-45) > LeftFace ) flag = true; 
 			}
 			
 			if( Engine->Input_GetKeyState(HGEK_RIGHT) && ( Aztec->vPosition.x < 350.0f || !bMove ) && Aztec->GetRightFace() < 1366.0f  ) 
 			{	
 				if( !( bMove == false && Aztec->GetLeftFace() >= 350.0f && LevelStartFlag == true ) || THIS_IS_LEVEL_NUMBER == 1 )
				if(!flag )  
 					if( ( THIS_IS_LEVEL_NUMBER == 1 && ( !( (iLevelOneEvents != 6 || iLevelOneEvents != 7 ) && Aztec->vPosition.x > 720 ) || iLevelOneEvents >= 8 )   ) 
 						|| THIS_IS_LEVEL_NUMBER == 2 )
 					Aztec->vPosition.x += 2.6f; 
 
 				if( Aztec->vPosition.x >= 350.0f && bEnding == false ) fDistanceCovered += 0.3f;
 			}
 			else 
 				if( Engine->Input_GetKeyState(HGEK_LEFT) && Aztec->vPosition.x > -30.0f && !VerticalCollision ) 
 				{	if(!flag)  Aztec->vPosition.x -= 2.6f; }
 	}
 
 	if( PLAYERSTATUS == ON_THE_OBJECT && VerticalCollision == false )
 	{
 		PLAYERSTATUS = IN_THE_AIR;
 	}	
 
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MovePlayerOnEarth( float dt )
{
	if( Aztec->GetStance() == DUCK && Aztec->GetFrame() == 0 && !Aztec->IsPlaying() )  {	Aztec->ChangeStance(IDLE);	}

	ePLAYER_STANCE STANCE_AZTEC = Aztec->GetStance();
	ePLAYER_STANCE FACING_AZTEC = Aztec->GetFacing();
	RightSideCollision = LeftSideCollision = false;
	HorizontalCollision  = VerticalCollision = false;				
	
		if(  STANCE_AZTEC != MELEE )		  {	bMeleeFlag = false; }
		else if( Aztec->GetFrame() != 1 )	  {	bMeleeFlag = true;  }

	// melee logic			
	if( STANCE_AZTEC == MELEE  && (Aztec->GetFrame() == 1) && PLAYERSTATUS == ON_THE_GROUND && bMeleeFlag )
	{	
		bMeleeFlag = false;
		float aztec_face = ( FACING_AZTEC == FACERIGHT )? (Aztec->GetRightFace()-10.0f) : (aztec_face = Aztec->GetLeftFace()+10.0f);
		float left=0.0f,right=0.0f; 
		bool checkBoxes = true;	
		bool meleeMiss = true;
		
		for(unsigned int k=0; k<pGameEnemyList.size(); k++ )
		{	
			if( !pGameEnemyList[k]->IsDead() )	
			{
				///  set few variables before collision test
				left = pGameEnemyList[k]->GetLeftFace();  right = pGameEnemyList[k]->GetRightFace();
				// set left and right	
				if( pGameEnemyList[k]->GetFacing() == FACELEFT )	
				{ left += 50;   if(Aztec->vPosition.x > pGameEnemyList[k]->vPosition.x ) {  left-=20;  right -= 20;  }  }
				else  // when enemy is facing right
				{ right -= 50;  if(Aztec->vPosition.x < pGameEnemyList[k]->vPosition.x ) {	left+=20;  right += 20;  }	}							
			    
				if( aztec_face >= left && aztec_face <= right )	// check collision					
				{
					eSOUNDEFFECTS PlayEffect = NULL_SOUND;

					switch (pGameEnemyList[k]->GetId())
					{
					case HUMAN: PlayEffect = NULL_SOUND; pGameEnemyList[k]->PlayDeathSound(EnemyDialogsList); break;
					case ALIEN1: PlayEffect = DIE_ALIEN1; break;
					case ALIEN2: PlayEffect = DIE_ALIEN2; break;
					case ALIEN3: PlayEffect = DIE_ALIEN3; break;
					}
					
					if(PlayEffect != NULL_SOUND)
					SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );	

					
					checkBoxes = false;
					CreateEffect(Aztec,ParticleList,HIT_BLOOD,pGameEnemyList[k]);
					AddScore(hgeVector(pGameEnemyList[k]->vPosition.x + 20, pGameEnemyList[k]->vPosition.y), "+20",ENEMY_MELEES);
					SoundEffectsList.push_back( PlaySoundEffect( (Aztec->pCurrentWeapon->GetWeaponID()== SEMIAUTO)?(MELEE_AZTEC_1):(MELEE_AZTEC_2)) );
					pGameEnemyList[k]->Die();
					
					meleeMiss = false;
					break;
				}
			}
		}
		
		if(checkBoxes)
		{
		  if( !CheckMelee( Aztec, BoxSprite ) )
		  {
			  if( CheckMelee( Aztec, MixSprite ) )
				  meleeMiss = false;
		  }
		  else
			  meleeMiss = false;
		}

		SoundEffectsList.push_back( PlaySoundEffect(MELEE_MISS) );
	}

		if(  STANCE_AZTEC != THROW_GRENADE )  {	grenadeflag = false; }
		else if( Aztec->GetFrame() != 3 )	  {	grenadeflag = true;  }
		if(  STANCE_AZTEC == THROW_GRENADE &&  Aztec->GetFrame() == 3 && grenadeflag)  
		{	
			grenadeflag = false;
			GrenadeList.push_back( createGrenade(Aztec,hTexBullets) );
			SoundEffectsList.push_back(PlaySoundEffect(PLAYER_THROW_GRENADE));
			Aztec->LowerGrenades();
		}

		for (unsigned int pi=0; pi<GrenadeList.size(); pi++ ) 
			MoveGrenade(GrenadeList[pi],dt,GROUND);	

				// with Boxes 
				float Minus = 0.0f;
				for(unsigned int i=0; i < BoxSprite->Objects.size(); i++)
				{ 
					if(  BoxSprite->Objects[i].GetLeftFace() < SCREENWIDTH && BoxSprite->Objects[i].GetRightFace() > 0 ) 
					{
					    // horizontal collision for object						
						if( HorizontalCollision = HorizontalCollisionDetection( *Aztec, BoxSprite->Objects[i]) )
						{  
							if( BoxSprite->Objects[i].GetLeftFace() > (Aztec->GetLeftFace()+40) && /*FACING_AZTEC == FACERIGHT*/Aztec->vDirection.x == 1 )
							{	RightSideCollision = true;  }
							else if (  BoxSprite->Objects[i].GetLeftFace() < (Aztec->GetLeftFace()+40) && /*FACING_AZTEC == FACELEFT*/Aztec->vDirection.x == -1 )
							{	LeftSideCollision = true;	}
						}
					
						// vertical collision for object						
						switch(BoxSprite->Objects[i].GetId())
						{
						case 1:   Minus = 3.0f;  break;
						case 2:	  Minus = 3.0f;  break;	
						case 3:	  Minus = 3.0f; break;		
						case 4:   Minus = 3.0f; break;		
						}
						VerticalCollision = ( VerticalCollisionDetection( *Aztec,BoxSprite->Objects[i],Minus ) );
						if( HorizontalCollision || VerticalCollision ) break;
					}	
				}
 ////////////////////////////   If already a collision is detected
				
				if( !HorizontalCollision &&!VerticalCollision )
				{
					for(unsigned int i=0; i < MixSprite->Objects.size(); i++) 
					{		
					  	  if( MixSprite->Objects[i].IsCollidable() &&  MixSprite->Objects[i].GetLeftFace() < SCREENWIDTH && MixSprite->Objects[i].GetRightFace() > 0 ) 
						  {	 
						  		// Horizontal collision
								if( HorizontalCollision = HorizontalCollisionDetection( *Aztec, MixSprite->Objects[i]) )
								{  
									if( MixSprite->Objects[i].GetLeftFace() > (Aztec->GetLeftFace()+40) && FACING_AZTEC == FACERIGHT )
									{	RightSideCollision = true;  }
									else if ( MixSprite->Objects[i].GetLeftFace() < (Aztec->GetLeftFace()+40) && FACING_AZTEC == FACELEFT )
									{	LeftSideCollision = true;	}
								}
								
								// Vertical collision
								switch(MixSprite->Objects[i].GetId())
								{
								case 5:   Minus = 50;  	break;  // small coil
								case 6:	  Minus = 10; 	break;  // big coil 
								case 7:	  Minus = 50;	break;  // for tree
								}
								
								VerticalCollision = ( VerticalCollisionDetection( *Aztec,MixSprite->Objects[i],Minus ) );
								if(  HorizontalCollision || VerticalCollision ) break;
						  }		
					}	
				} //end of if
	
				///////////////////////  Player Movement Logic //////////////////////////			
				if( ( STANCE_AZTEC == RUNNING || STANCE_AZTEC == LOWMOVE || STANCE_AZTEC == MOVE_BACK))
				{   
					if( Aztec->vPosition.x <= fBoundX && ( ( FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == 1.0f) || (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f ) ) )	
					{	
						if( RightSideCollision != true || /*(VerticalCollision == true && HorizontalCollision == true )*/(PLAYERSTATUS == ON_THE_OBJECT) ) 
							Aztec->Move(dt);
					}
					else
					if( ( (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == -1.0f ) || (FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == -1.0f) ) && Aztec->vPosition.x > -30.0f)  
					{	
						 if( LeftSideCollision != true || /*( VerticalCollision == true && HorizontalCollision == true )*/(PLAYERSTATUS == ON_THE_OBJECT) ) 
							Aztec->Move(dt);
					}

				}
						
				if( ( Aztec->vPosition.x > fBoundX ) && ( (FACING_AZTEC == FACERIGHT&&Aztec->vDirection.x == 1.0f) ||  (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f) ) && bMove )
					if( HorizontalCollision != true  || VerticalCollision || STANCE_AZTEC == JUMPING)
						switch (STANCE_AZTEC)
					{
						case JUMPING:	if(!Engine->Input_GetKeyState(HGEK_RIGHT)) break;
						case MOVE_BACK:
						case RUNNING:											
							sky.scrollX((0.05f) *dt,1);
							mountains.scrollX((0.06f) *dt,1);
							ground1.scrollX((0.6f) *dt,1);
							GrassSprite->Move((154.0f) *dt,-1);
							BoxSprite->Move((154.0f) *dt,-1);
							MixSprite->Move((154.0f) *dt,-1);
							fDistanceCovered += 0.3f;
							if (bEnding)
							{
								LSX -= 153.421f*dt;
								//ptrPro[0]->vPosition.x -= 153.421f*dt;
								//ptrPro[1]->vPosition.x -= 153.421f*dt;
							}
							for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= 153.421f*dt;
							for(unsigned int p = 0; p < pGameEnemyList.size() ; p++ )  pGameEnemyList[p]->vPosition.x -= 153.421f*dt;
							for(unsigned int p = 0; p < pDeadBodies.size() ; p++ )  pDeadBodies[p]->vPosition.x -= 153.421f*dt;
							for(unsigned int p = 0; p<GrenadeList.size(); p++ )	GrenadeList[p]->vPosition.x -= 153.421f*dt;
							for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= 153.421f*dt;
							for(unsigned int p = 0; p<vClouds.size(); p++ )	vClouds[p].pos.x -=  153.421f*dt*0.8;	
							for(unsigned int p = 0; p<vBonus.size(); p++ )	vBonus[p]->vPosition.x -=  153.421f*dt;	
							for(unsigned int p = 0; p<vListOfObjects.size(); p++ )	vListOfObjects[p]->x -=  153.421f*dt;	
							for(unsigned int p = 0; p<vScores.size(); p++ )	vScores[p].position.x -=  153.421f*dt;
							for(unsigned int p = 0; p<ParticleList.size(); p++ )
							{ 
								float x,y;
								ParticleList[p]->GetTransposition(&x,&y);
								x-= 153.421f*dt; 
								ParticleList[p]->Transpose( x,y );
							}
							break;		

						case LOWMOVE:	
							sky.scrollX((0.01f)*dt,1);
							mountains.scrollX((0.02f)*dt,1);
							ground1.scrollX((0.3f)*dt,1);
							GrassSprite->Move((77.0f)*dt,-1);
							BoxSprite->Move((77.0f)*dt,-1);
							MixSprite->Move((77.0f)*dt,-1);	
							fDistanceCovered += 0.3f;
							if (bEnding)
							{
								LSX -= 76.421f*dt;
							}
							for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= 76.421f*dt;
							for(unsigned int p = 0; p < pGameEnemyList.size() ; p++ ) pGameEnemyList[p]->vPosition.x -= 76.421f*dt;  // for enemies alive 
							for(unsigned int i = 0; i < pDeadBodies.size();     i++ ) pDeadBodies[i]->vPosition.x -= 76.421f*dt;  // for dead enemies
							for(unsigned int p = 0; p<vListOfObjects.size(); p++ )	vListOfObjects[p]->x -=  76.421f*dt;	
							for(unsigned int p = 0; p < GrenadeList.size();     p++ ) GrenadeList[p]->vPosition.x -= 76.421f*dt;
							for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= 76.421*dt;
							for(unsigned int p = 0; p<vBonus.size(); p++ )	vBonus[p]->vPosition .x -=  76.421f*dt;	
							for(unsigned int p = 0; p<vClouds.size(); p++ )	vClouds[p].pos.x -=  76.421f*dt*0.8;	
							for(unsigned int p = 0; p<vScores.size(); p++ )	vScores[p].position.x -=  76.421f*dt;
							for(unsigned int p = 0; p<ParticleList.size(); p++ )
							{ 
								float x,y;
								ParticleList[p]->GetTransposition(&x,&y);
								x-= 76.421f*dt;
								ParticleList[p]->Transpose( x,y );
							}
							break;
					}
  return false;
}

/////////////////////////////// CHECKS COLLISION OF ALL THE COLLIDABLE OBJECTS WITH BULLETS //////////////////////////////
void LauncherEffect( Bullet* Bult );
bool checkBulletCollision(std::vector<LevelObjects> &Box)
{
		
 for( unsigned int i=0; i<vInGameBullets.size(); i++ )  // for all the bullets	
 {
	for( unsigned int j=0; j<Box.size(); j++ )
	{ 
		if(  Box[j].IsCollidable() && !vInGameBullets[i]->IsDead()&& !Box[j].IsDead() )
		{		
			if(  Box[j].GetLeftFace() < SCREENWIDTH && Box[j].GetRightFace() > 0 )
			{
				    float Minus=0.0f, Xmas=0.0f; 
									 
					switch(Box[j].GetId())  // get id of the box
					{
					 case 1: Minus = 6.0f; 
						    if( Box[j].GetHealth() >= 51 ) Xmas = -6.0f;	
						   break;	
					 case 2: Minus = 7.0f; 
							if( Box[j].GetHealth() >= 51 ) Xmas = -6.0f;	
						   break;
					 case 3: Minus = 10.0f; 
						     Xmas = -5.0f;	
						   break;	
					 case 4: Minus = 10.0f; Xmas = 3.0f;	
							 Xmas = -5.0f;	
						   break;	
					 case 5: Minus = 55.0f; 
							if( vInGameBullets[i]->vDirection.x == 1 )  Xmas = 20.0f; 
							else Xmas = 4.0f; 
						   break;	
					 case 6: Minus = 15.0f;
							if( vInGameBullets[i]->vDirection.x == 1 )  Xmas = 8.0f;
							else Xmas = 15.0f; 
					}

						if( ObjectCollision( Box[j], *vInGameBullets[i], Xmas ,Minus)  )  // collision detected
						{
							int damage = 0;
							
							switch( vInGameBullets[i]-> GetId() )
							{
							case ASSAULTRIFLE_BULLET:   damage=12;   break;
							case SEMIAUTO_BULLET:	    damage=3;	 break; 
							case SHOTGUN_BULLET:	    damage=65;	 break; 	
							case ROCKETLAUNCHER_BULLET: damage=500;  break;	
							case ENEMYBULLET_TYPE1:     damage=4;    break;
							case ENEMYBULLET_TYPE2:     damage=6;   break;
							case ENEMYBULLET_TYPE3:     damage=10;   break;
							case ENEMYBULLET_TYPE4:     damage=12;   break;
							}

						   Box[j].DecreaseHealth(damage);
						   CreateEffect( vInGameBullets[i], Box[j], ParticleList );		 	
						   // kill bullets every collision
						   vInGameBullets[i]->Die();  // Bullet Will Die In the Move function
						   
						   eSOUNDEFFECTS PlayEffect=NULL_SOUND;

						   switch(Box[j].GetId())
						   {
						   case 1:  PlayEffect=HIT_WOOD; break;
						   case 2:  PlayEffect=(Box[j].GetHealth()>50)? HIT_METAL:HIT_WOOD;  break;
						   case 3:  
						   case 4:  PlayEffect=HIT_ROCK; break;
						   case 5:  
						   case 6:  PlayEffect=HIT_COIL; break;
						   }
						   if(vInGameBullets[i]->GetId()!=ROCKETLAUNCHER_BULLET)
						    SoundEffectsList.push_back(PlaySoundEffect(PlayEffect));
						   else 
						   {
							   SoundEffectsList.push_back(PlaySoundEffect(LAUNCHER_EXPLOSION));
							   Box[j].Die();
							   hgeParticleSystem* temp = 0;
							   float x = ( vInGameBullets[i]->vDirection.x < 0 ) ? vInGameBullets[i]->vPosition.x : vInGameBullets[i]->GetRightFace();
							   temp = ParticleFactory(BLAST,x,vInGameBullets[i]->vPosition.y, 0);
							   if(temp)   ParticleList.push_back(temp);
							   LauncherEffect( vInGameBullets[i] );
						   }

						   if( Box[j].IsDead() )   // delete from LevelObj List
						   {
							  Box[j].Die();
							   /// fire particle effect
							  GenerateBonus(Box[j],THIS_IS_LEVEL_NUMBER);
							   
							   switch(Box[j].GetId())
							   {
							   case 1:  PlayEffect=BREAK_WOOD; break;
							   case 2:  PlayEffect=BREAK_WOOD; break;
							   case 3:  PlayEffect=BREAK_ROCK; break;
							   case 4:  PlayEffect=BREAK_ROCK; break;
							   case 5:  PlayEffect=BREAK_COIL; break;
							   case 6:  PlayEffect=BREAK_COIL; break;
							   }	   
								     
								   
							   CreateEffect( vInGameBullets[i], Box[j], ParticleList );			
							   SoundEffectsList.push_back(PlaySoundEffect(PlayEffect));  								
							    
							   std::vector<LevelObjects>::iterator	Itr = Box.begin();
							   Itr += j;
							   Itr = Box.erase(Itr);
							   if( j != 0  && j != (Box.size()-1) ) j--;
							   //continue;						
						   }
						   else if( Box[j].GetHealth() <= 50 )
						   {
							   if( Box[j].GetId() == 1 || Box[j].GetId() == 2 )
							   {
							       Box[j].SetImage(DamageBoxTex);
								   if( !Box[j].bDamageFlag )
								   SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			
								 if ( vInGameBullets[i]->vDirection.x == -1 )
								  
									 Box[j].Spr->SetFlip(true,false,false); 
									 if( !Box[j].bDamageFlag )
									 SoundEffectsList.push_back( PlaySoundEffect(DAMAGE_BOX) );			
							   }
							   Box[j].bDamageFlag  = true;
						   }
				      }
			}
		}
	}
 }
 return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkBulletCollision( std::vector<Enemy*>& EnemyList )
{
	for ( unsigned int bul = 0; bul < vInGameBullets.size(); bul++)
	{
		eBULLETID BulId = vInGameBullets[bul]->GetId();
		if( BulId == ASSAULTRIFLE_BULLET || BulId == SEMIAUTO_BULLET || BulId == SHOTGUN_BULLET || BulId == ROCKETLAUNCHER_BULLET )
			for (unsigned int enm=0; enm<pGameEnemyList.size(); enm++ )
			{
				if( !pGameEnemyList[enm]->IsDead() && !vInGameBullets[bul]->IsDead() )
				{
					Enemy &enemy = *pGameEnemyList[enm];		
					Bullet &bullet = *vInGameBullets[bul];

					if ( !enemy.IsDead() && !bullet.IsDead() ) 
					{
						float Minus = 20.0f;
						float EnemyUpFace = enemy.GetUpFace(),
						   EnemyRightFace = enemy.GetRightFace(),
						    EnemyLeftFace = enemy.GetLeftFace(),
							R,L;	
					
						switch(enemy.GetId())
						{
						case HUMAN:     Minus = 20.0f;   R = 30.0; L = 58.0f;  break;
						case ALIEN1:   
						case ALIEN3:    Minus = 62.0f; R = 30.0f; L = 41.0f;  break;
						case ALIEN2:	Minus = 20.0f; R = 30.0f; L = 44.0f;  break;
						}	

						if( enemy.GetFacing() == FACELEFT )
						{
							EnemyRightFace -= R;
								EnemyLeftFace += L;						
						}
						else 
						{
							EnemyRightFace -= L; 
								EnemyLeftFace += R;							
						}
			

						if ( bullet.GetRightFace() > EnemyLeftFace && bullet.GetLeftFace() < EnemyRightFace )   // for X axis
						{ 
							if ( bullet.GetUpFace() < enemy.GetDownFace()   && bullet.GetDownFace() > enemy.GetUpFace()+Minus )	  // for Y axis
							{	
									int damage = 0;
									switch( vInGameBullets[bul]-> GetId() )
									{
									case ASSAULTRIFLE_BULLET:   damage=15;   break;
									case SEMIAUTO_BULLET:	    damage=11;	 break; 
									case SHOTGUN_BULLET:	    damage=40;	 break; 	
									case ROCKETLAUNCHER_BULLET: damage=100;  break;	
									}

									eSOUNDEFFECTS PlayEffect = NULL_SOUND;

									if(vInGameBullets[bul]-> GetId() != ROCKETLAUNCHER_BULLET )
									{   
										PlayEffect = ( EnemyList[enm]->GetId() == HUMAN )? (HIT_FLESH_HUMAN):(HIT_FLESH_ALIEN);	
									}
									else 
									{
										PlayEffect = LAUNCHER_EXPLOSION;
										hgeParticleSystem* temp = 0;
										float x = ( vInGameBullets[bul]->vDirection.x < 0 ) ? vInGameBullets[bul]->vPosition.x : vInGameBullets[bul]->GetRightFace();
										temp = ParticleFactory(BLAST,x,vInGameBullets[bul]->vPosition.y, 0);
										if(temp)   ParticleList.push_back(temp);
										EnemyList[enm]->Die();
										LauncherEffect(vInGameBullets[bul]);
									}

									SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );

									EnemyList[enm]->LowerHealth(damage);
									bullet.Die();
									enemy.LowerHealth(20);	
									if(enemy.IsDead())                          //////////////////////////////////////////////////// ENEMY DIES
									{	
										
										switch (EnemyList[enm]->GetId())
										{
										case HUMAN: PlayEffect = NULL_SOUND;  enemy.PlayDeathSound(EnemyDialogsList); AddScore(hgeVector(enemy.GetLeftFace() + 20,enemy.GetUpFace()),"+10",HUMAN_KILL);break;
										case ALIEN1: PlayEffect = DIE_ALIEN1; AddScore(hgeVector(enemy.GetLeftFace() + 20,enemy.GetUpFace()),"+15",ALIEN1_KILLS);break;
										case ALIEN2: PlayEffect = DIE_ALIEN2; AddScore(hgeVector(enemy.GetLeftFace() + 20,enemy.GetUpFace()),"+25",ALIEN2_KILLS);break;
										case ALIEN3: PlayEffect = DIE_ALIEN3; AddScore(hgeVector(enemy.GetLeftFace() + 20,enemy.GetUpFace()),"+20",ALIEN3_KILLS);break;
										}
										if(vInGameBullets[bul]-> GetId() != ROCKETLAUNCHER_BULLET )
										SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );	
										enemy.Die();
										//if(enemy.GetId()==HUMAN) GiveWeapon(&enemy);
									}


									CreateEffect(&bullet,ParticleList);	   //////////////////////////////////////////////////// SPECIAL EFFECTS 
							}
						}
					}
				}
			}
	}

	return false;
}



template<class T>
void DeleteVector(int i,std::vector<T*> &pG)
{
	std::vector<T*>::iterator itr=pG.begin();
	itr += i; 
	itr = pG.erase(itr);
}






void GiveWeapon(Enemy* enm)
{
	float x = enm->vPosition.x  ; 
	float y = enm->vPosition.y  ; 

	y += 60.0f;
	ePLAYER_STANCE facing = enm->GetFacing(); 
	if(facing == FACERIGHT)
		x += 60.0f;
	else { x += 20.0f; }
	WeaponObject*p = createWeaponObject(ASSAULTRIFLE,x,y) ;
	if(facing == FACELEFT) p->sprite->SetFlip(true,false);	
	p->SetAmmo(30);
	vWeaponList.push_back(p); 
}


WeaponObject* createWeaponObject(eWEAPONS wId,int x, int y)
{
	WeaponObject* retWep = NULL;
	eWEAPONTYPE wClass = PRIMARY ;
	if(wId==SEMIAUTO)	
		wClass = SECONDARY ;	
	retWep = new WeaponObject(wId, wClass, 50.0f, hgeVector(x,y), hgeVector(-1.0f,1.0f) );	
	retWep->Init(Engine,hTexBullets);
	return retWep;
}


Grenade* createGrenade(Protagonist* Azt, HTEXTURE hTex)
{	
	float x = Azt->vPosition.x;
	float y = Azt->vPosition.y;
	y+= 35.0f;
	(Azt->GetFacing()==FACERIGHT)? (x+=70) : (x+=50) ;
	float dx = (Azt->GetFacing()==FACERIGHT)? 1.0f : -1.0f;	

	Grenade*Gn = new Grenade( hgeVector(x,y), hgeVector(dx,-1.0f) );
	Gn->Init(hTex);

	if(dx == -1.0f)
		Gn->vSpeed.x -= 100.0f;

	return Gn;
}



Grenade* createGrenade(Enemy* enm, HTEXTURE hTex)
{	
	float x = enm->vPosition.x;
	float y = enm->vPosition.y;
	eWEAPONS id = GRENADE;

	if( enm->GetId() == ALIEN2 ) 
	{ 
		y+= 20.0f; id = GRENADE; 
	}
	else if(enm->GetId() == ALIEN1 || enm->GetId() == ALIEN3)
	{ 
		y+= 50; id = GRENADE; 
	}
	else
	{
		y+=60; id = LAUNCHER_GRENADE;
	}

	if( enm->GetId() == ALIEN2 )
	{
		x = (enm->GetFacing()==FACERIGHT)? (enm->GetRightFace()-50) : ( enm->GetLeftFace()+50 ) ;  
	}
	else if( enm->GetId() == ALIEN1 || enm->GetId() == ALIEN3 )
	{
		x = ( enm->GetFacing()==FACERIGHT)? (enm->GetRightFace()-30) : ( enm->GetLeftFace()+30 ) ;
	}
	else
	{
		x = ( enm->GetFacing()==FACERIGHT)? (enm->GetRightFace()-25) : ( enm->GetLeftFace()+25 ) ;
	}

	float dx = ( enm->GetFacing()==FACERIGHT)? 1.0f : -1.0f;	

	Grenade*Gn = new Grenade( hgeVector(x,y), hgeVector(dx,-1.0f), id );
	Gn->Init(hTex);

	if( enm->GetId() != HUMAN )
	{
		Gn->vSpeed.x = 185.0f + (rand()+1)%40;
		if(dx == 1.0f) Gn->vSpeed.x += 30;
		if( ( enm->vPosition.x - Aztec->vPosition.x ) > 610 ) Gn->vSpeed.x+=100;
	}

	return Gn;
}



void MoveGrenade(Grenade* grenade,float dt,const int GROUND)
{
	const float Gravity = 2.99f, Ground = GROUND-5;
	float dir = -1.0f;
	
	if( grenade == pSpecialGrenade && !Jester->IsDead() && grenade->vPosition.x < Jester->vPosition.x + 10.0f  ) 
	{ grenade->vDirection.x=0; grenade->vSpeed.x=0; }
	
	if( grenade->vDirection.x == -1 ) dir = 1.0f; 

	if(grenade->vPosition.y < Ground )
	{
		if(grenade->vPosition.y < 605 )grenade->bounceFlag = true;

		grenade->vSpeed.y += Gravity;
		if(grenade->vDirection.x == 1)
			grenade->fRotate += 0.05f;
		if(grenade->vDirection.x == -1)	
			grenade->fRotate += 0.05f*-1;	

	}
	else if(grenade->vSpeed.x > 0.1f  )
	{	
		if(grenade->bounceFlag )
		{ grenade->bounceFlag = false;	   SoundEffectsList.push_back( PlaySoundEffect(GRENADE_BOUNCE,20) ); }

		grenade->vSpeed.y=0.0f;
		grenade->vSpeed.x *= 0.94f;
		grenade->fRotate = grenade->vSpeed.x*0.05f*dir; 

		float cal = (grenade->vPosition.y - Ground); 
		cal*=cal/2.0f;
		grenade->vPosition.y = Ground - cal;
		grenade->vSpeed.y -= cal;	
	}
	else
	{
		grenade->vSpeed.y=0.0f;
		grenade->vDirection.y = 0.0f;
		grenade->vSpeed.x=0.0f;
		grenade->fRotate=0.0f;
	}

	grenade->vPosition.x += grenade->vDirection.x*(grenade->vSpeed.x*dt);
	grenade->vPosition.y += (grenade->vSpeed.y* ( dt * 2.5f ) );
}



void ExplosionEffectOnObjects(TileMap* Sprite, float fx)
{

	for (unsigned int bx=0; bx < Sprite->Objects.size(); bx++)
	{   
		LevelObjects& Box = Sprite->Objects[bx];
		if( !Box.IsDead() && Box.GetLeftFace() < 1370 && Box.GetRightFace() > 0 )
		{
			if( Box.GetRightFace() >=(fx-80.0f) && Box.GetLeftFace() <= (fx+80.f) && Box.IsCollidable() )
			{
				eSOUNDEFFECTS PlayEffect=NULL_SOUND;
				switch(Box.GetId())
				{
				case 1:  PlayEffect=BREAK_WOOD; break;
				case 2:  PlayEffect=BREAK_WOOD; break;
				case 3:  PlayEffect=BREAK_ROCK; break;
				case 4:  PlayEffect=BREAK_ROCK; break;
				case 5:  PlayEffect=BREAK_COIL; break;
				case 6:  PlayEffect=BREAK_COIL; break;
				}	   

				eParticles	par=GREY_SMOKE;
				float x,y;

				switch( Box.GetId() )
				{
				case 1:   
				case 2:   par = BROWN_SMOKE; break;
				case 3:   
				case 4:   par = GREY_SMOKE;  break; 
				case 5:
				case 6:   par = BLACK_SMOKE; break;  
				}	


				x = Box.GetRightFace() - Box.GetLeftFace();
				y = Box.GetDownFace() - Box.GetUpFace();
				x/=2; x += Box.GetLeftFace();  y /= 2.0f; y += Box.GetUpFace();

				ParticleList.push_back ( ParticleFactory(par,x,y-20,0) );
				ParticleList.push_back ( ParticleFactory(par,x,y+15,0) );

				SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
				Sprite->Objects.erase( Sprite->Objects.begin() + bx );		

				if( bx != 0  && bx != Sprite->Objects.size()-1 ) bx--;
			}
		}	
	}




};



void ExplosionAffect(float x)
{
		// enemies
		EffectOfExplosionOnEnemies(x,80);

		// Objects		
		ExplosionEffectOnObjects( BoxSprite, x);
		if( THIS_IS_LEVEL_NUMBER == 1 )
		ExplosionEffectOnObjects( MixSprite, x);
	
		// Player
		EffectOfExplosionOnProtagonist(x,80);
}



void MaintainGrenades(std::vector< Grenade*> &GrenadeList)
{
	for(unsigned int i=0; i<GrenadeList.size(); i++ )
		if( GrenadeList[i]->Explode() )
		{
			// allies
			if( iLevelOneEvents == 7 && pSpecialGrenade == GrenadeList[i] )
			{
				Jester->Die();		SoundEffectsList.push_back(PlaySoundEffect(DEATH_JESTER));
				Psycho->Die();		SoundEffectsList.push_back(PlaySoundEffect(DEATH_PSYCHO));
				Prophet->Die();		SoundEffectsList.push_back(PlaySoundEffect(DEATH_PROPHET));

				DialogLevelOne = new MusicPlayer(sound_engine);
				DialogLevelOne->Play(Diags_Misc[1]);
				pSpecialGrenade = 0;
				Bonus *Bon[]=
				{
					new Bonus(AMMO_ASSAULTRIFLE,hgeVector (Jester->vPosition.x+20, GROUND-17.0f) ),
					new Bonus(AMMO_ASSAULTRIFLE,hgeVector (Psycho->vPosition.x+20, GROUND-17.0f) ),
					new Bonus(AMMO_ASSAULTRIFLE,hgeVector (Prophet->vPosition.x+20,GROUND-17.0f) )	
				};
				for( int l=0; l<3; l++ ) { Bon[l]->bHorFlip = true;  Bon[l]->Init(hTexBullets); vBonus.push_back(Bon[l]);  }
				 
			}

			hgeParticleSystem *temp=0; 
			ExplosionAffect(GrenadeList[i]->vPosition.x+6.0f);

			temp = ParticleFactory(BLAST_DEBRIS,GrenadeList[i]->vPosition.x,GrenadeList[i]->vPosition.y - 30, 0);
			ParticleList.push_back(temp);

			temp = ParticleFactory(GRENADE_BLAST,GrenadeList[i]->vPosition.x,GrenadeList[i]->vPosition.y - 30, 0);
			temp->info.fDirection = 0;
			ParticleList.push_back(temp);
			temp = ParticleFactory(BLAST,GrenadeList[i]->vPosition.x,GrenadeList[i]->vPosition.y - 75, 0);
			ParticleList.push_back(temp);
			GrenadeList[i]->Release();
			delete GrenadeList[i];
			GrenadeList.erase(GrenadeList.begin()+i);
			SoundEffectsList.push_back(PlaySoundEffect(GRENADE_EXPLOSION));
		}
}



void ProcessSound(vector <SoundInfo> &EffectsList)
{
	for(int i=0; i<EffectsList.size(); i++)
	{
		Engine->Effect_PlayEx( EffectsList[i].hEffect ,EffectsList[i].iVolume );
	}
	while(!EffectsList.empty()) EffectsList.pop_back();
}

template<class T>  void RenderObjects(std::vector<T*> &Bul)
{
	for(unsigned int i=0 ; i<Bul.size(); i++)
	{
		Bul[i]->Render();
	}
}

///////////////////////////////////////////////////////////////////////////   Clearing Items On Game Exit/Restart

template< class T > void PopList(std::vector< T >  &List)
{   
	while( !List.empty() )   
	   List.pop_back();
}

template< class T >
void EraseList(std::vector< T > &List)
{
	while(!List.empty())	
	{
		List.pop_back();
	}
}


void EmptyLists()
{	
	
	EraseList(pGameEnemyList);
	EraseList(pDeadBodies);
	EraseList(vInGameBullets);
	EraseList(GrenadeList);
	EraseList(ParticleList);
	EraseList(LauncherEffectParticleList);
	EraseList(vListOfObjects);
	EraseList(ObjLevList);
	EraseList(vBonus);

	for(int i=0; i<vBirds.size(); i++)				delete vBirds[i].anim;
	for(int i=0; i<vBirds.size(); i++)				delete vBirds[i].falling;
	for(int i=0; i<vClouds.size(); i++)				delete vClouds[i].spr;
	for(int i=0; i<Leaves.size(); i++)				delete Leaves[i].spr;
	for(int i=0; i<vScores.size(); i++)				delete vScores[i].font_score;
	
	
	// PopList(vIdleStateEnemies);  //PopList(vWeaponList);
	PopList(ObjLevList);
	PopList(vListOfObjects);
	PopList(pDeadBodies);
	PopList(pGameEnemyList);
	PopList(vInGameBullets);
	PopList(GrenadeList);
	PopList(ParticleList);
	PopList(LauncherEffectParticleList);
	PopList(Leaves);
	PopList(vClouds);
	PopList(vBonus);
	PopList(vBirds);
	PopList(SoundEffectsList);
	PopList(EnemyDialogsList);
	PopList(vScores);
}



void spawnBS()
{
  
   Enemy* pEnm=0;
   ePLAYER_STANCE Facing=FACELEFT;
   eENEMY id = HUMAN;
   float dir = -1.0f;
   float x = 0.0f, y = 485.0f;
   EnemyCounterEnding++;	

	switch(rand()%2)
	{
	case 0:  Facing = FACERIGHT;
			 dir = 1.0f;
			 x = - 125 - ( rand()%50 );
		     break;
	default:  
			 Facing = FACELEFT;
			 dir = -1.0f;
			 x = SCREENWIDTH + 100 + ( rand()%201 );
			 break;
	}
										
   

   if(THIS_IS_LEVEL_NUMBER == 2)
   {
	 int num =  ( rand() % 2 ) ? (rand()%4) : ((rand()%3)+1);
	 switch(num)	
	 {
	 case 1: id = HUMAN; break;
	 case 2: id = ALIEN1; break;
	 case 3: id = ALIEN2; break;
	 case 4: id = ALIEN3; break;
	 }

	  y = 565.0f;
   }
	
   hgeVector vPos( x , y );
   pEnm = new Enemy ( id, Facing, RUNNING, vPos, hgeVector(dir,0.0f) );
   pEnm->Init(Engine,hTexEnemy,hSpeakerTex);
   pGameEnemyList.push_back(pEnm);
}



void checkExistance();
Enemy* CreateEnemy(int);
bool BringEnemy(int);
void ControlEnemy(Protagonist* &Aztec, Enemy* &, float dt) ;
void ManageEnemy(float dt, int level, Protagonist *Aztec)
{	
	if(iLevelOneEvents==9)
	{
		HoldOn.TimeOver();
	}

	 if( iLevelOneEvents < 5 && Spawn.TimerEnd() )
	 { 
		 BringEnemy(level ); 
	 }
	 else if( iLevelOneEvents == 9 && HoldOn.TimeOver() )
	 {

		 if( Spawn.TimerEnd() && pGameEnemyList.size() < 7 && EnemyCounterEnding < 45 )
		 { 
			 spawnBS();
		 }
	 }

	for( int i=0; i<pGameEnemyList.size(); i++ )
	{ 
		if( iLevelOneEvents < 5 &&  pGameEnemyList[i]->vPosition.x > 1390.0f ) { return; }
		else	
		if( iLevelOneEvents == 7  )
		{
		   if (	!pGameEnemyList[i]->IsDead() && pGameEnemyList[i]->GetStance() == IDLE && pGameEnemyList[i]->GetRightFace()< 60.0f )   
			pGameEnemyList[i]->ChangeStance(RUNNING);
		}
		else
		if( iLevelOneEvents == 9 && !pGameEnemyList[i]->IsDead() )
		{ 
			if( pGameEnemyList[i]->GetStance() == IDLE && pGameEnemyList[i]->GetRightFace() < 60.0f || pGameEnemyList[i]->vPosition.x > 1250.0f )
			    pGameEnemyList[i]->ChangeStance(RUNNING);
		}
		
		ControlEnemy( Aztec, pGameEnemyList[i], dt ); 
	}

}


///////////////////////////////////////////////////////////////////////////////////////
namespace
{
	float XXX[10]	 =   {  0,  0,  0,  0,   0,  0 ,  0,  0	,  0,   0	};
	const int SIZEOBJ = 47;
	IDFIRST LoadTheseObjects[SIZEOBJ] = 
	{
		TREE_DESTROYED,TREE_DESTROYED, ROCKS,ROCKS,ROCKS,ROCKS,ROCKS,ROCKS,GRAVELS,GRAVELS,CAR,GRAVELS,GRAVELS,GRAVELS,GRAVELS,GRAVELS,MEDIUM_GRASS,MEDIUM_GRASS,BUSHES,SMALLGRASS,SMALLGRASS,
		GRAVELS,TREE,TREE,TREE,TREE,TREE_DESTROYED,TREE_DESTROYED,TREE_DESTROYED,TREE_DESTROYED,TREE,TREE,TREE,TREE,TREE,TREE,TREE,CAR,ROCKS,ROCKS,ROCKS,ROCKS,ROCKS,ROCKS,ROCKS,GRAVELS,GRAVELS 
	};
}




void ProcessLevelOneEvents()
{
	if( iLevelOneEvents == 0 )
	{
		iLevelOneEvents = 1;
	}

	if( iLevelOneEvents == 1 )
	{
		LoadObjects(ObjLevList,LoadTheseObjects,SIZEOBJ,GROUND,SpriteSheetObj2);	
		DialogLevelOne = new MusicPlayer(sound_engine,str,3);
		DialogLevelOne->PlayTrack(0);
		iLevelOneEvents = 2;
		bAztecIsSpeaking = true;
	}
	else 
		if( iLevelOneEvents == 2 && !DialogLevelOne )
		{
			bAztecIsSpeaking = false;
			iLevelOneEvents = 3;			
			EraseList(ObjLevList);
			PopList(ObjLevList);
			Aztec->Release(Engine);
			if(DialogLevelOne) { DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne=0;  }
			sound_engine->stopAllSounds();
			delete Aztec;
			Aztec = new Protagonist;
			Aztec->vPosition.x = 20;
			Aztec->vPosition.y = 480;
			Aztec->Init(Engine);
			Aztec->ShotGun.SetAmmo( Aztec->ShotGun.GetAmmo() - 5 );
			Aztec->RocketLauncher.SetAmmo( Aztec->RocketLauncher.GetAmmo() - 5 );
			fDistanceCovered = 0.0f;
		}
		else
			if( iLevelOneEvents == 3 )
			{
				if(Engine->Input_GetKey()==HGEK_ENTER)
				{
					iLevelOneEvents = 4;
					GameLevelMusic->PlayTrack(0);
					if(DialogLevelOne) { DialogLevelOne->Stop(); delete DialogLevelOne;  }
					DialogLevelOne=0;	
				}
			}
			else
				if( iLevelOneEvents == 4 && bEnding)
				{
					iLevelOneEvents = 5;
					bAztecIsSpeaking = false;
					//SoundEffectsList.push_back(PlaySoundEffect(FLUTE_STINGER_1));
					if(GameLevelMusic)
					{
						GameLevelMusic->Stop();
						delete GameLevelMusic; 
						GameLevelMusic = 0;
					}
					GameLevelMusic = new MusicPlayer(sound_engine,newyork,2); GameLevelMusic->PlayTrack(0);	GameLevelMusic->SetVolume(1.0f);
				}
				else 
					if( iLevelOneEvents == 5 && Aztec->vPosition.x - LSX > 300 )
					{
						iLevelOneEvents = 6;
						if(DialogLevelOne) { DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne = 0; }
						DialogLevelOne = new MusicPlayer(sound_engine,conv_level_end,17);
						DialogLevelOne->PlayTrack(0);
					}
					else 
						if( iLevelOneEvents == 6 && DialogLevelOne == 0 && !GameLevelMusic )
						{
							iLevelOneEvents = 7;
//							if(GameLevelMusic){ GameLevelMusic->Stop(); delete GameLevelMusic;  GameLevelMusic=0; }
							DialogLevelOne = new MusicPlayer(sound_engine, finale, 6);
						}
						else
							if( iLevelOneEvents == 7 && Prophet->IsDead() && !DialogLevelOne && !GameLevelMusic && pGameEnemyList.size()==0 )
							{
								iLevelOneEvents = 8;
								fBoundX = 1250.0f;
								DialogLevelOne = new MusicPlayer(sound_engine,Diags_Misc+2,4);
								DialogLevelOne->PlayTrack(0);
							}
							else
							if( iLevelOneEvents == 8 && !DialogLevelOne )
							{
								iLevelOneEvents = 9;
								GameLevelMusic = LoadMusicPlayer(1010);
								GameLevelMusic->PlayTrack(2); 
								GameLevelMusic->SetVolume(0.5f); 
								fBoundX = 1250.0f;
								EnemyCounterEnding=0;
								HoldOn.setstart();
								bMove=false;
							}
							else
							if( iLevelOneEvents == 9 && pGameEnemyList.size() == 0 && EnemyCounterEnding >= 45 )
							{
								iLevelOneEvents = 10;
								if(DialogLevelOne) { DialogLevelOne->Stop(); delete DialogLevelOne; DialogLevelOne=0; }
								if(GameLevelMusic) { GameLevelMusic->Stop(); delete GameLevelMusic; GameLevelMusic=0; }
								GameLevelMusic = new MusicPlayer(sound_engine);
								GameLevelMusic->Play("Sound/music/p_win.ogg");
							}
							else
							if( iLevelOneEvents==10 && !GameLevelMusic )
							{
								iLevelOneEvents = 11; font->SetColor(0xffffffff);
							}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadObjects(std::vector<ObjectLevel*> &List,IDFIRST Objects[] ,const int SIZEOBJ, const float GND, HTEXTURE hTex )
{
	float x,y,w,h,hm,Place=0.0f;
	for(int i=0; i<SIZEOBJ; i++)
	{
		switch( Objects[i] )
		{
		case H_SPACE_5_PIX:		 Place += 5.0f;    continue; break;
		case H_SPACE_10_PIX:	 Place += 10.0f;   continue; break;
		case H_SPACE_100_PIX:	 Place += 100.0f;  continue; break;
		case H_SPACE_500_PIX:	 Place += 500.0f;  continue; break;
		case H_SPACE_1000_PIX:	 Place += 1000.0f; continue; break;
		
		case NIGHT_GRASS_MEDIUM: x = 0; y = 662;   w = 458;  h = 37;	hm=h;   break;
		case NIGHT_GRASS_SMALL:  x = 0; y = 641;   w = 268;  h = 20;	hm=h;   break;
		case TREE_DESTROYED:     x = 550; y = 350;   w = 200;  h = 366;	hm=h;	break;
		case TREE:		   x = 500; y = 0;   w = 250;  h = 350;	hm=h;			break;
		case ROCKS:		   x =   0; y = 204;   w = 482;  h = 100; hm=h;			break;
		case GRAVELS:	   x =   0; y = 0; w = 180;  h = 100; hm=h;				break;
		case CAR:		   x =   0; y = 100; w = 243;  h = 100; hm=h;			break;
		case SMALLGRASS:   x =   0; y = 301; w = 121;  h = 77;  hm=h;  hm -= 7;	break;
		case BUSH:		   x =   132; y = 301; w = 254;  h = 68; hm=h; hm -= 2;	break;
		case BUSHES:	   x =   0; y = 385; w = 475;  h = 75; hm=h;			break;
		case MEDIUM_GRASS: x =   0; y = 540; w = 405;  h = 100; hm=h;			break;
        case LARGE_GRASS:  x =   0; y = 480; w = 445;  h = 55; hm=h;			break;     
		default:   Place += 5.0f;    continue;     
		}
		
		ObjectLevel* ObjLev;
		ObjLev = new ObjectLevel;
		ObjLev->Sprite = new hgeSprite(hTex, x, y, w, h);
		ObjLev->ObjId = Objects[i];
		ObjLev->x = Place;
		ObjLev->y = GND - hm;
		ObjLev->w = w;
		ObjLev->h = h;
		List.push_back(ObjLev);
		Place += w+10.0f;	
	}
}





bool MPOE(float dt);
bool UpdateScene(float dt)
{
	if(DialogLevelOne )
	{
		if(DialogLevelOne->GetTrack() == 0 && DialogLevelOne->IsFinished() )
		{
			if(Engine->Input_GetKeyState(HGEK_ENTER))
			{
				DialogLevelOne->PlayTrack(1);
			}
		}
		else
		{
			int trk = DialogLevelOne->GetTrack();
			if(Engine->Input_GetKey()==HGEK_PERIOD)
			{
				if( trk < DialogLevelOne->GetTracks()-1 )
				{
					DialogLevelOne->PlayTrack(trk+1);	
				}
				else
				{
					DialogLevelOne->SetPlayPosition( DialogLevelOne->GetPlayPosition()+1000 );
				}
			}
			DialogLevelOne->PlayList();

			if( !DialogLevelOne->IsPlaying() )
			{
				DialogLevelOne->Stop();
				delete DialogLevelOne;
				DialogLevelOne = 0;
			}
		}
	}
	


	MPOE(dt);
	Aztec->Update(Engine,dt);
	

	if( Engine->Input_GetKey() == HGEK_1 && Aztec->pCurrentWeapon->GetWeaponID() != ASSAULTRIFLE )  
	{ 
		Aztec->SelectAssaultRifle();   SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
	}else 
		if( Engine->Input_GetKey() == HGEK_2 && Aztec->pCurrentWeapon->GetWeaponID() != SEMIAUTO )	
		{ 
			Aztec->SelectSideArm();        SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
		}

	    JumpAndCollision( dt, GROUND );

	if( Engine->Input_GetKeyState(HGEK_SPACE) && !Aztec->IsDead() )   /// FIRE WEAPON
	{   
		bool bWeaponisEmpty = Aztec->pCurrentWeapon->IsEmpty();
		if( Aztec->FireWeapon() )
		{
			if( !bWeaponisEmpty )
			{
				createBullet(Aztec, hTexBullets, Engine, vInGameBullets); 
				void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList);

				ShowGunSpark( Aztec, ParticleList );
				eSOUNDEFFECTS PlayEffect = NULL_SOUND;
				switch( Aztec->pCurrentWeapon->GetWeaponID() )
				{
				case ASSAULTRIFLE:   PlayEffect=FIRE_ASSAULT_RIFLE; break;
				case SEMIAUTO:       PlayEffect=FIRE_PISTOL;		break;
				case SHOTGUN:	     PlayEffect=FIRE_SHOTGUN;		break;	
				case ROCKETLAUNCHER: PlayEffect=ROCKET_LAUNCHER;	break;
				}
				SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );
				
			}
			else
				SoundEffectsList.push_back( PlaySoundEffect(WEAPON_EMPTY) );
		} // end of if block that is operated around the fire call
	}

	/////////////////////////////////////////////////////////////////////////

	for (unsigned  int i=0; i<ParticleList.size(); i++ )  ParticleList[i]->Update(dt);		   
	ManageParticleList(ParticleList);	

	ProcessSound(SoundEffectsList);
	
	Move( vInGameBullets, dt,Engine );	
	UpdateCloud(vClouds,dt);
	UpdateLeaves(Leaves);
	UpdateBirds(vBirds,dt);
	MaintainGrenades(GrenadeList);

	


	return false;
}

bool MPOE(float dt)
{
	if( Aztec->GetStance() == DUCK && Aztec->GetFrame() == 0 && !Aztec->IsPlaying() )  {	Aztec->ChangeStance(IDLE);	}

	ePLAYER_STANCE STANCE_AZTEC = Aztec->GetStance();
	ePLAYER_STANCE FACING_AZTEC = Aztec->GetFacing();
	RightSideCollision = LeftSideCollision = false;
	HorizontalCollision  = VerticalCollision = false;				

	if(  STANCE_AZTEC != THROW_GRENADE )  {	grenadeflag = false; }
	else if( Aztec->GetFrame() != 3 )	  {	grenadeflag = true;  }
	if(  STANCE_AZTEC == THROW_GRENADE &&  Aztec->GetFrame() == 3 && grenadeflag)  
	{	
		grenadeflag = false;
		GrenadeList.push_back( createGrenade(Aztec,hTexBullets) );
		SoundEffectsList.push_back(PlaySoundEffect(PLAYER_THROW_GRENADE));
		Aztec->LowerGrenades();
	}
	for (unsigned int pi=0; pi<GrenadeList.size(); pi++ ) 
		MoveGrenade(GrenadeList[pi],dt,GROUND);	


	///////////////////////  Player Movement Logic //////////////////////////			
	if( ( STANCE_AZTEC == RUNNING || STANCE_AZTEC == LOWMOVE || STANCE_AZTEC == MOVE_BACK))
	{   
		if(Aztec->vPosition.x <= fBoundX && ( ( FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == 1.0f) || (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f ) ) )	
		{	
				Aztec->Move(dt);
		}
		else
			if( ( (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == -1.0f ) || (FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == -1.0f) ) && Aztec->vPosition.x > -30.0f)  
					Aztec->Move(dt);
	}

	if( ( Aztec->vPosition.x > fBoundX ) && ( (FACING_AZTEC == FACERIGHT&&Aztec->vDirection.x == 1.0f) ||  (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f) ) && bMove )
		if( HorizontalCollision != true  || VerticalCollision || STANCE_AZTEC == JUMPING)
			switch (STANCE_AZTEC)
		{
			case JUMPING:	if(!Engine->Input_GetKeyState(HGEK_RIGHT)) break;
			case MOVE_BACK:
			case RUNNING:											
				sky.scrollX((0.05f) *dt,1);
				mountains.scrollX((0.06f) *dt,1);
				ground1.scrollX((0.6f) *dt,1);
				
				for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= 153.421f*dt;
				for(unsigned int p = 0; p<GrenadeList.size(); p++ )	GrenadeList[p]->vPosition.x -= 153.421f*dt;
				for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= 153.421f*dt;
				for(unsigned int p = 0; p<vClouds.size(); p++ )	vClouds[p].pos.x -=  153.421f*dt*0.8;	
				for(unsigned int p = 0; p<ObjLevList.size(); p++ ) ObjLevList[p]->x -= 153.421f*dt; 
				for(unsigned int p = 0; p<vScores.size(); p++ ) vScores[p].position.x -= 153.421f*dt;
				for(unsigned int p = 0; p<ParticleList.size(); p++ )
				{ 
					float x,y;
					ParticleList[p]->GetTransposition(&x,&y);
					x-= 153.421f*dt; 
					ParticleList[p]->Transpose( x,y );
				}
				break;		

			case LOWMOVE:	
				sky.scrollX((0.01f)*dt,1);
				mountains.scrollX((0.02f)*dt,1);
				ground1.scrollX((0.3f)*dt,1);
				
				for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= 76.421f*dt;
				for(unsigned int p = 0; p < GrenadeList.size();     p++ ) GrenadeList[p]->vPosition.x -= 76.421f*dt;
				for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= 76.421*dt;
				for(unsigned int p = 0; p<vBonus.size(); p++ )	vBonus[p]->vPosition .x -=  76.421f*dt;	
				for(unsigned int p = 0; p<ObjLevList.size(); p++ ) ObjLevList[p]->x -= 76.421f*dt; 
				for(unsigned int p = 0; p<ParticleList.size(); p++ )
				{ 
					float x,y;
					ParticleList[p]->GetTransposition(&x,&y);
					x-= 76.421f*dt;
					ParticleList[p]->Transpose( x,y );
				}
				break;
		}


return false;
}

bool RenderScene()
{

	if( iLevelOneEvents == 0 ) return false;
	
	sky.Render(0,0);
	mountains.Render(0,464);
	/*RenderBirds(vBirds);*/
	for(int i=0; i<ObjLevList.size(); i++)	ObjLevList[i]->Render();
	
	ground1.Render(0,615);
	ground1.Render(256,615);
	ground1.Render(512,615);
	ground1.Render(768,615);
	ground1.Render(1024,615);
	ground1.Render(1280,615);

	RenderObjects(vInGameBullets); 
	Aztec->Render();
	RenderObjects(GrenadeList);	
	RenderObjects(vBonus);	
	RenderCloud(vClouds);	
	
		

	for (unsigned int i = 0 ; i < ParticleList.size(); i++ )
		if (ParticleList[i])  ParticleList[i]->Render();

	if(DialogLevelOne)
	{
		if( DialogLevelOne->GetTrack() == 0 && DialogLevelOne->IsFinished() )
		{
			font->SetColor(0xff000000);
			font->printf(350,350,0,"Prophet Is Asking You About Your Safe Landing, Press Enter To Reply");		  
		}

		if(DialogLevelOne->IsPlaying())
		{
			AztecSpeaks->RenderEx(50,700,fAngleSpeaker);
		}
	}

	//////////////////////////Displays Pause Menu when pressed ESC 	
	return false;
}



void LauncherEffect(Bullet* Bult)
{
	 const float center = Bult->vPosition.x + (Bult->GetWidth()/2);
	 const int BlastRadius  = 40;

	 EffectOfExplosionOnEnemies( center , 40 ); 
	 EffectOfExplosionOnProtagonist( center, 80 );
	 	
}

void EffectOfExplosionOnEnemies( const float center, const int BlastRadius )
{
   const float  ImpactLeft = center - BlastRadius;
   const float ImpactRight = center + BlastRadius;

   for( int i=0; i<pGameEnemyList.size(); i++ )		
   {
		 if( pGameEnemyList[i]->IsDead() ) 	continue;
		
		 const Enemy* EnmPtr = pGameEnemyList[i];	
		 float faceLeft = EnmPtr->GetLeftFace(), faceRight=EnmPtr->GetRightFace();	
		 const ePLAYER_STANCE FACING = EnmPtr->GetFacing();

		 switch(EnmPtr->GetId())
		 {
		 case HUMAN: 
		     ( FACING == FACERIGHT ) ? ( faceLeft += 25.0f, faceRight -= 40.0f ) : (faceRight -= 25.0f,  faceLeft += 40.0f );
			 break; 
		 case ALIEN1: 
		 case ALIEN2:
		 case ALIEN3:
			 ( FACING ==  FACELEFT ) ? ( faceLeft += 43.0f, faceRight -= 25.0f ) : (faceRight -= 43.0f, faceLeft += 25.0f  );
			 break;
		 }// end of switch			
		
		// check for collision
		
		 if( ImpactLeft < faceRight && ImpactRight > faceLeft )
		 {
			 AddScore(hgeVector(pGameEnemyList[i]->vPosition.x, pGameEnemyList[i]->vPosition.y),"+10",HUMAN_KILL);
			pGameEnemyList[i]->Die();
			pGameEnemyList[i]->PlayDeathSound(EnemyDialogsList);
		 } 	
   }// end for for loop			
}


void EffectOfExplosionOnProtagonist( const float center, const int BlastRadius )
{
	const float AzCentre = ( Aztec->GetFacing() == FACERIGHT ) ? ( Aztec->GetRightFace() - 65.0f ) : ( Aztec->GetLeftFace() + 65.0f ); 
	const float expDistance = center - AzCentre;  // distance between protagonist and blast
	float ReduceHealth = 0.0f;	


	if(  ( expDistance >= 0 && expDistance < BlastRadius ) )
	{
		if( expDistance <= BlastRadius/4 )			ReduceHealth = 75.0f;
		else 
			if( expDistance <= BlastRadius/3 )		ReduceHealth = 50.0f;
			else 
				if( expDistance <= BlastRadius/2 )	ReduceHealth = 25.0f;
				else 
				{
					ReduceHealth = 15.0f;
				}

		SoundEffectsList.push_back(PlaySoundEffect(PLAYER_PAIN));	
		Aztec->LowerHealth(ReduceHealth);
	}
	else if( expDistance <= 0 && expDistance > -BlastRadius )
	{
		if( expDistance >= -BlastRadius/4 )			ReduceHealth = 75.0f;
		else 
			if( expDistance >= -BlastRadius/3 )	    ReduceHealth = 50.0f;
			else 
				if( expDistance >= -BlastRadius/2 )	ReduceHealth = 25.0f;
				else 
					ReduceHealth = 15.0f;
				
		SoundEffectsList.push_back(PlaySoundEffect(PLAYER_PAIN));	
		Aztec->LowerHealth(ReduceHealth);
	}
	
	

return;
}