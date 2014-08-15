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

#include "Thing.h"
#include "GameState.h"
#include "Game.h"

void Stvar::Init(Vec2 poz, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->stanje=stanje;

	dim.x=32;
	dim.y=32;	
}
void Stvar::Update(float deltaT)
{
	Box k1;
	k1.v1=poz;
	k1.v2=poz+dim;
	Box k2; 
	k2.v1=stanje->DajIgraca()->DajPoz();
	k2.v2=stanje->DajIgraca()->DajPoz()+stanje->DajIgraca()->DajDim();
	if(k1.Collision(&k2))
	{
		Pokupi(stanje->DajIgraca());
	}
}
void Stvar::Render(unsigned char stil)
{
}
void Stvar::Unisti()
{
}
void Stvar::Pokupi(Igrac* igrac)
{
}
