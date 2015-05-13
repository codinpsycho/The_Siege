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





#include "StateLevel2.h"
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

const int SIZEOBJT = 63; 

IDFIRST Level2Objects[SIZEOBJT] = 
{
   BUSH, 	   		   BUSH, 	   		   BUSH, 	   		   BUSH, 	   		   LARGE_GRASS, 	   LARGE_GRASS, 	   LARGE_GRASS, 		//  7   
   SMALLGRASS,         SMALLGRASS,         SMALLGRASS,         SMALLGRASS,         SMALLGRASS,         SMALLGRASS,         SMALLGRASS,			// 14   
   TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE, 			   TREE,				// 21
   TREE, 			   TREE, 			   CAR, 			   TREE, 			   TREE, 			   TREE, 			   TREE,				// 28
   TREE, 			   TREE, 			   SMALLGRASS, 		   TREE_DESTROYED,	   TREE_DESTROYED,	   TREE, 			   TREE,				// 35
   SMALLGRASS,         SMALLGRASS,         CAR,                BUSH,               BUSH,               NIGHT_GRASS_MEDIUM, NIGHT_GRASS_MEDIUM,  // 42   
   NIGHT_GRASS_MEDIUM, TREE, 			   ROCKS, 			   TREE, 			   TREE, 			   TREE, 			   TREE,				// 49
   TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,     TREE_DESTROYED,		// 54		
   ROCKS,			   ROCKS,			   CAR,			       GRAVELS,			   TREE_DESTROYED,	   GRAVELS,			   GRAVELS,				// 63
};

/////////////////// Function Prototypes ///////////////////////////////////////////////////////////////////////////////////////////////
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
bool JumpAndCollision(float dt);									       // Jump And Object
bool checkBulletCollision(std::vector<LevelObjects>&);  // check all the bullets in the scene
bool MovePlayerOnEarth( float dt );								   // Move Player Left or Right
void ManageEnemy(float dt, int level,Protagonist*);				   // manage Enemies;
bool checkBulletCollision(std::vector<Enemy*>&);
void RenderHUD();
void UpdateHUD();
void GenerateBonus(LevelObjects&Lov, const int i);
Bullet* createEnemyBullet(Enemy* enemy, HTEXTURE hTex, HGE* Engine,std::vector< Bullet* > &vInGameBullets);
void AddScore(hgeVector _position, char* _score, enum eScores);
void UpdateScores(vector<ScoreUp> &vScores);
void RenderScores();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcessSound(vector <SoundInfo> &EffectsList);
template<class T>  
void RenderObjects(std::vector<T*> &Bul);
void MaintainGrenades(std::vector< Grenade*> &GrenadeList);
bool HorizontalCollisionDetection( Protagonist &Pro, LevelObjects &BoxObject );
inline bool VerticalCollisionDetection( Protagonist &Pro, LevelObjects &BoxObject, float );
void GiveWeapon( Enemy* enm );
WeaponObject* createWeaponObject( eWEAPONS wId,int x, int y );
Grenade* createGrenade( Protagonist* Azt, HTEXTURE hTex );
void MoveGrenade( Grenade* grenade, float dt , const int);
void checkExistance();
void BulletCollisionPro(  );
MusicPlayer* LoadMusicPlayer(int i);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Extern Game Engine Pointer and Game State Manager
extern GameStateManager *Manager ;
extern HGE *Engine;
extern ISoundEngine* sound_engine;

// constants
const int SCREENWIDTH = 1366;     
const int SCREENHEIGHT = 768;

////Tile Map Objects
extern TileMap *GrassSprite;
extern TileMap *BoxSprite;
extern TileMap *MixSprite;
// Particle Effect Variables
extern hgeParticleSystem * NewParticleEffect;
extern hgeSprite *ParSprite;
extern hgeSprite *blastSprite;
extern hgeSprite *GrenadeBlastSprite;
extern hgeSprite *GunSparkSprite;
extern hgeSprite *FireHitSprite;

extern hgeSprite *Health;
extern hgeSprite *CurWeapon;
extern hgeSprite *LostShip;
extern hgeSprite *SolarGun;
extern hgeFont *font;

// layers
//Custom Sprite Objects for scrolling
sprite sky2(0,0,SCREENWIDTH,400);
sprite jungle(0,0,SCREENWIDTH,316);
sprite ground(0,0,SCREENWIDTH,91);
sprite bushes(0,0,SCREENWIDTH,359);

const int xPos = 30;  //Starting Position for Tile Map Objects
extern float fAlpha;
extern bool bShowInfo;  
extern bool paused;

// texture
extern HTEXTURE healthTex;
extern HTEXTURE DamageBoxTex;
extern HTEXTURE groundtex ;
extern HTEXTURE boxtex;
extern HTEXTURE cur;
extern HTEXTURE rest;
extern HTEXTURE res;
extern HTEXTURE ex;
extern HTEXTURE hTexEnemy;
extern HTEXTURE hTexBullets;
extern HTEXTURE ParTex;
extern HTEXTURE GunSparkTex;
extern HTEXTURE FireHitTex;
extern HTEXTURE hLeafTex;
extern HTEXTURE blast;
extern HTEXTURE texBirds;
extern HTEXTURE Objects;
extern HTEXTURE hCallOutTex;
extern HTEXTURE hSpeakerTex;
extern HTEXTURE hGroundTex;
extern HTEXTURE PauseMenuTex;
extern HTEXTURE SpriteSheetObj2;
extern HTEXTURE Fallingtex;

	   HTEXTURE objects;
	   HTEXTURE hLevel2tex;
	   HTEXTURE hVtolTex;
	   HTEXTURE hTexNames;


extern Protagonist *Aztec;     // Aztec - protagonist 
extern char*pStrTexEnemy;
extern char*pStrBullets;
extern hgeSprite *PauseMenuSpr;
extern hgeSprite *CallOutSpr;
extern hgeSprite *sprGrenade;
hgeSprite *Level2Spr=0, *sprNames;
hgeSprite *AztecSpeaks = 0;

TileMap *obj = 0;

const float GROUND = 700.0f;        // the height of ground 
const float GRAVITY = 0.20f;
static float EscapeVelocity = 0.0f; 
extern float fDistanceCovered;
extern int EnemyCounterEnding;      // this counts the number of enemies generated in the end of this level
extern int Total_Score,Total_kills;				//Variables for Scoring and stats
extern int Birds_killed, hits_sustained, Box_destroyed,Melees, Bullets_Wasted; //

extern float fBoundX;
extern bool bMove;
extern bool bEnding;
////////////// FLAGS ////////////////////////////
extern bool RightSideCollision;
extern bool LeftSideCollision;
extern bool HorizontalCollision;
extern bool VerticalCollision;
extern bool WeaponCollision;
extern bool grenadeflag;
extern bool bMeleeFlag;
extern bool bDisplayBonusMessage;
extern bool bActivateShotgun ;
extern bool bActivateLauncher;
extern CONDITION PLAYERSTATUS;
static bool flagPlay = true; 
bool bEventOccur = false;
unsigned int iEventNumber = 0;
unsigned int iSpawnEnemies = 0;
bool bAztecIsSpeaking = false;
bool LevelStartFlag = true;
/////////////////////////////////////////////////
extern bool bGameOver;
extern Timer GameOver;
extern Timer HoldOn;
extern Timer Spawn;
/////////////////////////////////////////////////

extern std::vector< Enemy*  > pDeadBodies;             // list of pointers to dead bodies of enemies 
extern std::vector< Enemy*  > pGameEnemyList;          // list of pointers to enemy
extern std::vector< Bullet* > vInGameBullets;		   // list of pointers to bullets
extern std::vector< WeaponObject* > vWeaponList;       // list of weapon objects to be rendered
extern std::vector< hgeParticleSystem* > ParticleList; // list of particle effects in the scene extern std::vector< Bullet* > vInGameBullets; 
extern std::vector< Leaf        > Leaves;
extern std::vector< Cloud       > vClouds;
extern std::vector< Bonus*      > vBonus;
extern std::vector< Bird        > vBirds;
extern std::vector< Grenade*    > GrenadeList;
extern std::vector< SoundInfo   > SoundEffectsList;
extern std::vector< InfoDialog  > EnemyDialogsList;
extern std::vector< ObjectLevel*> vListOfObjects;
extern std::vector< hgeParticleSystem* > LauncherEffectParticleList; 
std::vector< ObjectLevel*> vListOfCars;
extern vector<ScoreUp> vScores;
static Enemy* pDeadEnemyFound = 0;
extern MusicPlayer *KeyMusicPlayer;
extern MusicPlayer *GameLevelMusic;
	   MusicPlayer *Transmission,*Music;

static Timer DeathTimer(2000);

void LoadTransmission(int i,MusicPlayer*&ptr);
bool JumpAndCollision(float dt,const int);
bool MovePlayerOnEarth2( float dt );
bool CheckMelee(Protagonist*, TileMap* );
void ShowGunSpark(Protagonist* Aztec, vector<hgeParticleSystem*> &ParticleList);
void checkExistance();
void ManageEnemyLevel2(float dt, Protagonist *Aztec);
void ProcessLevel2Events();
void ProcessBonus();
void ProcessLevelObjects();
void GenerateItemsLevel2();
void ClearBoxSprite();
void Bullet2BulletCollision( Bullet* bPtr );
void updateVtol(float dt);
void ShowNames();


