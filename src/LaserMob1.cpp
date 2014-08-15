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

#include "LaserMob1.h"
#include "GameState.h"
#include "LaserProjectile.h"

void LaserMob1::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	Mob::Init(poz,stanje,mapa);

	dim.x=64;
	dim.y=64;
	
	maxbrzina=150;	
	brzinaPunjenja=250;	
	domet=512;

	hp=40;
    textura=stanje->DajMT()->DajTexturu("../data/mob1Diffuse.tga")->id;
    texturaN=stanje->DajMT()->DajTexturu("../data/mob1Normal.tga")->id;
    texturaG=stanje->DajMT()->DajTexturu("../data/mob1Glow.tga")->id;
}
void LaserMob1::Update(float deltaT)
{
	Mob::Update(deltaT);
	Pucanje(new LaserProjektil(),deltaT);	
	Vec2 smjer;
	smjer=stanje->DajIgraca()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
	if(smjer.Duljina()<300)
	{
		brzina-=100*deltaT;
		if(brzina<0)
			brzina=0;
	}
	else
	{
		brzina+=100*deltaT;
		if(brzina>maxbrzina)
			brzina=maxbrzina;
	}
}
void LaserMob1::Render(unsigned char stil)
{
	Mob::Render(stil);
}
void LaserMob1::Pucanje(Projektil* p, float deltaT)
{	
	Mob::Pucanje(p,deltaT);	
}
void LaserMob1::Unisti()
{
    sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("../data/Zvukovi/explozija1.wav"));
    z->play();
	Mob::Unisti();
}
void LaserMob1::PrimiStetu(Projektil* projektil)
{
	Mob::PrimiStetu(projektil);
}
