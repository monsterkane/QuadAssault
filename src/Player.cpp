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

#include "Player.h"
#include "Box.h"
#include "GameState.h"
#include "Laser.h"
#include "Plasma.h"
#include "Minigun.h"
#include "Light.h"

void Igrac::Init(Vec2 poz, GameState* stanje, unsigned char** mapa)
{
    for(int i=0; i<4; ++i)
        oruzjeSlot[i] = false;

	this->poz=poz;
	this->stanje=stanje;
	this->mapa=mapa;
	dim.x=64;
	dim.y=64;

    textura=stanje->GetTM()->DajTexturu("../data/tenkTorzoDiffuse.tga")->id;
    texturaN=stanje->GetTM()->DajTexturu("../data/tenkTorzoNormal.tga")->id;

    podloga_tex=stanje->GetTM()->DajTexturu("../data/tenkPodlogaDiffuse.tga")->id;
    podloga_normal=stanje->GetTM()->DajTexturu("../data/tenkPodlogaNormal.tga")->id;

    tracnica_tex=stanje->GetTM()->DajTexturu("../data/tracnicaDiffuse.tga")->id;
    tracnica_normal=stanje->GetTM()->DajTexturu("../data/tracnicaNormal.tga")->id;
	
	farovi=stanje->GetLight(false);
	farovi->Init(Vec2(0.0, 0.0), 1024, stanje);
	farovi->Postavke(Vec3(1.0, 1.0, 1.0), 16);

	for(int i=0; i<4; i++)
		oruzja[i]=NULL;

	hp=100;
	energija=100.0;
	puca=false;
	unisten=false;

	pomak_tracnica=0.0;
	rotacija=0.0;

	brzina=200;
}

void Igrac::Pucaj(Vec2 misPoz, float deltaT)
{
	if(unisten==false)
	{
		Vec2 smjer;
		smjer=misPoz-poz-Vec2(dim.x/2, dim.y/2);
		smjer.Normaliziraj();

		for(int i=0; i<4; i++)
		{		
			if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
			{
				if(energija>=oruzja[i]->DajPotrebnuEnergiju())
				{
					Vec2 oPoz=oruzja[i]->DajPoz();
		
					float kut=atan2(oPoz.y,oPoz.x)*180/3.14 + 90;

					Vec2 slot;
					slot.x=cos((rotacijaTorza+kut)/180.0*3.14);
					slot.y=sin((rotacijaTorza+kut)/180.0*3.14);
					slot.Mnozi(sqrt(oPoz.x*oPoz.x + oPoz.y*oPoz.y)); //oruzje x offset

					oruzja[i]->Pucaj(DajSredinu()+slot,smjer,mapa,IGRAC);									
				}
				puca=true;
			}
		}
	}
}
bool Igrac::ProvjeraSudara()
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
		Box k2;
		k2.v1=stanje->GetMobs()->at(i)->DajPoz();
		k2.v2=stanje->GetMobs()->at(i)->DajPoz()+
			stanje->GetMobs()->at(i)->DajDim();
		if(k1.Collision(&k2))
			return true;		
	}

	return false;
}
void Igrac::SudarProjektila()
{
	Box k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
	for(int i=0; i<stanje->GetProjectiles()->size(); i++)
	{
		if(stanje->GetProjectiles()->at(i)->vlasnik==NEPRIJATELJ)
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
void Igrac::PrimiStetu(Projektil* p)
{
	if(unisten==false)
	{
		hp-=p->DajStetu();
		p->unisten=true;
	}
}
void Igrac::DodajOruzje(Oruzje* o)
{
	for(int i=0; i<4; i++)
	{
		if(oruzjeSlot[i]!=true)
		{
			oruzja[i]=o;
			oruzjeSlot[i]=true;
			o->Init(stanje);
			if(i==2)
				o->PromijeniPoz(Vec2(-24,0));
			if(i==0)
				o->PromijeniPoz(Vec2(-8,-12));
			if(i==1)
				o->PromijeniPoz(Vec2(8,-12));
			if(i==3)
				o->PromijeniPoz(Vec2(24,0));
			break;
		}
	}
}
bool Igrac::JeUnisten()
{
	return unisten;
}
void Igrac::OduzmiEnergiju(float e)
{
	energija-=e;
	if(energija<0.0)
		energija=0.0;
}
void Igrac::DodajHP(float kolicina)
{
	hp+=kolicina;
	if(hp>100.0)
		hp=100.0;
}
Igrac::Igrac()
{
}
Igrac::~Igrac()
{
	for(int i=0; i<4; i++)
		if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
		{
			delete oruzja[i];	
			oruzja[i]=NULL;
		}
}
