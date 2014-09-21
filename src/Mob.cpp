/*
 *   Copyright (C) 2011, 2012 Marko Stanić
 *   Copyright (C) 2014 QuadAssault contributors    
 *
 *   This file is part of QuadAssault.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with This program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Mob.h"
#include "GameState.h"
#include "Projectile.h"
#include "LaserProjectile.h"
#include "TrashPickup.h"

void Mob::Init(Vec2 poz, GameState* stanje, unsigned char** mapa)
{
	this->poz=poz;
	this->stanje=stanje;
	this->mapa=mapa;

	dim.x=64;
	dim.y=64;

	rotacija=0;
	akceleracija=0;
	brzina=100;
	maxbrzina=100;	

	brzinaPunjenja=250;
	punjenje=0;
	domet=512;

	hp=100;	
}
void Mob::Update(float deltaT)
{
	akceleracija=1;

	Vec2 smjer;
	smjer=stanje->GetPlayer()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
	smjer.Normaliziraj();

	rotacija=atan2(smjer.y,smjer.x)*180/3.14 + 90;

	Vec2 moment;
	moment.x=cos((rotacija-90)/180.0*3.14)*akceleracija;
	moment.y=sin((rotacija-90)/180.0*3.14)*akceleracija;	

	poz.y+=moment.y*brzina*deltaT;
	if(ProvjeraSudara())
		poz.y-=moment.y*brzina*deltaT;
	poz.x+=moment.x*brzina*deltaT;
	if(ProvjeraSudara())
		poz.x-=moment.x*brzina*deltaT;

	SudarProjektila();	

	if(hp<=0)
		unisten=true;

	akceleracija=0;
}
void Mob::Render(unsigned char stil)
{	
	GLuint tex;
	
	if(stil==DIFFUSE)
		tex=textura;
	if(stil==NORMAL)
		tex=texturaN;
	if(stil==GLOW)
		tex=texturaG;

	if(stil==DIFFUSE) //SJENA
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();		
		glColor4f(0.0, 0.0, 0.0, 0.6);			
		SpriteT(poz+Vec2(5,5),dim,rotacija,tex);			
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();
		glDisable(GL_BLEND);
	}

	glPushMatrix();	
	SpriteT(poz,dim,rotacija,tex);	
	glPopMatrix();	
}
void Mob::Unisti()
{
	Explosion* e=stanje->GetExplosion();
	e->Init(DajSredinu(),128,stanje);
	e->Setup(128,3000,200);
	for(int i=0; i<4; i++)
	{
		SmecePickup* c=(SmecePickup*)stanje->GetThing(new SmecePickup());
		c->Init(DajSredinu(),stanje);
	}
}
void Mob::SpawnEfekt()
{
	Explosion* e=stanje->GetExplosion();
	e->Init(DajSredinu(),512,stanje);
	e->Setup(32,1000,100);
	e->SetColor(Vec3(0.25,0.5,1.0));
}

void Mob::DodajMoment(float x)
{
	akceleracija=x;
}
void Mob::Rotiraj(float rot)
{
	rotacija+=rot;
	if(rotacija>360.0)
		rotacija=0.1;
	if(rotacija<0.0)
		rotacija=359.9;
}

bool Mob::ProvjeraSudara()
{
	Box k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
	for(int x=(poz.x/BLOCK_SIZE)-2; x<(poz.x/BLOCK_SIZE)+2; x++)
	for(int y=(poz.y/BLOCK_SIZE)-2; y<(poz.y/BLOCK_SIZE)+2; y++)
	{
		if(x>=0 && x<MX && y>=0 && y<MY)
		if(mapa[x][y]!=FLOOR)
		{
			Box k2;
			k2.v1=Vec2(x*BLOCK_SIZE,y*BLOCK_SIZE);
			k2.v2=Vec2(x*BLOCK_SIZE,y*BLOCK_SIZE)+Vec2(BLOCK_SIZE,BLOCK_SIZE);
			if(k1.Collision(&k2))
				return true;
		}
	}
	for(int i=0; i<stanje->GetMobs()->size(); i++)
	{
		if(stanje->GetMobs()->at(i)!=this)
		{
			Box k2;
			k2.v1=stanje->GetMobs()->at(i)->DajPoz();
			k2.v2=stanje->GetMobs()->at(i)->DajPoz()+
				stanje->GetMobs()->at(i)->DajDim();
			if(k1.Collision(&k2))
				return true;
		}
	}
	Box k2;
	k2.v1=stanje->GetPlayer()->DajPoz();
	k2.v2=stanje->GetPlayer()->DajPoz()+
		stanje->GetPlayer()->DajDim();
	if(k1.Collision(&k2))
		return true;

	return false;
}
void Mob::SudarProjektila()
{
	Box k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
	for(int i=0; i<stanje->GetProjectiles()->size(); i++)
	{
		if(stanje->GetProjectiles()->at(i)->vlasnik==IGRAC)
		{
			Box k2;
			k2.v1=stanje->GetProjectiles()->at(i)->DajPoz();
			k2.v2=stanje->GetProjectiles()->at(i)->DajPoz()+
				stanje->GetProjectiles()->at(i)->DajDim();
			if(k1.Collision(&k2))
			{
				PrimiStetu(stanje->GetProjectiles()->at(i));				
			}
		}
	}
}

void Mob::PrimiStetu(Projektil* projektil)
{
	hp-=projektil->DajStetu();
	projektil->unisten=true;
}
void Mob::Pucanje(Projektil* p, float deltaT)
{
	if(stanje->GetPlayer()->JeUnisten()==false)
	{
		if(punjenje<100)
			punjenje+=brzinaPunjenja*deltaT;
		if(punjenje>=100)
		{
			Vec2 smjerPucanja=stanje->GetPlayer()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
			float l=smjerPucanja.Duljina();
			if(l<domet)
			{
				smjerPucanja.Normaliziraj();
				Projektil* pr=stanje->GetProjectile(p);
				pr->Init(DajSredinu(),smjerPucanja,stanje,mapa,NEPRIJATELJ);				
			}	
			punjenje=0;
		}
	}
}
