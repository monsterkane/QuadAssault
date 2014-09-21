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

#include "TrashParticle.h"
#include "GameState.h"

void SmeceCestica::Init(Vec2 poz, GlavnoStanje* stanje)
{
	Cestica::Init(poz,stanje);
	maxZivot=45;
	zivot=maxZivot;	
    tex=stanje->DajMT()->DajTexturu("../data/Smoke1Diffuse.tga")->id;
    texN=stanje->DajMT()->DajTexturu("../data/Smoke1Normal.tga")->id;
}
void SmeceCestica::Update(float deltaT)
{
	Cestica::Update(deltaT);
}
void SmeceCestica::Render(unsigned char stil)
{
	Cestica::Render(stil);
}