StateLevel2::StateLevel2(void)
{

}

StateLevel2::~StateLevel2(void)
{

}



#define SIEGE_LEVEL_2 2 
extern int THIS_IS_LEVEL_NUMBER;

float iAlpha = 255.0f;
bool bLevel2BeginScene;
bool bBringVtol = false;
bool bPlayerEntersVtol = false, bVtolFlagX = false, bVtolFlagY = false, bPlayerGetInFlag = false, bShowNames = false ;
int names=0;


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

Timer Takeoff(4000);
VTOL *vtol=0;
float HudRenderPointY = 718.0;
float HudRenderPointX = 0.0;
float HudRenderPointX2 = 1126.0f;
float HudRenderPointY2 = 718.0f;
hgeSprite *HudWeapon;
hgeFont *fontHud;
HTEXTURE  HUDtex, HUDtexAmmo ;
hgeSprite *HUDspr=0, *HUDsprAmmo=0 ;

void InitHud();
void ReleaseHud();
void RenderHud();

namespace
{
  HTEXTURE L2_SkyTex,L2_JungleTex,L2_GroundTex,L2_Bushes;
}




bool bGameIsInTheFinalStage = false;
extern bool bLOAD_END;
hgeParticleSystem *CarOnFire=0,*CarFireOnSmoke=0,*JetThrust=0;
ObjectLevel *FireCar = 0;
MusicPlayer *JetThrustSound=0;
static bool GOD_MODE_FLAG=false;


bool StateLevel2::Init()
{
	THIS_IS_LEVEL_NUMBER = SIEGE_LEVEL_2;
	GameStateManager* Manger;
	Manger = new GameStateManager;
	////////////////////
	//Loads All Textures
	   L2_SkyTex = Engine->Texture_Load( "Textures/Level2/sky.png" );
	L2_JungleTex = Engine->Texture_Load( "Textures/Level2/jungle.png" );
	L2_GroundTex = Engine->Texture_Load("Textures/Level2/ground.png");
	  L2_Bushes  = Engine->Texture_Load("Textures/Level2/bushes.png");

	sky2.LoadTexture(L2_SkyTex);
	jungle.LoadTexture(L2_JungleTex);
	ground.LoadTexture(L2_GroundTex);
	bushes.LoadTexture(L2_Bushes);

	boxtex = Engine->Texture_Load("Textures/Level1/boxesprite.png");
	DamageBoxTex = Engine->Texture_Load("Textures/Level1/damagebox.png");
	hLevel2tex = Engine->Texture_Load("textures/level2/level2intro.png");
	////////////////////////////////////////////////////////////////////////////////////////////////
	cur = Engine->Texture_Load("Textures/Game Paused/cur1.png");
	rest = Engine->Texture_Load("Textures/Game Paused/Restart.png");
	res = Engine->Texture_Load("Textures/Game Paused/resume.png");
	ex = Engine->Texture_Load("Textures/Game Paused/exit.png");
	hCallOutTex = Engine->Texture_Load("Textures/Level1/callout.png");

	ParTex = Engine->Texture_Load("Particle Effects/particles.png");
	GunSparkTex = Engine->Texture_Load("Particle Effects/particles.png");
	FireHitTex = Engine->Texture_Load("Particle Effects/particles.png");
	hLeafTex = Engine->Texture_Load("Textures/Level1/leaf.png");
	Objects = Engine->Texture_Load("Textures/Level1/level1obj.png");
	objects = Engine->Texture_Load("textures/level2/level2obj.png");
	blast = Engine->Texture_Load("Sprites/particles.png");
	texBirds = Engine->Texture_Load("Sprites/bird.png");
	Fallingtex = Engine->Texture_Load("sprites/falling.png");
	SpriteSheetObj2 = Engine->Texture_Load("Sprites/SiegeObjects2.png");

	hTexEnemy = Engine->Texture_Load(pStrTexEnemy);
	hTexBullets = Engine->Texture_Load(pStrBullets);
	healthTex = Engine->Texture_Load("Textures/Level1/health.png");
	PauseMenuTex = Engine->Texture_Load("Textures/Game Paused/blur.png");
	PauseMenuSpr = new hgeSprite (PauseMenuTex,0,0,1366,768);

	////////////////////////////////////////////////////////////////////////////////////////////////
	   hTexNames = Engine->Texture_Load("Textures/credits/credits.png");
	   sprNames = new hgeSprite(hTexNames,0,0,768,768);
	   
	hSpeakerTex = Engine->Texture_Load("Sprites/speaker.png");
	if(!hSpeakerTex)  MessageBox(0,"/Sprites/speaker.png","File Not Found",MB_OK);
	hVtolTex = Engine->Texture_Load("Sprites/vtol.png");
	vtol =  new VTOL();
	vtol->Init(hVtolTex);	
	/////////////////////////////////////////////
	//////  Initialization Required For Player
	Aztec = new Protagonist;
	Aztec->vPosition.x = 20;
	Aztec->vPosition.y = 565;
	Aztec->Init(Engine);
	HorizontalCollision = false;
	VerticalCollision = false;
	EscapeVelocity = 0.0f;	
	PLAYERSTATUS=ON_THE_GROUND;
	RightSideCollision = false;
	LeftSideCollision  = false;
	WeaponCollision = false;
	grenadeflag = false;
	bMeleeFlag = false;
	bAztecIsSpeaking = false;
	fBoundX = 350.0f;
	fDistanceCovered = 0.0f;
	iEventNumber = 0;
	pDeadEnemyFound = 0;
	Transmission = 0;
	AztecSpeaks = 0;
	iAlpha=255.0f;
	bMove = true;
	bEventOccur = false;
	bActivateShotgun = false;
	bActivateLauncher = false;
	bGameOver = false;
	bEnding = false;
	bMove = true;
	LevelStartFlag = true;
	bShowInfo = true;
	flagPlay = true;
	bDisplayBonusMessage = false;
	bBringVtol = false;
	bPlayerEntersVtol = false;
	bPlayerGetInFlag = false ;
	bVtolFlagX = bVtolFlagY = false ;
	bShowNames = false ;
	EnemyCounterEnding=0; 
	iSpawnEnemies = 0;
	Spawn.setEndTime(1200);
	/////////////////////////////////////////////
	GUI = new hgeGUI();
	//Sets Cursor
	cursor = new hgeSprite(cur,0,0,32,32);
	//Allocates memory to tile map pointers
	obj = new TileMap()	;
	BoxSprite = new TileMap();
	MixSprite = 0;
	sprGrenade  = new hgeSprite(Objects,270,100,30,20);
	Health	  = new hgeSprite(healthTex,0,0,20,20);
	CurWeapon   = new hgeSprite(Objects,0,0,360,200);
	SolarGun	  = new hgeSprite(hTexBullets,90,0,75,40);
	blastSprite = new hgeSprite(blast,32,0,32,32);
	GrenadeBlastSprite = new hgeSprite(blast,32,0,32,32);	 
	CallOutSpr = new hgeSprite(hCallOutTex,0,0,158,46);
	AztecSpeaks = new hgeSprite( hSpeakerTex,0,0,80,75 );
	AztecSpeaks->SetHotSpot( 40,32 );
	//Init Sprites needed for Particle Effects 
	font = new hgeFont("Fonts/font.fnt");	//Init Font
	ParSprite = new hgeSprite(ParTex,0,96,32,32);
	GunSparkSprite = new hgeSprite(GunSparkTex,64,64,32,32);
	FireHitSprite = new hgeSprite(FireHitTex,64,64,32,32);
	Level2Spr= new hgeSprite(hLevel2tex,0,0,1366,768);
	GrenadeBlastSprite->SetBlendMode(BLEND_ALPHAADD);
	blastSprite->SetHotSpot(16,16);
	ParSprite->SetHotSpot(16,16);
	GunSparkSprite->SetBlendMode(BLEND_ALPHAADD );
	FireHitSprite->SetBlendMode(BLEND_ALPHAADD);
/////////////////////////////////////////////////////////////
	
	BoxSprite->Read("BoxTile2.txt");
	BoxSprite->SetPos(xPos,470);
	BoxSprite->SetTileImage(boxtex);
	BoxSprite->CreateLevel();       //Converts DATA into LevelObjects 
	
	obj->Read("level2obj.txt");
	obj->SetPos(200,0);
	obj->SetTileImage(objects);
	obj->CreateLevel();


	//Init GUI  
	GUI->SetCursor(cursor);

	//Adds Buttons to Pause Menu
	GUI->AddCtrl(new Button(1,100,200,res,res,res));
	GUI->AddCtrl(new Button(2,100,240,rest,rest,rest));
	GUI->AddCtrl(new Button(3,70,280,ex,ex,ex));
	GUI->SetNavMode(HGEGUI_CYCLED | HGEGUI_UPDOWN);
	
	

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
	
	KeyMusicPlayer =  LoadMusicPlayer(1000);
	GameLevelMusic =  LoadMusicPlayer(2);
	Music =  new MusicPlayer(sound_engine);
	
	LoadTransmission(1,Transmission);

	if( Transmission )  
	{   // Transmission->PlayTrack(0);	
		bMove = false;  	
	}
	
	void LoadEnd();
	if(bLOAD_END) { LoadEnd(); bLOAD_END = false; }
	else
	{
		LoadObjects(vListOfObjects, Level2Objects, SIZEOBJT, GROUND+3, SpriteSheetObj2 );
	}
	
	for(unsigned int p = 0; p<vListOfObjects.size(); p++ )	
	{
		if( vListOfObjects[p]->ObjId == CAR )
		{
			vListOfCars.push_back(vListOfObjects[p]);
		}
	}	
	
	InitHud();
	bLevel2BeginScene=true;
	FireCar = 0;  JetThrust = CarOnFire = CarFireOnSmoke = 0;
	GOD_MODE_FLAG=false;

 return true;
}

