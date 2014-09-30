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

#include "Minigun.h"
#include "GameState.h"
#include "MinigunProjectile.h"

void Minigun::Init(GameState* stanje)
{
	Weapon::Init(stanje);
    tex=stanje->GetTM()->DajTexturu("../data/weapon1.tga")->id;
    texN=stanje->GetTM()->DajTexturu("../data/weapon1Normal.tga")->id;
    texG=stanje->GetTM()->DajTexturu("../data/weapon3Glow.tga")->id;
	chargingSpeed=1500;
	requiredEnergy=0.5;
}
void Minigun::Update(float deltaT)
{
	Weapon::Update(deltaT);
}
void Minigun::Render()
{
	Weapon::Render();
}
void Minigun::Fire(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Weapon::Fire(poz,smjer,mapa,vlasnik);
	if(currentCharging==charging)
	{
		for(int i=0; i<1; i++)
		{
			absPos.x-=smjer.x*4;
			absPos.y-=smjer.y*4;		
			FireProjectile(new MinigunProjektil());				
		}
		currentCharging=0;
	}
}
