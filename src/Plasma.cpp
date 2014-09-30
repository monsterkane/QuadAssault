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

void Plazma::Init(GameState* stanje)
{
	Weapon::Init(stanje);
    tex=stanje->GetTM()->DajTexturu("../data/weapon1.tga")->id;
    texN=stanje->GetTM()->DajTexturu("../data/weapon1Normal.tga")->id;
    texG=stanje->GetTM()->DajTexturu("../data/weapon2Glow.tga")->id;
	chargingSpeed=100;
	requiredEnergy=6;
}
void Plazma::Update(float deltaT)
{
	Weapon::Update(deltaT);
}
void Plazma::Render()
{
	Weapon::Render();
}
void Plazma::Fire(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Weapon::Fire(poz,smjer,mapa,vlasnik);
	if(currentCharging==charging)
	{
		FireProjectile(new PlazmaProjektil());
		currentCharging=0;
	}
}
