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

#include "Projectile.h"
#include "GameState.h"
#include "Explosion.h"

void Projektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	this->poz=poz;
	this->smjer=smjer;
	this->stanje=stanje;
	this->mapa=mapa;
	this->vlasnik=vlasnik;	

	svjetlo=stanje->DodajSvjetlo(false);	

	domet_timer=0;

	unisten=false;

	//NASLJEDJEN DIO:

	brzina=1000;
	domet=600;
	steta=50;

	dim.x=1;
	dim.y=1;

	svjetlo->Init(poz,64,stanje);
	svjetlo->Postavke(Vec3(1.0, 0.5, 0.25), 2);	
}
void Projektil::Update(float deltaT)
{
	for(int x=(poz.x/BLOCK_SIZE)-2; x<(poz.x/BLOCK_SIZE)+2; x++)
	for(int y=(poz.y/BLOCK_SIZE)-2; y<(poz.y/BLOCK_SIZE)+2; y++)
	{
		if(unisten==true)
		{
			break;break;
		}
		if(x>=0 && x<MX && y>=0 && y<MY)
		if(mapa[x][y]!=FLOOR && mapa[x][y]!=EMPTY)
		{
			Box k1;
			k1.v1=poz;
			k1.v2=poz+dim;

			Box k2;
			k2.v1=Vec2(x*BLOCK_SIZE,y*BLOCK_SIZE);
			k2.v2=Vec2(x*BLOCK_SIZE,y*BLOCK_SIZE)+Vec2(BLOCK_SIZE,BLOCK_SIZE);
			if(k1.Collision(&k2))
				unisten=true;
		}
	}
	if(unisten==false)
	{		
		poz.y+=smjer.y*brzina*deltaT;
		poz.x+=smjer.x*brzina*deltaT;
		svjetlo->PromijeniPoz(poz);		
		domet_timer+=1000*deltaT;
		if(domet_timer>domet)
			unisten=true;
	}
	
}
void Projektil::Render(unsigned char stil)
{
}
void Projektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	svjetlo=NULL;
	Explosion* e=stanje->DodajExploziju();
	e->Init(poz,128,stanje);
	e->Setup(4,100,20);
	e->SetColor(Vec3(0.25, 0.5, 1.0));	
	e=NULL;
}
Projektil::Projektil()
{
}
Projektil::~Projektil()
{	
}
float Projektil::DajStetu()
{
	return steta;
}