void RenderHud();
void EmptyLists();

/////////////////////////////////////////////////// UPDATE NEXT FRAME
float volume = 0.75f;


void LoadEnd()
{
	iEventNumber =7; 
	iSpawnEnemies = 80;
	bMove = true;
	bLevel2BeginScene = false;
	LevelStartFlag = false;	
	
	for(int i=0; i<vListOfObjects.size(); i++ )
	{
		if( vListOfObjects[i]->x >= SCREENWIDTH )
		{	
			vListOfObjects.erase(vListOfObjects.begin()+i);
		}
	}

	for(int i=0; i<BoxSprite->Objects.size(); i++ )
	{
		if( BoxSprite->Objects[i].GetLeftFace() >= SCREENWIDTH )
		{	
			BoxSprite->Objects.erase(BoxSprite->Objects.begin()+i);
		}
	}

	for(int i=0; i<obj->Objects.size(); i++ )
	{
		if( obj->Objects[i].GetLeftFace() >= SCREENWIDTH )
		{	
			obj->Objects.erase(obj->Objects.begin()+i);
		}
	}

}

void ProduceCarFireEffect(ObjectLevel*Ol )
{
	CarOnFire = new hgeParticleSystem("Particle Effects/fire.psi",     ParSprite);  
	CarFireOnSmoke = new hgeParticleSystem("Particle Effects/firesmoke.psi",ParSprite);  
	CarOnFire->FireAt( Ol->x+40, Ol->y+22 );
	CarFireOnSmoke->FireAt( Ol->x+40, Ol->y+5 );
}

void ManageEffects(float dt)
{
	if(!vListOfObjects.empty() && !FireCar)
	for(unsigned int p = 0; p<vListOfCars.size(); p++ )	
	{
		if( vListOfCars[p]->x < SCREENWIDTH && vListOfCars[p]->x > -40.0f )
		{
			if (!FireCar)
			{   
				ProduceCarFireEffect(vListOfCars[p]);
				FireCar =  vListOfCars[p];
				vListOfCars.erase(vListOfCars.begin()+p);
				break;
			}
		}
	}

	

	if(FireCar)
	{
        CarOnFire->Update(dt); 	CarFireOnSmoke->Update(dt);  

		if( FireCar->x < -50)
		{
			FireCar = 0;
			CarFireOnSmoke->Stop();  
			delete CarFireOnSmoke; 
			CarFireOnSmoke=0;
			CarOnFire->Stop();  
			delete CarOnFire; 
			CarOnFire = 0;
		}
	}	
}

