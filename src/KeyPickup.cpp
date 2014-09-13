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

#include "KeyPickup.h"
#include "GameState.h"

void KeyPickup::Init(Vec2 pos, GameState* state, int id)
{
    Stvar::Init(pos,state);

	dim.x=32;
	dim.y=32;
	this->id=id;
	
    rotation=0;
    tex=state->GetTM()->DajTexturu("../data/KljucDiffuse.tga")->id;
    texN=state->GetTM()->DajTexturu("../data/KljucNormal.tga")->id;
    texG=state->GetTM()->DajTexturu("../data/KljucGlow.tga")->id;

    light=state->GetLight(false);
    light->Init(pos+Vec2(dim.x/2,dim.y/2),128,state);
    if(id==RED)
        light->Postavke(Vec3(1.0,0.1,0.1),4);
    if(id==BLUE)
        light->Postavke(Vec3(0.1,0.25,1.0),4);
    if(id==GREEN)
        light->Postavke(Vec3(0.1,1.0,0.1),4);
}
void KeyPickup::Update(float deltaT)
{
	Stvar::Update(deltaT);
    rotation+=100*deltaT;
    if(rotation>360)
        rotation=0;
}
void KeyPickup::Render(unsigned char type)
{
	GLuint t;
    if(type==DIFFUSE)
		t=tex;
    if(type==NORMAL)
		t=texN;
    if(type==GLOW)
	{
		t=texG;
        if(id==RED)
			glColor3f(1.0, 0.1, 0.1);
        if(id==BLUE)
			glColor3f(0.1, 0.1, 1.0);
        if(id==GREEN)
			glColor3f(0.1, 1.0, 0.1);
	}
    SpriteT(DajPoz(),DajDim(),rotation,t);
	glColor3f(1.0, 1.0, 1.0);
}
void KeyPickup::Unisti()
{
    light->Unisti();
}
void KeyPickup::Pokupi(Igrac* player)
{
    sf::Sound* s = stanje->GetSound(new sf::Sound(),
        stanje->GetSM()->DajZvuk("../data/Zvukovi/pickup.wav"));
    s->play();
    int door;
    if(id==RED)
        door=RED_DOOR;
    if(id==BLUE)
        door=BLUE_DOOR;
    if(id==GREEN)
        door=GREEN_DOOR;

	for(int x=0; x<MX; x++)
	for(int y=0; y<MY; y++)
	{
        if(stanje->GetMap()[x][y]==door)
		{
			stanje->GetMap()[x][y]=FLOOR;
			stanje->GetBlock(x,y)->Init(Vec2(x*BLOCK_SIZE, y*BLOCK_SIZE), FLOOR, stanje);
			Explosion* e=stanje->GetExplosion();
			e->Init(Vec2(x*BLOCK_SIZE+BLOCK_SIZE/2, y*BLOCK_SIZE+BLOCK_SIZE/2), 128, stanje);
			e->Setup(20,1000,50);
            if(id==RED)
				e->SetColor(Vec3(1.0, 0.1, 0.1));
            if(id==BLUE)
				e->SetColor(Vec3(0.1, 0.1, 1.0));
            if(id==GREEN)
				e->SetColor(Vec3(0.1, 1.0, 0.1));
		}
	}
	
	
	unisten=true;
}
