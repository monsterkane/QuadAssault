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

#include "PlasmaProjectile.h"
#include "GameState.h"
#include "RocketSmoke.h"

void PlazmaProjektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** maps, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,maps,vlasnik);
	brzina=800;
	domet=800;
	steta=12;

	dim=Vec2(1,1);

	dimTimer=0.0;

	svjetlo->Init(poz,256,stanje);
	svjetlo->Postavke(Vec3(0.25, 0.5, 1.0),18);	

    tex=stanje->DajMT()->DajTexturu("../data/shell1.tga")->id;

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
        stanje->DajMZ()->DajZvuk("../data/Sounds/plasma1.wav"));
    z->play();
}
void PlazmaProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
	dimTimer+=deltaT*750;
	if(dimTimer>=10.0)
	{
		Cestica* c=stanje->DodajCesticu(new DimRakete());
		c->Init(poz+Vec2(dim.x/2,dim.y/2),stanje);
		dimTimer=0.0;
	}
}
void PlazmaProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==DIFFUSE)
		SpriteT(poz,dim,0,tex);
}
void PlazmaProjektil::Unisti()
{		
	unisten=true;
	svjetlo->Unisti();
	Explosion* e=stanje->DodajExploziju();	
	e->Init(poz,256,stanje);
	e->Setup(20,1000,50);
	e->SetColor(Vec3(1.0, 0.75, 0.5));

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
        stanje->DajMZ()->DajZvuk("../data/Sounds/explosion1.wav"));
    z->play();
}