bool StateLevel2::Update(float dt)
{   
	if( bShowNames )
	{
		if( Takeoff.TimerEnd() )
		{	
			names ++; 
			if( Engine->Input_GetKey() == HGEK_ENTER || names > 4) Manager->SetState(STATE_CREDITS);
			if(JetThrustSound) {  JetThrustSound->Stop(); delete JetThrustSound; JetThrustSound = 0 ;  }
		}

		return false;
	}

	if( bLevel2BeginScene )	 
	{
		if (Engine->Input_KeyDown(HGEK_ENTER) ) 
		{  
			bLevel2BeginScene = false; 
			Transmission->PlayTrack(0);
			Music->Play("Sound/music/motivational_3_orch.ogg");			Music->SetVolume(volume);
		}
		return false;	
	}
		

	if (Engine->Input_KeyDown(HGEK_ESCAPE))
	{
		if (!paused)  
		{
			paused = true;
			if(Transmission) Transmission->Pause();
			if(Music) Music->Pause();
			if(GameLevelMusic) GameLevelMusic->Pause();
			if(JetThrustSound) JetThrustSound->Pause();
			Engine->Channel_PauseAll(); 
			KeyMusicPlayer->PlayTrack(5,true);
			KeyMusicPlayer->SetVolume(volume);
			
		}
		else  
		{
			if(Transmission) Transmission->Resume();
			if(Music) Music->Resume();
			if(GameLevelMusic) GameLevelMusic->Resume();
			if(JetThrustSound) JetThrustSound->Resume();
			paused = false;
			KeyMusicPlayer->Stop();
			Engine->Channel_ResumeAll(); 
		}
	}
	if (paused)
	{
		//Updates GUI
		int id = GUI->Update(dt);
		if (id == 1) 
		{ 
			paused = false;	Engine->Channel_ResumeAll();    KeyMusicPlayer->Stop();	 
			if(Transmission) Transmission->Resume();        if(Music) Music->Resume();   
			if(GameLevelMusic) GameLevelMusic->Resume();	if(JetThrustSound) JetThrustSound->Resume();
		}
		else if (id == 2)  
		{
			paused = false;   Engine->Channel_ResumeAll();      Manager->SetState(STATE_LEVEL2); 
		}
		else if (id == 3)  
		{  
			paused = false;   Engine->Channel_ResumeAll();      Manager->SetState(STATE_MENU); 	 
		}
	}
	else 
	{
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
			if( Engine->Input_GetKey() == HGEK_3 && Aztec->pCurrentWeapon->GetWeaponID() != SHOTGUN )  
			{ 
				Aztec->SelectShotGun();        SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
			}else
			if( Engine->Input_GetKey() == HGEK_4 && Aztec->pCurrentWeapon->GetWeaponID() != ROCKETLAUNCHER )  
			{
				Aztec->SelectRocketLauncher(); SoundEffectsList.push_back(PlaySoundEffect(SWITCH_WEAPON));  
			}
		}
		
		if( Music )
		{
			if( iEventNumber == 0 )
			{
				if( !Music->IsPlaying() ) 
				{
					Music->Stop();	
					delete Music;	
					Music = 0;
				}
			}
			else 
				if( iEventNumber >= 11 )
				{
					Music->PlayList();
					if( iEventNumber == 15 && Music->GetTrack() == 0 && Music->GetPlayPosition() > 71000 )
					{
						Music->PlayTrack(1);
						Music->SetPlayPosition(3900);
					}

					if( !Music->IsPlaying() )
					{
					    Music->Stop();	 delete Music;  Music=0;
					}
				}
		}	
		
		if( GameLevelMusic ) 
		{	
			GameLevelMusic->PlayList();
			if(Transmission) GameLevelMusic->SetVolume(0.15f);
			else GameLevelMusic->SetVolume(volume);
		}

		if( Transmission && (iEventNumber == 0 || iEventNumber == 5 || iEventNumber == 8 || iEventNumber == 10 || iEventNumber == 15) )
		{	
			Transmission->PlayList();

			int tk = Transmission->GetTrack();
			if( iEventNumber == 0 )
			bAztecIsSpeaking = ( tk == 1 || tk == 4 )? true:false;
			else if( iEventNumber == 5 )
			bAztecIsSpeaking = ( tk == 2 )? false : true;
			else if( iEventNumber == 8 )
			{
				switch(tk)
				{
				case 0:	case 1:	case 2:	case 5:	case 7:	case 10:  bAztecIsSpeaking=true; break;
				default: bAztecIsSpeaking=false;
				}
			}
			else if( iEventNumber == 10 )
			bAztecIsSpeaking = ( tk == 0 || tk == 4 )? true:false;

			if( Transmission->IsPlaying() == false )
			{
				if( iEventNumber == 0 )	{ bMove = true; LevelStartFlag = false; GameLevelMusic->PlayTrack(0); GameLevelMusic->SetVolume(volume); }
				Transmission->Stop();
				delete Transmission;
				Transmission = 0;
				bAztecIsSpeaking = false;
				if(iEventNumber == 0)			SoundEffectsList.push_back(PlaySoundEffect(STINGER_2));
				else if(iEventNumber == 8) 
				{ 
					fDistanceCovered = 0.0f;  ClearBoxSprite();  GenerateItemsLevel2();
				}
				
			}
			if( iEventNumber != 15 )
			if(Engine->Input_GetKey() == HGEK_PERIOD && Transmission )
			{
				int trk = Transmission->GetTrack();
				if( trk < Transmission->GetTracks()-1 )
				{ Transmission->PlayTrack( trk+1 );  }
				else 
				{ 
					Transmission->Stop(); delete Transmission;
					Transmission = 0;  
					bAztecIsSpeaking = false;
					if( iEventNumber == 0 )	   
					{   
						bMove = true; SoundEffectsList.push_back(PlaySoundEffect(STINGER_2));  LevelStartFlag = false;  
						if(Music) { Music->Stop();	delete Music;	Music = 0; }
						GameLevelMusic->PlayTrack(0); GameLevelMusic->SetVolume(volume);
					} 
					else if( iEventNumber == 8) 
					{ 
						fDistanceCovered = 0.0f;  ClearBoxSprite();  GenerateItemsLevel2();
					}
				}
			}
		}
		else if( (iEventNumber == 2 || iEventNumber == 3 || iEventNumber == 6 || iEventNumber == 7 || 
				  iEventNumber == 12 || iEventNumber == 13 || iEventNumber == 14 || iEventNumber == 4 ) && Transmission ) 
		{
			if( !Transmission->IsPlaying() )
			{
				if( iEventNumber == 14 )	bPlayerGetInFlag = true;

				delete Transmission;  Transmission = 0;
				bAztecIsSpeaking = false;	
			}
		}	


		if(iEventNumber==3)
		{
			if(pDeadEnemyFound)
			{
				if( pDeadEnemyFound->vPosition.x <= -100.0f ) pDeadEnemyFound = 0;
			}
		}

		ProcessLevel2Events();

		if(JetThrust) JetThrust->Update(dt);
		ManageEffects(dt);

		if(bBringVtol) updateVtol(dt);
		
		if(bPlayerEntersVtol == false)
		{
			Aztec->Update(Engine,dt);
			MovePlayerOnEarth2( dt );
			JumpAndCollision( dt,GROUND );
			Move( vInGameBullets, dt,Engine );				  // update bullets
			checkBulletCollision( BoxSprite->Objects);		  // with Box Sprites
			checkBulletCollision( pGameEnemyList );			  // with Box Enemies
			BulletCollisionPro(  );
			for( int i=0; i<vInGameBullets.size(); i++)	 Bullet2BulletCollision( vInGameBullets[i] );
			MaintainGrenades(GrenadeList);
			ManageEnemyLevel2(dt,Aztec);
			checkExistance();
			ProcessBonus();
			UpdateScores(vScores);
			if(!bDisplayBonusMessage)
			ProcessLevelObjects();
		}

		UpdateLeaves(Leaves);
		UpdateBirds(vBirds,dt);

		
		/// FIRE WEAPON
		if( Engine->Input_GetKeyState(HGEK_SPACE) && !Aztec->IsDead() )   
		{   
			bool bWeaponisEmpty = Aztec->pCurrentWeapon->IsEmpty();
			if( Aztec->FireWeapon() )
			{
				if( !bWeaponisEmpty )
				{
					createBullet(Aztec, hTexBullets, Engine, vInGameBullets); 
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

		// update and manage particles in the scene
		for (unsigned  int i=0; i<ParticleList.size(); i++ ) 
		{ ParticleList[i]->Update(dt);  }		   
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



		// process sound effects
		ProcessSound(SoundEffectsList);
		// process soldier dialogs
		for (int z=0; z<EnemyDialogsList.size(); z++)	
			Engine->Effect_PlayEx(EnemyDialogsList[z].hDialog,50);
		while(!EnemyDialogsList.empty())  
			EnemyDialogsList.pop_back();
		

		for(int l=0; l<BoxSprite->Objects.size(); l++ )
		{
			if( BoxSprite->Objects[l].GetRightFace() < -5.0f )
			{
				BoxSprite->Objects[l].Release();
				BoxSprite->Objects.erase( BoxSprite->Objects.begin() + l );
				if( l != 0 && l != BoxSprite->Objects.size()-1 ) l--;
			}
		}
	
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

		if( Aztec->IsDead() && Aztec->IsPlaying() )
		{
			DeathTimer.setstart();
		}
		else 
			if ( Aztec->IsDead() && !Aztec->IsPlaying() && DeathTimer.TimeOver() )  	
			{	
				Manager->SetState(STATE_GAMEOVER);		
			}

	}
	return false;
}
/////////////////////////////////////////////////// RENDER THIS FRAME
bool StateLevel2::Render()
{
	if(bShowNames)	{ ShowNames(); return false; }
	sky2.Render(0,0);
	jungle.Render(0,395);
	RenderBirds(vBirds);
	RenderObjects(vListOfObjects);
	if(FireCar)	{ 	CarFireOnSmoke->Render();	CarOnFire->Render(); 	}
	ground.Render(0,697);
	RenderObjects(pDeadBodies);
	BoxSprite->Render();
	RenderObjects(pGameEnemyList);
	RenderObjects(vInGameBullets);
	if(bPlayerEntersVtol == false) Aztec->Render();
	RenderObjects(GrenadeList);
	obj->Render();
	RenderObjects(vBonus);
	if(bBringVtol && vtol ) vtol->Render();
	RenderLeaves(Leaves);
	if(JetThrust) JetThrust->Render();
	bushes.Render(0,660);
	RenderScores();
	
	for (unsigned int i = 0 ; i < ParticleList.size(); i++ ) if(ParticleList[i])  ParticleList[i]->Render();
	for (unsigned  int i=0; i<LauncherEffectParticleList.size(); i++ ) LauncherEffectParticleList[i]->Render();
	
	if(bAztecIsSpeaking && bPlayerEntersVtol == false)
	{
		float fAx = Aztec->vPosition.x + 60;
		AztecSpeaks->RenderEx( fAx, Aztec->vPosition.y ,0.0f,0.5f,0.5f );
	}

	if( bVtolFlagX && bVtolFlagY && bPlayerGetInFlag )
	{
		CallOutSpr->RenderEx(vtol->GetLeftFace()+520,vtol->GetDownFace()+105,0.0,0.9f); 
		font->printf(vtol->GetLeftFace()+545,vtol->GetDownFace()+110,0,"Jump");
	}

	if(bDisplayBonusMessage)
	{
		float scl = font->GetScale();
		font->SetScale(0.7f);
		font->SetColor(0xff000000);
		CallOutSpr->RenderEx(487,717,0.0f,1.8f,0.7f); 
		font->printf(500,724,0,"Press \"Enter\" To Pick Up The Item");
		font->SetScale(scl);
	}
	////////////Displaying SCORE
	font->SetColor(ARGB(200,255,255,255));
	font->SetScale(1.5f);
	font->printf(10,10,0,"SCORE : %d",Total_Score);
	/////////////////////////////
	if(iEventNumber <= 10)	RenderHud();
	if (paused)	{	PauseMenuSpr->Render(0,0);	GUI->Render();  	}
	if( bLevel2BeginScene )	 
	{
		Level2Spr->SetColor(  ARGB(iAlpha,255,255,255) );
		Level2Spr->RenderEx(0,0,0);	
	}
	return false;
}

/////////////////////////////////////////////////////////////////////
bool StateLevel2::Release()
{
	Engine->Channel_StopAll();
	ReleaseHud();
	EmptyLists();     	
	while( !vListOfCars.empty() ) vListOfCars.pop_back();

	      vtol->Release();     
	 BoxSprite->Release();
		   obj->Release();
		 Aztec->Release(Engine);
	       GUI->Leave();	

	delete vtol;			    vtol=0;
	delete PauseMenuSpr;        PauseMenuSpr=0;
	delete GUI; 				GUI =  0;
	delete cursor;				cursor = 0;
	delete obj;					obj=0;	
	delete BoxSprite ;			BoxSprite = 0;
	delete font;				font = 0;
	delete Aztec;				Aztec = 0; 	
	delete SolarGun;			SolarGun = 0;
	delete CallOutSpr;			CallOutSpr = 0;
	delete GunSparkSprite;		GunSparkSprite=0;
	delete FireHitSprite;		FireHitSprite=0;
	delete ParSprite;			ParSprite=0;
	delete sprGrenade;			sprGrenade=0;  
	delete Health;				Health=0;	  
	delete CurWeapon;			CurWeapon=0;
	delete blastSprite;			blastSprite=0;
	delete GrenadeBlastSprite;  GrenadeBlastSprite=0;
	delete Level2Spr;			Level2Spr=0;
	
	if(KeyMusicPlayer) { KeyMusicPlayer->Stop();	  delete KeyMusicPlayer; KeyMusicPlayer=0;	    }
	  if(Transmission) { Transmission->Stop();        delete Music;				Music=0;			}
	if(GameLevelMusic) { GameLevelMusic->Stop();	  delete Transmission;		Transmission=0;		}
	         if(Music) { Music->Stop();				  delete GameLevelMusic;	GameLevelMusic=0;	}
	if(JetThrustSound) { JetThrustSound->Stop();	  delete JetThrustSound;	JetThrustSound=0;	}
	if(CarOnFire)      { CarOnFire->Stop(true);		  delete CarOnFire;			CarOnFire=0;		}
	if(CarFireOnSmoke) { CarFireOnSmoke->Stop(true);  delete CarFireOnSmoke;	CarFireOnSmoke =0;  }	
	
	// Unloads All The Textures /////////////////////////////////////////////////////////////////////	
	Engine->Texture_Free( objects );			objects=0;
	Engine->Texture_Free( SpriteSheetObj2);		SpriteSheetObj2=0;
	Engine->Texture_Free( healthTex );			healthTex=0;
	Engine->Texture_Free( hTexEnemy );			hTexEnemy=0;	
	Engine->Texture_Free( blast );				blast=0;
	Engine->Texture_Free( hCallOutTex );		hCallOutTex=0;
	Engine->Texture_Free( boxtex );				boxtex=0;
	Engine->Texture_Free( cur );			    cur=0;
	Engine->Texture_Free( rest );				rest=0;
	Engine->Texture_Free( res );				res=0;
	Engine->Texture_Free( ex );					ex=0;
	Engine->Texture_Free(DamageBoxTex);			DamageBoxTex=0;
	Engine->Texture_Free(texBirds);				texBirds=0;
	Engine->Texture_Free(hTexBullets);			hTexBullets=0;
	Engine->Texture_Free(hLeafTex);				hLeafTex=0;
	Engine->Texture_Free(Objects);				Objects=0;
	Engine->Texture_Free(ParTex);				ParTex=0;	
	Engine->Texture_Free(GunSparkTex);			GunSparkTex=0;
	Engine->Texture_Free(FireHitTex);			FireHitTex=0;
	Engine->Texture_Free(hSpeakerTex);			hSpeakerTex=0;
	Engine->Texture_Free(hLevel2tex);			hLevel2tex=0;
	Engine->Texture_Free(hVtolTex);				hVtolTex=0;
	Engine->Texture_Free(L2_SkyTex);			L2_SkyTex=0;
	Engine->Texture_Free(L2_Bushes);			L2_Bushes=0;
	Engine->Texture_Free(L2_GroundTex);			L2_GroundTex=0;
	Engine->Texture_Free(L2_JungleTex);			L2_JungleTex=0;
	Engine->Texture_Free(PauseMenuTex);			PauseMenuTex=0;
	////////////////////////////////////////////////////////////////////////////////////////////////
		
	return true;
}

bool MovePlayerOnEarth2( float dt )
{
	if( Aztec->GetStance() == DUCK && Aztec->GetFrame() == 0 && !Aztec->IsPlaying() )  {	Aztec->ChangeStance(IDLE);	}
	
	const ePLAYER_STANCE STANCE_AZTEC = Aztec->GetStance();
	const ePLAYER_STANCE FACING_AZTEC = Aztec->GetFacing();
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
					 case HUMAN: PlayEffect = NULL_SOUND; break;
					case ALIEN1: PlayEffect = DIE_ALIEN1; break;
					case ALIEN2: PlayEffect = DIE_ALIEN2; break;
					case ALIEN3: PlayEffect = DIE_ALIEN3; break;
					}
					SoundEffectsList.push_back( PlaySoundEffect(PlayEffect) );	

					//BulletCollision=true;
					checkBoxes = false;
					CreateEffect(Aztec,ParticleList,HIT_BLOOD,pGameEnemyList[k]);
					AddScore(hgeVector(pGameEnemyList[k]->vPosition.x + 20, pGameEnemyList[k]->vPosition.y), "+20",ENEMY_MELEES);
					SoundEffectsList.push_back( PlaySoundEffect( (Aztec->pCurrentWeapon->GetWeaponID()== SEMIAUTO)?(MELEE_AZTEC_1):(MELEE_AZTEC_2)) );
					
					pGameEnemyList[k]->Die();
					if(pGameEnemyList[k]->GetId()==HUMAN) GiveWeapon(pGameEnemyList[k]);
					meleeMiss = false;
					break;
				}
			}
		}
		
		if(checkBoxes)
		{
			if( CheckMelee( Aztec, BoxSprite ) )
			{
					meleeMiss = false;
			}
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
////////////////////////////////////////////////////////////////////////////////////////////////

		// with Boxes 
		float Minus = 0.0f;
		for(unsigned int i=0; i < BoxSprite->Objects.size(); i++)
		{ 
			if(  BoxSprite->Objects[i].GetLeftFace() < SCREENWIDTH && BoxSprite->Objects[i].GetRightFace() > 0 ) 
			{
				// horizontal collision for object						
				if( HorizontalCollision = HorizontalCollisionDetection( *Aztec, BoxSprite->Objects[i]) )
				{  
					if( BoxSprite->Objects[i].GetLeftFace() > (Aztec->GetLeftFace()+40) && FACING_AZTEC == FACERIGHT )
					{	RightSideCollision = true;  }
					else if (  BoxSprite->Objects[i].GetLeftFace() < (Aztec->GetLeftFace()+40) && FACING_AZTEC == FACELEFT )
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
///////////////////////////////////////////////////////////////////////////////////////

		///////////////////////  Player Movement Logic //////////////////////////			
		if( ( STANCE_AZTEC == RUNNING || STANCE_AZTEC == LOWMOVE || STANCE_AZTEC == MOVE_BACK))
		{   
			if(Aztec->vPosition.x <= fBoundX && ( ( FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == 1.0f) || (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f ) ) )	
			{	
				if( RightSideCollision != true || (VerticalCollision == true && HorizontalCollision == true ) ) 

					Aztec->Move(dt);
			}
			else
				if( ( (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == -1.0f ) || (FACING_AZTEC == FACERIGHT && Aztec->vDirection.x == -1.0f) ) && Aztec->vPosition.x > -30.0f)  
					if( LeftSideCollision != true || ( VerticalCollision == true && HorizontalCollision == true ) ) 
					{  

						Aztec->Move(dt);
					}

		}
			
		const float SPEEDFAST = 142.421F;
		const float SPEEDSLOW = 61.521F;

		if( ( Aztec->vPosition.x > fBoundX ) && ( (FACING_AZTEC == FACERIGHT&&Aztec->vDirection.x == 1.0f) ||  (FACING_AZTEC == FACELEFT && Aztec->vDirection.x == 1.0f) ) && bMove )
			if( HorizontalCollision != true  || VerticalCollision || STANCE_AZTEC == JUMPING)
				switch (STANCE_AZTEC)
			{
				case JUMPING:	if(!Engine->Input_GetKeyState(HGEK_RIGHT)) break;
				case MOVE_BACK:
				case RUNNING:											
					sky2.scrollX(.01*dt,1);
					jungle.scrollX(.04*dt,1);
					ground.scrollX(.07*dt,1);
					bushes.scrollX(.14*dt,1);
					BoxSprite->Move((SPEEDFAST) *dt,-1);
					fDistanceCovered += 0.3f;
					for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= SPEEDFAST*dt;
					for(unsigned int p = 0; p < pGameEnemyList.size() ; p++ )  pGameEnemyList[p]->vPosition.x -= SPEEDFAST*dt;	 // for enemies alive 
					for(unsigned int p = 0; p < pDeadBodies.size() ; p++ )  pDeadBodies[p]->vPosition.x -= SPEEDFAST*dt;	     // for dead enemies 
					for(unsigned int p = 0; p<GrenadeList.size(); p++ )	GrenadeList[p]->vPosition.x -= SPEEDFAST*dt;
					for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= SPEEDFAST*dt;
					for(unsigned int p = 0; p<vBonus.size(); p++ )	vBonus[p]->vPosition.x -=  SPEEDFAST*dt;	
					for(unsigned int p = 0; p<obj->Objects.size(); p++ )	obj->Objects[p].fWorldX -= SPEEDFAST*dt;
					for(unsigned int p = 0; p<vListOfObjects.size(); p++ )	vListOfObjects[p]->x -=  SPEEDFAST*dt;
					for(unsigned int p = 0; p<vScores.size(); p++ )	vScores[p].position.x -=  153.421f*dt;
					for(unsigned int p = 0; p<ParticleList.size(); p++ )
					{ 
						float x,y;
						ParticleList[p]->GetTransposition(&x,&y);
						x-= SPEEDFAST*dt; 
						ParticleList[p]->Transpose( x,y );
					}
					
					if( FireCar )
					{ 
						float x=0.0f,y=0.0f;
						CarOnFire->GetTransposition(&x,&y);
						x-=SPEEDFAST*dt; 
						CarOnFire->Transpose(x,y);
						CarFireOnSmoke->GetTransposition(&x,&y);
						x-=SPEEDFAST*dt;
						CarFireOnSmoke->Transpose(x,y);
					}

					break;		

				case LOWMOVE:	
					sky2.scrollX(.01*dt,1);
					jungle.scrollX(.02*dt,1);
					ground.scrollX(.035*dt,1);
					bushes.scrollX(.07*dt,1);
					
					BoxSprite->Move(SPEEDSLOW*dt,-1);
					fDistanceCovered += 0.3f;
					
					for(unsigned int p = 0; p < vInGameBullets.size() ; p++ )  vInGameBullets[p]->vPosition.x -= SPEEDSLOW*dt;
					for(unsigned int p = 0; p < pGameEnemyList.size() ; p++ ) pGameEnemyList[p]->vPosition.x -= SPEEDSLOW*dt;  // for enemies alive 
					for(unsigned int i = 0; i < pDeadBodies.size();     i++ ) pDeadBodies[i]->vPosition.x -= SPEEDSLOW*dt;  // for dead enemies
					for(unsigned int p = 0; p < GrenadeList.size();     p++ ) GrenadeList[p]->vPosition.x -= SPEEDSLOW*dt;
					for(unsigned int p = 0; p<Leaves.size(); p++ )	Leaves[p].pos.x -= SPEEDSLOW*dt;
					for(unsigned int p = 0; p<vBonus.size(); p++ )	vBonus[p]->vPosition.x -=  SPEEDSLOW*dt;	
					for(unsigned int p = 0; p<obj->Objects.size(); p++ )	obj->Objects[p].fWorldX -= SPEEDSLOW*dt;	
					for(unsigned int p = 0; p<vListOfObjects.size(); p++ )	vListOfObjects[p]->x -=  SPEEDSLOW*dt;	
					for(unsigned int p = 0; p<vScores.size(); p++ )	vScores[p].position.x -=  153.421f*dt;
					for(unsigned int p = 0; p<ParticleList.size(); p++ )
					{ 
						float x,y;
						ParticleList[p]->GetTransposition(&x,&y);
						x-= SPEEDSLOW*dt;
						ParticleList[p]->Transpose( x,y );
					}

					if( FireCar )
					{ 
						float x=0.0f,y=0.0f;
						CarOnFire->GetTransposition(&x,&y);
						x-=SPEEDSLOW*dt; 
						CarOnFire->Transpose(x,y);
						CarFireOnSmoke->GetTransposition(&x,&y);
						x-=SPEEDSLOW*dt;
						CarFireOnSmoke->Transpose(x,y);
					}

					
					break;
			}
			return false;
}

Enemy* CreateEnemy(int opt);
void spawnBS();
void bringEnemyLevel2();
void ControlEnemy(Protagonist* &Aztec, Enemy* &, float dt) ;
void ManageEnemyLevel2(float dt, Protagonist *Aztec)
{
	if(Spawn.TimerEnd())
	bringEnemyLevel2();	
	
	for( int i=0; i<pGameEnemyList.size(); i++ )
	{ 
		if( bEnding == false && pGameEnemyList[i]->vPosition.x > 1390.0f ) return;
		else if( bEnding && (pGameEnemyList[i]->vPosition.x > 1300.0f || pGameEnemyList[i]->vPosition.x < 60.0f) ) 
		{
			if( pGameEnemyList[i]->GetStance() == IDLE )
			pGameEnemyList[i]->ChangeStance(RUNNING);
		}
		ControlEnemy( Aztec,pGameEnemyList[i], dt );  
	}
}

void bringEnemyLevel2()
{
	// limit no. of enemies per frame
	if( pGameEnemyList.size() > ( 4 + (rand()%2) ) ) return; 

	int num	= -1;

	if( iSpawnEnemies < 12 && iEventNumber <= 2 && bEventOccur == false )	
	{
		num = 0;
	}
	else if( iSpawnEnemies < 30 && iEventNumber <= 4 && fDistanceCovered > 650.0f && bAztecIsSpeaking == false && Transmission == 0 )
	{
		num = rand() % 2; // 0 or 1
	}
	else if( iSpawnEnemies >= 30 && iSpawnEnemies < 45 )
	{
		num = rand() % 3; //0,1,2
	}
	else if( iEventNumber >= 5 && iEventNumber < 8 && iSpawnEnemies >= 45 && iSpawnEnemies < 75 && Transmission == 0 )
	{
		num =  ( rand() % 2 ) ? (rand()%4) : ((rand()%3)+1) ;  
								//0,1,2,3	   //1,2,3			
	}
	else if( iEventNumber == 9 && EnemyCounterEnding <=40 )
	{
		if( HoldOn.TimeOver() )
		spawnBS();				
	}

	if( num >= 0 )
	{
		Enemy* enemy = CreateEnemy(num);
		enemy->vPosition.x += 100 + (rand()%50);

		if(enemy)
		{
		enemy->Init(Engine,hTexEnemy,hSpeakerTex);
		pGameEnemyList.push_back(enemy);
		++iSpawnEnemies;
		}
	}
}


void ProcessLevel2Events()
{
	if( fDistanceCovered > 300.0f && fDistanceCovered < 303.0f && !bEventOccur && iEventNumber == 0 )
	{
		bEventOccur = true;
		iEventNumber = 1;
		Enemy* enmy = new Enemy(ALIEN1,FACELEFT,DEAD,hgeVector(1370.0f,565.0f),hgeVector(0,0));
		enmy->Init(Engine,hTexEnemy,hSpeakerTex);
		enmy->Die();
		enmy->anim->SetFrame(3);
		enmy->anim->Stop();
		pDeadEnemyFound = enmy;
		pDeadBodies.push_back(enmy);
	}
	else
	if( iEventNumber == 1 && pDeadEnemyFound )
	{
		if( Aztec->GetRightFace() > pDeadEnemyFound->GetLeftFace() && Aztec->GetLeftFace() < pDeadEnemyFound->GetRightFace() )
		{
			iEventNumber = 2;
			pDeadEnemyFound = 0;
			bEventOccur = false;					
			SoundEffectsList.push_back(PlaySoundEffect(STINGER_1));
			//SoundEffectsList.push_back(PlaySoundEffect(WHAT_THE_HELL_SLOW));
			Transmission = new MusicPlayer(sound_engine);
			Transmission->Play("Sound/Dialogs/Protagonist/what the hell slow.mp2");
			bAztecIsSpeaking = true;
			Enemy* enmy = new Enemy(ALIEN1,FACELEFT,IDLE,hgeVector(1600.0f,565.0f),hgeVector(-1.0f,0));
			enmy->Init(Engine,hTexEnemy,hSpeakerTex);
			pGameEnemyList.push_back(enmy);
			pDeadEnemyFound = enmy;
		}
	}
	else if( iEventNumber == 2 && pDeadEnemyFound)
	{
		if( pDeadEnemyFound->vPosition.x < 1330.0f )	
		{
			iEventNumber = 3;
			Transmission = new MusicPlayer(sound_engine);
			Transmission->Play("Sound/Dialogs/Protagonist/oh shit.mp2");
			bAztecIsSpeaking = true;
		}
	}	
	else if( iEventNumber == 3 && (!pDeadEnemyFound || pDeadEnemyFound->IsDead()) )
	{
		if(pDeadEnemyFound) pDeadEnemyFound = 0;

		iEventNumber = 4;   
		LoadTransmission(2,Transmission);
		Transmission->PlayTrack(0);
		bAztecIsSpeaking = true;
	}
	else if( iEventNumber == 4 && iSpawnEnemies >= 45 && pGameEnemyList.size() == 0 )
	{
		SoundEffectsList.push_back( PlaySoundEffect(STINGER_2) );
		iEventNumber = 5;
		LoadTransmission(3,Transmission);
		Transmission->PlayTrack(0);
		bAztecIsSpeaking = true;
	}
	else if( iEventNumber == 5 && iSpawnEnemies == 52  )
	{
		iEventNumber = 6;
		Transmission = new MusicPlayer(sound_engine);
		Transmission->Play("Sound/Dialogs/Level 2/nomad_trans_2.mp3");
		bAztecIsSpeaking = true;
	}
	else if( iEventNumber == 6 && iSpawnEnemies >= 63 )
	{
		iEventNumber = 7;
		Transmission = new MusicPlayer(sound_engine);
		Transmission->Play("Sound/Dialogs/Level 2/nomad_trans_3.mp3");
		bAztecIsSpeaking = true;
	}
	else if( iEventNumber == 7 && iSpawnEnemies >= 75 && pGameEnemyList.size() == 0 )
	{
		iEventNumber = 8;
		
		LoadTransmission(4,Transmission);
		Transmission->PlayTrack(0);
		bAztecIsSpeaking = true;
		if(GameLevelMusic)
		GameLevelMusic->Stop();
		bGameIsInTheFinalStage = true;
	}
	else if( iEventNumber == 8 && fDistanceCovered > 180 && !Transmission )
	{
		Music = new MusicPlayer(sound_engine);
		Music->Play("Sound/music/pyrrhic_victory_orch.ogg");
		Music->SetVolume(0.58f);
		HoldOn.setEndTime(7500); 
		HoldOn.setstart(); 
		iEventNumber = 9;
		bEnding = true;
		bMove = false;
		fBoundX = 1320.0f;
		bGameIsInTheFinalStage = true;
	}
	else if( iEventNumber == 9 && EnemyCounterEnding > 40 && pGameEnemyList.size() == 0 )
	{
		iEventNumber = 10;
		LoadTransmission(5,Transmission);
		Transmission->PlayTrack(0);
		bAztecIsSpeaking = true;
		if(Music){ Music->Stop(); delete Music; Music = 0; }
		static char* EndMusic[] = { "Sound/music/ending_1.ogg",	"Sound/music/ending_2.ogg", };
		Music = new MusicPlayer(sound_engine,EndMusic,2);		Music->PlayTrack(0);

	}
	else if( iEventNumber == 10 && !Transmission )
	{
		bBringVtol = true; 
		iEventNumber = 11;
		vtol->vPosition.x -= 1500.0f;	
		vtol->vPosition.y -= 1500.0f;
	}
	else if( iEventNumber == 11 && !Transmission && vtol->vPosition.y > -1200 )
	{ iEventNumber = 12;	Transmission = new MusicPlayer(sound_engine);	Transmission->Play("Sound/Dialogs/Level 2/6_trans_1.mp2"); }
	else if( iEventNumber == 12 && !Transmission && vtol->vPosition.y > -400  )
	{ iEventNumber = 13;	Transmission = new MusicPlayer(sound_engine);	Transmission->Play("Sound/Dialogs/Level 2/6_trans_2.mp2"); }
	else if( iEventNumber == 13 && !Transmission && bVtolFlagX && bVtolFlagY )
	{  iEventNumber = 14;	Transmission = new MusicPlayer(sound_engine);	Transmission->Play("Sound/Dialogs/Level 2/6_trans_3.mp2");  }
	else if( iEventNumber == 14 && !Transmission && bPlayerEntersVtol )
	{ 	
		iEventNumber = 15;	LoadTransmission(6,Transmission);	Transmission->PlayTrack(0);	 bGameIsInTheFinalStage = false;		 
	}
	else if( iEventNumber == 15 && !Transmission && vtol->vPosition.y < -400.0f )
	{ 
		bShowNames = true; iEventNumber = 16; Takeoff.setEndTime(2000); Takeoff.setstart(); bGameIsInTheFinalStage = false;	
	}
}


char* conversation_1[] =
{
"Sound/Dialogs/Level 2/trans_1.mp2", 
"Sound/Dialogs/Level 2/trans_2.mp2",
"Sound/Dialogs/Level 2/trans_3.mp2",
"Sound/Dialogs/Level 2/trans_4.mp2",
"Sound/Dialogs/Level 2/trans_5.mp2",
"Sound/Dialogs/Level 2/trans_6.mp2",
};

char* conversation_2[] =
{	
	"Sound/Dialogs/Level 2/nomad_trans_1.mp3",
};


char* conversation_3[] =
{	
	"Sound/Dialogs/Level 2/2_trans_0.mp2",
	"Sound/music/stop.ogg",
	"Sound/Dialogs/Level 2/2_trans_1.mp2",
	"Sound/Dialogs/Level 2/2_trans_2.mp2",
	"Sound/music/stop.ogg",
	"Sound/Dialogs/Level 2/2_trans_3.mp2",
	"Sound/music/stop.ogg",
	"Sound/Dialogs/Protagonist/damn it very angry.mp2",
	"Sound/Dialogs/Level 2/2_trans_4.mp2",
};

char* conversation_4[] =
{	
	"Sound/Dialogs/Level 2/3_trans_1.mp3",                // 0 nomad
	"Sound/Dialogs/Protagonist/what the hell slow.mp2",   // 1 nomad
	"Sound/Dialogs/Level 2/3_trans_2.mp2",				  // 2 nomad		
	"Sound/music/stop.ogg",								  // 3 stop	
	"Sound/Dialogs/Level 2/3_trans_3.mp2",                // 4 pilot
	"Sound/Dialogs/Level 2/3_trans_4.mp2",				  // 5 nomad 	
	"Sound/Dialogs/Level 2/3_trans_5.mp2",				  // 6 strickland
	"Sound/Dialogs/Level 2/3_trans_6.mp2",				  // 7 nomad
	"Sound/Dialogs/Level 2/3_trans_7.mp2",				  // 8 pilot
	"Sound/Dialogs/Level 2/3_trans_8.mp2",				  // 9 strickland		
	"Sound/Dialogs/Level 2/3_trans_9.mp2",				  // 10 nomad
	"Sound/Dialogs/Level 2/3_trans_10.mp2",				  // 11 strickland	
};

char* conversation_5[] =
{	
	"Sound/Dialogs/Level 2/4_trans_1.mp2",                // nomad
	"Sound/Dialogs/Level 2/4_trans_2.mp2",
	"Sound/music/stop.ogg",
	"Sound/Dialogs/Level 2/4_trans_3.mp2",
	"Sound/Dialogs/Level 2/4_trans_4.mp2",				  // nomad
};

char* conversation_6[] =
{	
	"Sound/Dialogs/Level 2/6_trans_4.mp2",		 // 0
	"Sound/music/stop.ogg",						 // 1
	"Sound/Dialogs/Level 2/6_trans_5.mp2",		 // 2
	"Sound/music/stop.ogg",						 // 3
	"Sound/Dialogs/Level 2/6_trans_6.mp2",		 // 4 
	"Sound/Dialogs/Level 2/6_trans_7.mp2",       // 5 nomad
	"Sound/items/null.wav",										    // 46
	"Sound/Dialogs/Level 2/6_trans_8.mp2",       // 6 nomad
};


// changed conversation 2


void LoadTransmission(int i,MusicPlayer*&ptr)
{
	switch(i)
	{
	case 1: ptr = new MusicPlayer(sound_engine,conversation_1,6); break;
	case 2: ptr = new MusicPlayer(sound_engine,conversation_2,1); break;
	case 3: ptr = new MusicPlayer(sound_engine,conversation_3,9); break;
	case 4: ptr = new MusicPlayer(sound_engine,conversation_4,12); break;
	case 5: ptr = new MusicPlayer(sound_engine,conversation_5,5); break;
	case 6: ptr = new MusicPlayer(sound_engine,conversation_6,8); break;
	}
}

void ProcessLevelObjects()	
{		
	float AzLeft ;
	float AzRight ;

	if(Aztec->GetFacing() == FACERIGHT)
	{
		AzRight = Aztec->GetRightFace() - 43.0f;
		AzLeft = Aztec->GetLeftFace() + 34.0f;
	}
	else 
	{
		AzLeft = Aztec->GetLeftFace() + 43.0f;
		AzRight = Aztec->GetRightFace() - 34.0f;
	}

	for( int i=0; i< obj->Objects.size(); i++ )
	{
       float obLeftFace = obj->Objects[i].GetLeftFace();
	   float obRightFace = obj->Objects[i].GetRightFace();
	   int id = 0;
	   
	   switch(obj->Objects[i].GetId())
	   {
	   case 4: id = 4;     obLeftFace += 7.0f ; obRightFace -= 30.0f; 			  break; // launcher 
	   case 5: id = 5;     obLeftFace += 11.0f ; obRightFace -= 36.0f;		      break; // shotgun  	
	   case 6: id = 6;     obLeftFace += 33.0f ; obRightFace -= 62.0f;		      break; // pistol	
	   case 7: id = 7;     obLeftFace += 15.0f ; obRightFace -= 46.0f;		      break; // assault rifle 	 
	   case 8: id = 8;     obLeftFace += 22.0f ; obRightFace -= 62.0f;			  break; // medi-kit 
	   case 9: id = 9; 	   obLeftFace += 31.0f ; obRightFace -= 72.0f;			  break; // grenade
	   }   		


       if( !obj->Objects[i].IsDead() &&  obLeftFace < 600.0f && id != 0 )
	   {
		    if( obLeftFace < AzRight && obRightFace > AzLeft )
			{
				bDisplayBonusMessage = true; 
				if(Engine->Input_GetKey() == HGEK_ENTER)
				{
					switch(obj->Objects[i].GetId())
					{
					case 4:  if( !Aztec->RocketLauncher.IsFull() )
							 {
								 Aztec->RocketLauncher.RaiseAmmo(40); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); 
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break; // launcher 
					case 5:  if( !Aztec->ShotGun.IsFull() )
							 { 
								 Aztec->ShotGun.RaiseAmmo(40);  SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); 
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break; // shotgun  	
					case 6:  if( !Aztec->SideArm.IsFull() )
							 { 
								 Aztec->SideArm.RaiseAmmo(20); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO));
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break; // pistol	
					case 7:  if( !Aztec->AssaultRifle.IsFull() )
		                     {
								 Aztec->AssaultRifle.RaiseAmmo(40); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO));
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break;  // assault rifle 	 
					case 8:  if( Aztec->GetHealth() < 100 )   // medi-kit 
							 {  
								 Aztec->RaiseHealth(30); SoundEffectsList.push_back(PlaySoundEffect(PICK_HEALTH));
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break;  
					case 9:  if( Aztec->GetGrenade() < 6)
							 { 
								 Aztec->RaiseGrenade(1); SoundEffectsList.push_back(PlaySoundEffect(PICK_AMMO)); 
								 obj->Objects.erase(obj->Objects.begin()+i);      bDisplayBonusMessage = false;				
							 }break; // grenade
					}   			
				}
				
				break;
			} else bDisplayBonusMessage = false;
	   }
	}	



}


void GenerateItemsLevel2()
{
	void AlterLevelAtTheEnding();	AlterLevelAtTheEnding();
	float x1 = SCREENWIDTH+250;
	const int SIZE=14; 
	Bonus* arrBon[SIZE] = 
	{
		new Bonus(MEDIKIT,hgeVector (x1,GROUND-17.0f) ),
		new Bonus(MEDIKIT,hgeVector (x1+50,GROUND-17.0f) ),

		new Bonus(AMMO_GRENADE,hgeVector (x1+90,GROUND-10.0f) ),
		new Bonus(AMMO_GRENADE,hgeVector (x1+110,GROUND-10.0f) ),
		new Bonus(AMMO_GRENADE,hgeVector (x1+130,GROUND-10.0f) ),
	
		new Bonus(AMMO_LAUNCHER,hgeVector (x1+150,GROUND-17.0f) ),
		new Bonus(AMMO_LAUNCHER,hgeVector (x1+240,GROUND-17.0f) ),

		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1+340,GROUND-17.0f) ),
		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1+420,GROUND-17.0f) ),
		new Bonus(AMMO_ASSAULTRIFLE,hgeVector (x1+500,GROUND-17.0f) ),

		new Bonus(AMMO_SHOTGUN,hgeVector (x1+570,GROUND-17.0f) ),
		new Bonus(AMMO_SHOTGUN,hgeVector (x1+650,GROUND-17.0f) ),

		new Bonus(MEDIKIT,hgeVector (x1+730,GROUND-17.0f) ),
		new Bonus(MEDIKIT,hgeVector (x1+780,GROUND-17.0f) ),
	};

	for(int i=0; i<SIZE; i++)
		arrBon[i]->Init(hTexBullets);

	for(int l=0; l<SIZE; l++)
		vBonus.push_back(arrBon[l]);

}


