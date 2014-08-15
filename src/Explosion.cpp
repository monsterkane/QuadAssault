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

#include "Explosion.h"
#include "GameState.h"

Explosion::Explosion()
{
}
Explosion::~Explosion()
{
    light->Unisti();
    light = NULL;
    state = NULL;
}
void Explosion::Init(Vec2 pos, float radius, GlavnoStanje* state)
{
    this->poz=pos;
	this->radius=radius;
    this->state=state;
    dead=false;
    destroyed=false;

    intensity=0;
    maxIntensity=4;
    growthRate=35;
    deathRate=10;

    color=Vec3(1.0, 0.75, 0.5);

    light=state->DodajSvjetlo(false);
    light->Init(pos,radius,state);
    light->Postavke(color, 0);
    light->PostaviExplozija(true);
}
void Explosion::Setup(float intensity, float growthRate, float deathRate)
{
    maxIntensity=intensity*2;
    this->growthRate=growthRate;
    this->deathRate=deathRate;
}
void Explosion::SetColor(Vec3 color)
{
    this->color=color;
}
void Explosion::Update(float deltaT)
{
    if(dead==false)
	{
        if(intensity<maxIntensity)
            intensity+=growthRate*deltaT;
		else
		{
            dead=true;
            intensity=maxIntensity;
		}
	}	
    if(dead==true)
	{
        if(intensity>0)
            intensity-=deathRate*deltaT;
		else
		{			
            destroyed=true;
            intensity=0;
		}
	}	
		
    light->Postavke(color, intensity);
}

void Explosion::Render()
{
}
