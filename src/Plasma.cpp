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

#include "Plasma.h"
#include "GameState.h"
#include "PlasmaProjectile.h"

void Plazma::Init(GlavnoStanje* stanje)
{
	Oruzje::Init(stanje);
    tex=stanje->DajMT()->DajTexturu("../data/weapon1.tga")->id;
    texN=stanje->DajMT()->DajTexturu("../data/weapon1Normal.tga")->id;
    texG=stanje->DajMT()->DajTexturu("../data/weapon2Glow.tga")->id;
	brzinaPunjenja=100;
	potrebnaEnergija=6;
}
void Plazma::Update(float deltaT)
{
	Oruzje::Update(deltaT);
}
void Plazma::Render()
{
	Oruzje::Render();
}
void Plazma::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** maps, bool vlasnik)
{
	Oruzje::Pucaj(poz,smjer,maps,vlasnik);
	if(trenutnoPunjenje==punjenje)
	{
		IspaliProjektil(new PlazmaProjektil());
		trenutnoPunjenje=0;
	}
}
