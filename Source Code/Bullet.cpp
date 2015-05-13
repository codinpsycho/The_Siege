#include "Bullet.h"
#include <hgeVector.h>

Bullet::Bullet(eBULLETID id, hgeVector v,hgeVector dir):vPosition(v),vDirection(dir)
{
	//rect = 0;
	PartSprite = 0;
	part = 0;
	eID = id;
	part = NULL;
	bDead = false;
	spr = NULL;
}

Bullet::~Bullet(void) 
{ 
	this->Release(); 
}

bool Bullet::IsDead()
{
	return bDead;
}

void Bullet::Move(float dt)
{
	vPosition.x += vDirection.x * vSpeed.x;
	vPosition.y += vDirection.y * vSpeed.y;
	if (eID != ASSAULTRIFLE_BULLET && eID != SEMIAUTO_BULLET  && eID != ENEMYBULLET_TYPE1 && eID != ROCKETLAUNCHER_BULLET )
	{
		part->Update(dt);
		//part->FireAt(vPosition.x, vPosition.y/*-2.0f*/);
		part->MoveTo(vPosition.x, vPosition.y/*-2.0f*/);
	}

}	

void Bullet::Render()
{
	if (eID != ASSAULTRIFLE_BULLET && eID != SEMIAUTO_BULLET  && eID != ENEMYBULLET_TYPE1 && eID != ROCKETLAUNCHER_BULLET)
	{
		part->Render();		//if(eID == ROCKETLAUNCHER_BULLET ) spr->Render( vPosition.x,vPosition.y ); // the trail is outside
	}
	else
		spr->Render( vPosition.x,vPosition.y );
}

extern HTEXTURE ParTex;

bool Bullet::Init(HGE* engine,HTEXTURE hTEX)
{	
	switch(eID)
	{
	case ASSAULTRIFLE_BULLET: 
		//spr =  new hgeSprite(hTEX,82,54,8,8);				
		/*spr = new hgeSprite(hTEX,95,54,12,8);				*/
		spr =  new hgeSprite(hTEX,82,54,8,8);
		spr->SetColor(0xffffff00);
		vSpeed = hgeVector(20.0f,10.0f);

		if( vDirection.x < 0 )	
			spr->SetFlip(true,false);
		
		break;
	case SEMIAUTO_BULLET:
		//spr =  new hgeSprite(hTEX,0,54,21,13);
		spr =  new hgeSprite(hTEX,82,54,8,8);
		spr->SetColor(0xffffff00);
		vSpeed = hgeVector(15.0f,9.0f);
		break; 
	case SHOTGUN_BULLET:
		spr =  new hgeSprite(hTEX,82,54,8,8);
		PartSprite = new hgeSprite(ParTex,0,96,32,32);
		PartSprite->SetBlendMode(BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_NOZWRITE);
		PartSprite->SetHotSpot(16,16);
		part = new hgeParticleSystem("Particle Effects/shotgun.psi",PartSprite);
		part->FireAt(vPosition.x,vPosition.y);
		vSpeed = hgeVector(18.0f,8.0f);
		break; 	
	case ROCKETLAUNCHER_BULLET:
		spr =  new hgeSprite(hTEX,59,30,23,7);
		//PartSprite = new hgeSprite(ParTex,0,96,32,32);
		//part = new hgeParticleSystem("Particle Effects/LauncherTrail.psi",PartSprite);
		part = 0; PartSprite = 0;

		vSpeed = hgeVector(24.0f,8.0f);
		break;	
	case ENEMYBULLET_TYPE1:   
		spr =  new hgeSprite(hTEX,82,54,8,8);
		spr->SetColor(0xffff0000);
		part = new hgeParticleSystem("Particle Effects/OurBullets.psi",spr);
		part->FireAt(vPosition.x,vPosition.y);
		vSpeed = hgeVector(9.7f,7.0f);
		break;
	case ENEMYBULLET_TYPE2:
		spr =  new hgeSprite(hTEX,82,54,8,8);
		PartSprite = new hgeSprite(ParTex,0,96,32,32);
		PartSprite->SetBlendMode(BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_NOZWRITE);
		PartSprite->SetHotSpot(16,16);

		part = new hgeParticleSystem("Particle Effects/green.psi",PartSprite);
		part->FireAt(vPosition.x,vPosition.y);

		vSpeed = hgeVector(7.5f,4.0f);
		break;
	case ENEMYBULLET_TYPE3:
		spr =  new hgeSprite(hTEX,82,54,8,8);
		PartSprite = new hgeSprite(ParTex,0,96,32,32);
		PartSprite->SetBlendMode(BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_NOZWRITE);
		PartSprite->SetHotSpot(16,16);

		part = new hgeParticleSystem("Particle Effects/purple.psi",PartSprite);
		part->FireAt(vPosition.x,vPosition.y);

		vSpeed = hgeVector(5.36f,5.0f);
		break;
	case ENEMYBULLET_TYPE4:
		spr =  new hgeSprite(hTEX,82,54,8,8);
		PartSprite = new hgeSprite(ParTex,0,96,32,32);
		PartSprite->SetBlendMode(BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_NOZWRITE);
		PartSprite->SetHotSpot(16,16);

		part = new hgeParticleSystem("Particle Effects/pink.psi",PartSprite);
		part->FireAt(vPosition.x,vPosition.y);
		vSpeed = hgeVector(6.2f,4.0f);
		break;
	}
	return true;
}

void Bullet::Release()
{
	delete spr; spr =0;
	if( eID != ROCKETLAUNCHER_BULLET && part )
	{
		delete part; part = 0; 
	}
	delete PartSprite; PartSprite = 0;
}

float Bullet::GetHeight()
{
	return spr->GetHeight();	

}

float Bullet::GetWidth()
{
	return spr->GetWidth();
} 

eBULLETID Bullet::GetId()
{
	return eID;
}

bool Bullet::checkBound()
{
	if(  vPosition.x < 0 )
	{
		return false;
	}
	if( vPosition.x > 1366)
	{
		return false;	
	}
	if( vDirection.y < 0 && vPosition.y < 0 )
	{
		return false;
	}

	return true;
}

float Bullet::GetLeftFace()
{
	return vPosition.x;
}

float Bullet::GetRightFace()
{
	return vPosition.x + spr->GetHeight();
}

float Bullet::GetUpFace()
{
	return vPosition.y;
}

float Bullet::GetDownFace()
{
	return vPosition.y + spr->GetHeight();
}

