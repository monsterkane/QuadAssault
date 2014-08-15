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

#include "LaserProjectile.h"
#include "GameState.h"

void LaserProjektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,mapa,vlasnik);
	brzina=910;
	domet=600;
	steta=4;

	svjetlo->Init(poz,128,stanje);
	svjetlo->Postavke(Vec3(0.5, 1.0, 0.2),12);

    sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("../data/Zvukovi/laser1.wav"));
    z->play();

    texG=stanje->DajMT()->DajTexturu("../data/laser1Glow.tga")->id;
}
void LaserProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
}
void LaserProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==GLOW)
	{
		float rot=atan2(smjer.y,smjer.x)*180/3.14 + 90;	
		SpriteT(poz-Vec2(8,16),Vec2(16,32),rot,texG);		
	}
}
void LaserProjektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	Explosion* e=stanje->DodajExploziju();
	e->Init(poz,128,stanje);
	e->Setup(8,100,80);
	e->SetColor(Vec3(1.0, 0.75, 0.5));	
}
