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

#include "MinigunProjectile.h"
#include "GameState.h"

void MinigunProjektil::Init(Vec2 poz, Vec2 smjer, GameState* stanje, unsigned char** mapa, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,mapa,vlasnik);
	brzina=1000;
	domet=500;
	steta=0.5;

	svjetlo->Init(poz,128,stanje);
	svjetlo->Postavke(Vec3(1.0, 1.0, 0.1),12);

    sf::Sound* z = stanje->GetSound(new sf::Sound(), stanje->GetSM()->DajZvuk("../data/Sounds/minigun1.wav"));
    z->play();

    texG=stanje->GetTM()->DajTexturu("../data/minigun1Glow.tga")->id;
}
void MinigunProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
}
void MinigunProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==GLOW)
	{
		float rot=atan2(smjer.y,smjer.x)*180/3.14 + 90;	
		SpriteT(pos-Vec2(8,16),Vec2(16,32),rot,texG);
	}
}
void MinigunProjektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	Explosion* e=stanje->GetExplosion();
	e->Init(pos,64,stanje);
	e->Setup(4,100,80);
	e->SetColor(Vec3(1.0, 0.75, 0.5));	
}
