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

#include "PlasmaMob1.h"
#include "GameState.h"
#include "PlasmaProjectile.h"

void PlazmaMob1::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	Mob::Init(poz,stanje,mapa);

	dim.x=64;
	dim.y=64;
	
	brzina=75;
	maxbrzina=75;
	brzinaPunjenja=50;	
	domet=512;

	hp=60;
    textura=stanje->DajMT()->DajTexturu("../data/mob1Diffuse.tga")->id;
    texturaN=stanje->DajMT()->DajTexturu("../data/mob1Normal.tga")->id;
    texturaG=stanje->DajMT()->DajTexturu("../data/mob2Glow.tga")->id;
}
void PlazmaMob1::Update(float deltaT)
{
	Mob::Update(deltaT);
	Mob::Pucanje(new PlazmaProjektil(),deltaT);	
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
void PlazmaMob1::Render(unsigned char stil)
{
	Mob::Render(stil);
}
void PlazmaMob1::Unisti()
{
    sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("../data/Zvukovi/explozija1.wav"));
    z->play();
	Mob::Unisti();
}
void PlazmaMob1::PrimiStetu(Projektil* projektil)
{
	Mob::PrimiStetu(projektil);
}
