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

#include "TrashPickup.h"
#include "GameState.h"

void SmecePickup::Init(Vec2 poz, GlavnoStanje* stanje)
{
	Stvar::Init(poz,stanje);

	dim.x=16;
	dim.y=16;	

	smjer.x=stanje->DajIgru()->Rand(1,10)-5;
	smjer.x/=5;
	smjer.y=stanje->DajIgru()->Rand(1,10)-5;
	smjer.y/=5;
	smjer.Normaliziraj();

	brzina=200;

	cesticaTimer=1.0;

	s=stanje->DodajSvjetlo(false);
	s->Init(poz,64,stanje);
	s->Postavke(Vec3(1.0, 0.75, 0.5),4);	
	s->PostaviExplozija(true);
	
    tex=stanje->DajMT()->DajTexturu("../data/SmeceDiffuse.tga")->id;
    texN=stanje->DajMT()->DajTexturu("../data/SmeceNormal.tga")->id;
}
void SmecePickup::Update(float deltaT)
{
	Stvar::Update(deltaT);		
	
	if(brzina>0.0)
	{
		s->PromijeniPoz(DajSredinu());
		if(cesticaTimer>=1.0)
		{
			SmeceCestica* c=(SmeceCestica*)stanje->DodajCesticu(new SmeceCestica());
			c->Init(DajPoz(),stanje);		
			cesticaTimer=0.0;
		}
		else
			cesticaTimer+=deltaT*10;

		poz.y+=smjer.y*brzina*deltaT;
		if(ProvjeraSudara()==true)
		{
			poz.y-=smjer.y*brzina*deltaT;
			smjer.y=-smjer.y;
		}
		poz.x+=smjer.x*brzina*deltaT;
		if(ProvjeraSudara()==true)
		{
			poz.x-=smjer.x*brzina*deltaT;
			smjer.x=-smjer.x;
		}
		brzina-=100*deltaT;
	}
	else
	{
		brzina=0.0;
	}

	
}
bool SmecePickup::ProvjeraSudara()
{
	Box k1;
	k1.v1=poz;
	k1.v2=poz+dim;
	unsigned char** mapa=stanje->DajMapu();
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
}
void SmecePickup::Render(unsigned char stil)
{
	if(stil!=GLOW)
	{
		GLuint t;
		if(stil==DIFFUSE)
			t=tex;
		if(stil==NORMAL)
			t=texN;
	
		SpriteT(poz,Vec2(dim.x,dim.y),0,t);
		glColor3f(1.0, 1.0, 1.0);
	}
	
}
void SmecePickup::Unisti()
{
	
}
void SmecePickup::Pokupi(Igrac* igrac)
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
        stanje->DajMZ()->DajZvuk("../data/Zvukovi/pickup.wav"));
    z->play();
	unisten=true;

	s->Unisti();
	Explosion* e=stanje->DodajExploziju();
	e->Init(DajSredinu(),128,stanje);
	e->Setup(12,100,50);
	e->SetColor(Vec3(1.0, 0.75, 0.5));	

	igrac->DodajHP(2);
}