void ClearBoxSprite()
{
	for( int l=0; l<BoxSprite->Objects.size(); l++ )
	{
		if( BoxSprite->Objects[l].GetLeftFace() >= 1366.0f )
		{
			BoxSprite->Objects[l].Release();
			BoxSprite->Objects.erase( BoxSprite->Objects.begin()+l );
			if( l != 0 && l != BoxSprite->Objects.size()-1 ) l--;
		}
	}
}

void Bullet2BulletCollision( Bullet* bPtr )
{
    if( bPtr->GetId() != SHOTGUN_BULLET ) return; 

	float MyDownFace = bPtr->vPosition.y + 7 ;
	float MyUpFace = bPtr->vPosition.y;

	for( int i=0; i < vInGameBullets.size(); i++ )
	{
	  Bullet* bPtrEnm = vInGameBullets[i];
	  eBULLETID bId = bPtrEnm->GetId();
	  if( bPtrEnm != bPtr )
	  if( bId == ENEMYBULLET_TYPE4 || bId == ENEMYBULLET_TYPE2 || bId == ENEMYBULLET_TYPE3 )
	  {
		  float ThemDownFace = bPtrEnm->vPosition.y + 7 ;
		  float ThemUpFace = bPtrEnm->vPosition.y;

		  if( MyDownFace > ThemUpFace && ThemDownFace > MyUpFace )	  
		  if( bPtr->GetRightFace() > bPtrEnm->GetLeftFace() && bPtr->GetLeftFace() < bPtrEnm->GetRightFace() )
		  {
			  bPtrEnm->Die();
			  bPtr->Die();	
			  CreateEffect( bPtr, ParticleList );
			  CreateEffect( bPtrEnm, ParticleList );
		  }  
	  }
	}
}


