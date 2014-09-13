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

void KljucPickup::Init(Vec2 poz, GameState* stanje, int id)
{
	Stvar::Init(poz,stanje);

	dim.x=32;
	dim.y=32;
	this->id=id;
	
	rotacija=0;
    tex=stanje->GetTM()->DajTexturu("../data/KljucDiffuse.tga")->id;
    texN=stanje->GetTM()->DajTexturu("../data/KljucNormal.tga")->id;
    texG=stanje->GetTM()->DajTexturu("../data/KljucGlow.tga")->id;

	s=stanje->GetLight(false);
	s->Init(poz+Vec2(dim.x/2,dim.y/2),128,stanje);
	if(id==CRVENI)
		s->Postavke(Vec3(1.0,0.1,0.1),4);	
	if(id==PLAVI)
		s->Postavke(Vec3(0.1,0.25,1.0),4);	
	if(id==ZELENI)
		s->Postavke(Vec3(0.1,1.0,0.1),4);	
}
void KljucPickup::Update(float deltaT)
{
	Stvar::Update(deltaT);
	rotacija+=100*deltaT;
	if(rotacija>360)
		rotacija=0;
}
void KljucPickup::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==GLOW)
	{
		t=texG;
		if(id==CRVENI)
			glColor3f(1.0, 0.1, 0.1);
		if(id==PLAVI)
			glColor3f(0.1, 0.1, 1.0);
		if(id==ZELENI)
			glColor3f(0.1, 1.0, 0.1);
	}
	SpriteT(DajPoz(),DajDim(),rotacija,t);
	glColor3f(1.0, 1.0, 1.0);
}
void KljucPickup::Unisti()
{
	s->Unisti();
}
void KljucPickup::Pokupi(Igrac* igrac)
{
	sf::Sound* z = stanje->GetSound(new sf::Sound(),
        stanje->GetSM()->DajZvuk("../data/Zvukovi/pickup.wav"));
    z->play();
	int vrata;
	if(id==CRVENI)	
		vrata=RED_DOOR;
	if(id==PLAVI)	
		vrata=BLUE_DOOR;
	if(id==ZELENI)
		vrata=GREEN_DOOR;

	for(int x=0; x<MX; x++)
	for(int y=0; y<MY; y++)
	{
		if(stanje->GetMap()[x][y]==vrata)
		{
			stanje->GetMap()[x][y]=FLOOR;
			stanje->GetBlock(x,y)->Init(Vec2(x*BLOCK_SIZE, y*BLOCK_SIZE), FLOOR, stanje);
			Explosion* e=stanje->GetExplosion();
			e->Init(Vec2(x*BLOCK_SIZE+BLOCK_SIZE/2, y*BLOCK_SIZE+BLOCK_SIZE/2), 128, stanje);
			e->Setup(20,1000,50);
			if(id==CRVENI)
				e->SetColor(Vec3(1.0, 0.1, 0.1));
			if(id==PLAVI)
				e->SetColor(Vec3(0.1, 0.1, 1.0));
			if(id==ZELENI)
				e->SetColor(Vec3(0.1, 1.0, 0.1));
		}
	}
	
	
	unisten=true;
}
