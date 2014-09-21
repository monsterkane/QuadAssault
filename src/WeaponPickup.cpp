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

#include "WeaponPickup.h"
#include "GameState.h"
#include "Laser.h"
#include "Plasma.h"
#include "Minigun.h"

void OruzjePickup::Init(Vec2 poz, GlavnoStanje* stanje, int id)
{
	Stvar::Init(poz,stanje);

	dim.x=32;
	dim.y=32;
	this->id=id;
	
	rotacija=0;
	if(id==LASER1)
	{
        tex=stanje->DajMT()->DajTexturu("../data/weapon1.tga")->id;
        texN=stanje->DajMT()->DajTexturu("../data/weapon1Normal.tga")->id;
        texG=stanje->DajMT()->DajTexturu("../data/weapon1Glow.tga")->id;
	}
	if(id==PLAZMA1)
	{
        tex=stanje->DajMT()->DajTexturu("../data/weapon1.tga")->id;
        texN=stanje->DajMT()->DajTexturu("../data/weapon1Normal.tga")->id;
        texG=stanje->DajMT()->DajTexturu("../data/weapon2Glow.tga")->id;
	}
	if(id==MINIGUN1)
	{
        tex=stanje->DajMT()->DajTexturu("../data/weapon1.tga")->id;
        texN=stanje->DajMT()->DajTexturu("../data/weapon1Normal.tga")->id;
        texG=stanje->DajMT()->DajTexturu("../data/weapon3Glow.tga")->id;
	}

	s=stanje->DodajSvjetlo(false);
	s->Init(poz+Vec2(dim.x/2,dim.y/2),256,stanje);
	if(id==LASER1)
		s->Postavke(Vec3(0.2,1.0,0.2),6);
	if(id==PLAZMA1)
		s->Postavke(Vec3(0.2,0.2,1.0),6);
}
void OruzjePickup::Update(float deltaT)
{
	Stvar::Update(deltaT);
	rotacija+=100*deltaT;
	if(rotacija>360)
		rotacija=0;
}
void OruzjePickup::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==GLOW)
		t=texG;
	SpriteT(poz+Vec2(dim.x/2-8,0),Vec2(16,32),rotacija,t);
}
void OruzjePickup::Unisti()
{
	s->Unisti();
}
void OruzjePickup::Pokupi(Igrac* igrac)
{
    sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("../data/Sounds/pickup.wav"));
    z->play();
	if(id==LASER1)
		igrac->DodajOruzje(new Laser());
	if(id==PLAZMA1)
		igrac->DodajOruzje(new Plazma());
	if(id==MINIGUN1)
		igrac->DodajOruzje(new Minigun());
	unisten=true;
}
