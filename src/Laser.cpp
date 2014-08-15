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

#include "Laser.h"
#include "GameState.h"
#include "LaserProjectile.h"

void Laser::Init(GlavnoStanje* stanje)
{
	Oruzje::Init(stanje);
    tex=stanje->DajMT()->DajTexturu("../data/oruzje1.tga")->id;
    texN=stanje->DajMT()->DajTexturu("../data/oruzje1Normal.tga")->id;
    texG=stanje->DajMT()->DajTexturu("../data/oruzje1Glow.tga")->id;
	brzinaPunjenja=600;
	potrebnaEnergija=2;
}
void Laser::Update(float deltaT)
{
	Oruzje::Update(deltaT);
}
void Laser::Render()
{
	Oruzje::Render();
}
void Laser::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Oruzje::Pucaj(poz,smjer,mapa,vlasnik);
	if(trenutnoPunjenje==punjenje)
	{
		for(int i=0; i<1; i++)
		{
			absPoz.x-=smjer.x*4;
			absPoz.y-=smjer.y*4;		
			IspaliProjektil(new LaserProjektil());				
		}
		trenutnoPunjenje=0;
	}
}