void updateVtol(float dt)
{
	float right, left, head = Aztec->GetUpFace()+36.0f;; 
	const float _SPEED_X = 70.0F, _SPEED_Y = 70.0F;
	if(!vtol) return;
	
	if( bPlayerEntersVtol==false )
	{

		if( !JetThrustSound && vtol->vPosition.y > -700 )
		{
			JetThrustSound = new MusicPlayer(sound_engine);
			JetThrustSound->Play("sound/items/plane.mp3");
			JetThrustSound->SetVolume(0.001f);
		}
		else 
			if( JetThrustSound )
			{
				if(JetThrustSound->GetVolume() < 0.8f)
					JetThrustSound->SetVolume( JetThrustSound->GetVolume()+0.001f );
			}
			else if(JetThrustSound && bVtolFlagY)
			{
				JetThrustSound->SetVolume(1.0f);
			}
		

			if( !JetThrust && vtol->vPosition.y > -30 ) 
			{ 
				JetThrust = new hgeParticleSystem("Particle Effects/jetplane.psi", ParSprite);   
				JetThrust->FireAt(950.0f,GROUND); JetThrust->info.nEmission = 0;
			}
			else if( JetThrust && !bVtolFlagY )
			{
				if(JetThrust->info.nEmission<600)
				   JetThrust->info.nEmission += 2;
			}
			else if( JetThrust && bVtolFlagY )
			{
			       JetThrust->info.nEmission = 800;
			}

		if( vtol->sprVtol->GetWidth()+vtol->vPosition.x < 1000 )	
		{ vtol->vPosition.x += _SPEED_X*dt; }
		else bVtolFlagX = true;
		if( vtol->sprVtol->GetHeight()+vtol->vPosition.y < 600.0f )	 { vtol->vPosition.y += _SPEED_Y*dt; }
		else { bVtolFlagY = true; }
	    
		if(Aztec->GetFacing() == FACERIGHT)
		{
			right = Aztec->GetRightFace() - 43.0f;
			left = Aztec->GetLeftFace() + 34.0f;
		}
		else 
		{
			left = Aztec->GetLeftFace() + 43.0f;
			right = Aztec->GetRightFace() - 34.0f;
		}
		
		if( bPlayerGetInFlag )
		if( head > vtol->GetUpFace() && Aztec->GetDownFace() < vtol->GetDownFace()+10 )
		{
			if( right > vtol->GetLeftFace()+520.0f && left < vtol->GetLeftFace()+660.0f )
			{
				if( bVtolFlagX && bVtolFlagY )
				{  
					bPlayerEntersVtol = true; Takeoff.setstart(); bVtolFlagX = bVtolFlagY = false; 
				}
			}
		}
	}
	else if( Takeoff.TimeOver() )
	{
		 vtol->vPosition.x += _SPEED_X * dt * 0.2f;
		 vtol->vPosition.y -= _SPEED_Y * dt * 0.5f;


		if( JetThrust && JetThrust->info.nEmission > 0 /*&& vtol->vPosition.y*/  )
		{
			JetThrust->info.nEmission -= 2;
		}
		else if( JetThrust && JetThrust->info.nEmission <= 0 )
		{
			JetThrust->Stop(); delete JetThrust; JetThrust = 0; 
		}
		
		if( JetThrustSound && JetThrustSound->GetVolume() > 0 && vtol->vPosition.y < 400.0f )
		{
			JetThrustSound->SetVolume( JetThrustSound->GetVolume()-0.0001f );
		}
		else
		if(  JetThrustSound && JetThrustSound->GetVolume() <= 0 )
		{
			JetThrustSound->Stop(); delete JetThrustSound; JetThrustSound=0;
		}

	}
		
}

