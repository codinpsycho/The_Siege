#include "Weapon.h"

Weapon::Weapon(eWEAPONS id,eWEAPONTYPE ewClass)	
{
	this->eID = id;
	switch(eID)
	{
	case ASSAULTRIFLE:    iAmmo = ASSAULTRIFLE_LIMIT;      MaxBullets = ASSAULTRIFLE_LIMIT;
		RateOfFire =170;
		break;
	case SEMIAUTO:        iAmmo = SEMIAUTO_LIMIT;		   MaxBullets = SEMIAUTO_LIMIT;
		RateOfFire =350;
		break;
	case SHOTGUN:         iAmmo = SHOTGUN_LIMIT;		   MaxBullets = SHOTGUN_LIMIT;
		RateOfFire =430;
		break;
	case ROCKETLAUNCHER:  iAmmo = ROCKETLAUNCHER_LIMIT;    MaxBullets = ROCKETLAUNCHER_LIMIT;
		RateOfFire =1200;
		break;
	}
	
	bFireFlag = true;
	FireBullet.setstart();
	FireBullet.setEndTime(RateOfFire);
}

void Weapon::ResetFireRates()
{
	switch(eID)
	{
	case ASSAULTRIFLE: 	  RateOfFire = 200;     break;
	case SEMIAUTO:        RateOfFire = 400;		break;
	case SHOTGUN:         RateOfFire = 600; 	break;
	case ROCKETLAUNCHER:  RateOfFire = 1500;	break;
	}
	FireBullet.setEndTime(RateOfFire);
	FireBullet.setstart();
}

int Weapon::RaiseAmmo(int am)
{
	int diff = 0;
	this->iAmmo += am;

	if( this->iAmmo  >	this->MaxBullets ) 
	{
		diff = iAmmo - MaxBullets;
		this->iAmmo = this->MaxBullets;
	}

	return diff;	 // return the bullets un used
}


bool Weapon::Fire() 
{ 
	//if(!FireBullet.TimerEnd()) return false;
	if( FireBullet.TimerEnd() ) { bFireFlag = true; }

	if( bFireFlag )
	{	
		bFireFlag = false;
		FireBullet.setstart();
		if ( iAmmo > 0 ) --iAmmo; 
		return true;
	}

	return false;
}

void Weapon::SetWeaponID(eWEAPONS id)			
{ 
	eID = id;		
	*this = Weapon(id,eWEAPONCLASS);
}

/////////////////////////////////////////////////////////////////////
WeaponObject::WeaponObject(eWEAPONS id,eWEAPONTYPE wClass,float speed, hgeVector& pos, hgeVector& dir): Weapon(id,wClass)
{	
	bDead = false;
	fSpeedX = speed;
	vPosition = pos;
	vDirection = dir;
	sprite = 0;
	height = 0.0f;
	width = 0.0f;
	hTexture = 0;
}

WeaponObject::WeaponObject( const WeaponObject& wep):Weapon(wep)
{
	fSpeedX = wep.fSpeedX;
	vPosition = wep.vPosition;
	vDirection = wep.vDirection;
	this->sprite = 0;
	bDead = wep.bDead;
	height = wep.height;
	width = wep.width;
	hTexture = wep.hTexture;
}

WeaponObject& WeaponObject:: operator = (const WeaponObject& wep)
{
	if( &wep != this )
	{
		this->Release();
		fSpeedX = wep.fSpeedX;
		vPosition = wep.vPosition;
		vDirection = wep.vDirection;
		this->sprite = 0;
		bDead = wep.bDead;
		height = wep.height;
		width = wep.width;
		hTexture = wep.hTexture;
	}
	return *this;
}

WeaponObject::~WeaponObject()
{

}

void WeaponObject::Init(HGE* Engine,HTEXTURE hTex)     // initialization occurs here
{
	switch(eID)
	{
	case ASSAULTRIFLE: 
		sprite = new hgeSprite(hTex,0,0,59,24); 
		break;
	case SEMIAUTO:
		sprite = new hgeSprite(hTex,62,0,24,21); 
		break;
	case SHOTGUN:
		sprite = new hgeSprite(hTex,91,0,73,23);  	
		break;
	case ROCKETLAUNCHER:
		sprite = new hgeSprite(hTex,166,0,84,26); 	
		break;
	}

	hTexture = hTex;
	height = sprite->GetHeight();
	width = sprite->GetWidth(); 
}

void WeaponObject::Render()
{	
	sprite->Render(vPosition.x,vPosition.y);
}

void WeaponObject::Move(float dt)
{
	vPosition.x += fSpeedX*dt * vDirection.x;
	vPosition.y += fSpeedX*dt * vDirection.y;
}

void WeaponObject::Release()
{
	delete this->sprite;
}


WeaponObject& WeaponObject::operator = (const Weapon& wep)
{
	(Weapon&) *this  = wep;  		
	return *this;
}

void WeaponObject::ReInit(HGE* Engine)
{
	this->Release();
	Init(Engine,hTexture);
}

void WeaponObject::SwapWeapon(Weapon& wep)
{
	Weapon& wOb = (Weapon&)*this;
	Weapon temp = wep;	   
	wep = wOb;	
	wOb = temp;	
}


//////////////////////////////////  Grenade Class Methods Definition   ////////////////////

Grenade:: Grenade(const hgeVector &pos , const hgeVector &dir, eWEAPONS id):Launch(3500)
{
	bDead= false;
	width=height=0.0f;
	sprite = 0;
	vSpeed = hgeVector(250.0f,-100.0f);
	vSpeed.x  += rand()%20; 
	vPosition = pos;
	vDirection = dir;
	fRotate = 0.5f;
	//Launch.setEndTime(3500);
	eId = id;
	fScale = 1.0f; fVscale = 0.0f;
}

void Grenade::Init(HTEXTURE hTex)
{
	this->sprite = new hgeSprite(hTex,0,30,13,13);
	sprite->SetHotSpot(7,7);
	height = 13;
	width = 13;
	Launch.reset();
	if(eId == LAUNCHER_GRENADE) 
	{ sprite->SetColor(0xff0f0f0f); fScale = 0.8; fVscale = 0.8f; }
	
}

void Grenade::Release()
{
	delete sprite;
	sprite = 0;
}

void Grenade::Render()
{
	sprite->RenderEx( vPosition.x,vPosition.y, fRotate, fScale, fVscale);
}

void Grenade::Move(float dt)
{
	vPosition.x += vDirection.x*(vSpeed.x*dt);
	vPosition.y += vDirection.y*(vSpeed.y*dt);
}

bool Grenade::Explode() const
{
	return Launch.TimeOver();
}


Grenade::~Grenade()
{
	this->Release();
}
