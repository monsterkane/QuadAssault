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

#include "Particle.h"
#include "GameState.h"
#include "Game.h"

void Cestica::Init(Vec2 poz, GameState* stanje)
{
	this->pos=poz;
	this->stanje=stanje;
	unisten=false;
	int xof=stanje->DajIgru()->Rand(2,4)-2;
	int yof=stanje->DajIgru()->Rand(2,4)-2;
	dim=Vec2(16+xof,16+yof);
	poz=poz+Vec2(xof,yof);
	zivot=100;
	maxZivot=zivot;	
}
void Cestica::Update(float deltaT)
{
	zivot-=deltaT*50;
	if(zivot<=0.0)
		unisten=true;
}
void Cestica::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==DIFFUSE)// || stil==NORMAL)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor3f(zivot/maxZivot, zivot/maxZivot, zivot/maxZivot );
		SpriteT(pos,dim,0,t);
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_BLEND);
	}
}