void ShowNames()
{
	switch(names)
	{
	 case 0:	sprNames->SetTextureRect(0.0f,350.0f,670.0f,130.0f); break;
	 case 1:	sprNames->SetTextureRect(0.0f,650.0f,160.0f, 50.0f); break;
	 case 2:	sprNames->SetTextureRect(0.0f,500.0f,300.0f, 50.0f); break;
	 case 3:	sprNames->SetTextureRect(0.0f,550.0f,300.0f, 50.0f); break;
	 default:	sprNames->SetTextureRect(0.0f,600.0f,300.0f, 50.0f); break;
	}
		sprNames->SetHotSpot( sprNames->GetWidth()/2,  sprNames->GetHeight()/2 );
		sprNames->Render( SCREENWIDTH/2,SCREENHEIGHT/2 );
}
void RenderHud()
{
	float plus=0.0f;
	switch(Aztec->GetWeaponId())
	{
	case ASSAULTRIFLE: HudWeapon->SetTextureRect(0,0,59,24); break;
	case SEMIAUTO: HudWeapon->SetTextureRect(62,0,24,21); plus=20.0f; break;
	case SHOTGUN: HudWeapon->SetTextureRect(91,0,73,23); break;
	case ROCKETLAUNCHER: HudWeapon->SetTextureRect(166,0,84,26);
	}

	HUDspr->Render(HudRenderPointX,HudRenderPointY); 
	HUDsprAmmo->SetFlip(true,false);
	HUDsprAmmo->Render(HudRenderPointX2,HudRenderPointY2); 

	for( int i=0; i<=Aztec->GetHealth()*2; i+=2 ) 
		Engine->Gfx_RenderLine( HudRenderPointX+80+i, HudRenderPointY+4, HudRenderPointX+80+i, HudRenderPointY+44, 0xffff0000);
	for (int i = 0, x= 1160; i < Aztec->GetGrenade(); i ++)	
	{ sprGrenade->Render(x,748); x += 20; }

	HudWeapon->Render(HudRenderPointX2+50.0f+plus,HudRenderPointY2+2.0f);
	fontHud->printf(HudRenderPointX2+160+35, HudRenderPointY2, HGETEXT_CENTER|HGETEXT_TOP, "%i", Aztec->pCurrentWeapon->GetAmmo());
}


