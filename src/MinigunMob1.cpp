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

#include "MinigunMob1.h"
#include "GameState.h"
#include "MinigunProjectile.h"

void MinigunMob1::Init(Vec2 poz, GameState* stanje, unsigned char** mapa)
{
	Mob::Init(poz,stanje,mapa);

	dim.x=64;
	dim.y=64;
	
	maxbrzina=250;	
	brzinaPunjenja=750;	
	domet=512;

	hp=35;
    textura=stanje->GetTM()->DajTexturu("../data/mob1Diffuse.tga")->id;
    texturaN=stanje->GetTM()->DajTexturu("../data/mob1Normal.tga")->id;
    texturaG=stanje->GetTM()->DajTexturu("../data/mob3Glow.tga")->id;
}
void MinigunMob1::Update(float deltaT)
{
	Mob::Update(deltaT);
	Pucanje(new MinigunProjektil(),deltaT);	
	Vec2 smjer;
	smjer=stanje->GetPlayer()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
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
void MinigunMob1::Render(unsigned char stil)
{
	Mob::Render(stil);
}
void MinigunMob1::Pucanje(Projektil* p, float deltaT)
{	
	Mob::Pucanje(p,deltaT);	
}
void MinigunMob1::Unisti()
{
    sf::Sound* z = stanje->GetSound(new sf::Sound(), stanje->GetSM()->DajZvuk("../data/Sounds/explosion1.wav"));
    z->play();
	Mob::Unisti();
}
void MinigunMob1::PrimiStetu(Projektil* projektil)
{
	Mob::PrimiStetu(projektil);
}