void InitHud()
{
	HUDtex = Engine->Texture_Load("Sprites/HUD4.png"); 
	HUDtexAmmo = Engine->Texture_Load("Sprites/HUD6.png"); 
	fontHud = new hgeFont("Fonts/font.fnt");	//Init Font
	HUDspr = new hgeSprite( HUDtex,0,0,401,48 );
	HUDsprAmmo = new hgeSprite( HUDtexAmmo,0,0,240,49 );
	HudWeapon = new hgeSprite( hTexBullets,0,0,512,256 );
	HUDspr->SetColor(0xFFFFFFFF); HUDsprAmmo->SetColor(0xFFFFFFFF);	
	fontHud->SetColor(0xffffffff); fontHud->SetScale(1.8f);
}

void ReleaseHud()
{
	Engine->Texture_Free( HUDtex );
	Engine->Texture_Free( HUDtexAmmo );
	delete fontHud;				fontHud = 0;
	delete HUDspr;				HUDspr=0;
	delete HUDsprAmmo;			HUDsprAmmo=0;
	delete HudWeapon;			HudWeapon=0;
}




IDFIRST finalGround[13]=
{
	H_SPACE_100_PIX,H_SPACE_100_PIX,H_SPACE_100_PIX,H_SPACE_100_PIX, H_SPACE_1000_PIX, TREE, TREE, TREE, TREE, TREE, TREE, TREE, TREE,
};


void AlterLevelAtTheEnding()
{
	for(int i=0; i<BoxSprite->Objects.size(); i++ )
	{
		if( BoxSprite->Objects[i].GetRightFace() <= 0 || BoxSprite->Objects[i].GetLeftFace() >= SCREENWIDTH )
		{
			BoxSprite->Objects[i].Release();
			BoxSprite->Objects.erase(BoxSprite->Objects.begin()+i);
			if( i != 0 && i != BoxSprite->Objects.size()-1 ) --i;
		}
	}
	
	for(int i=0; i<vListOfObjects.size(); i++ )
	{
	   if( vListOfObjects[i]->x > SCREENWIDTH ||  vListOfObjects[i]->GetRightFace() < 0 )
	   {
		   delete vListOfObjects[i]; 
		   vListOfObjects.erase(vListOfObjects.begin() + i);
	   }
	}

	LoadObjects(vListOfObjects,finalGround,13,GROUND+3,SpriteSheetObj2);	
}

