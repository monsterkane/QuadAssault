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

#include "RocketSmoke.h"
#include "GameState.h"
#include "Game.h"

void DimRakete::Init(Vec2 poz, GameState* stanje)
{
	Cestica::Init(poz,stanje);
	maxZivot=45;
	zivot=maxZivot;
	poz.x+=stanje->DajIgru()->Rand(8,16)-8;
	poz.y+=stanje->DajIgru()->Rand(8,16)-8;
    tex=stanje->GetTM()->DajTexturu("../data/Smoke1Diffuse.tga")->id;
    texN=stanje->GetTM()->DajTexturu("../data/Smoke1Normal.tga")->id;
}
void DimRakete::Update(float deltaT)
{
	Cestica::Update(deltaT);
}
void DimRakete::Render(unsigned char stil)
{
	if(stil==DIFFUSE)// || stil==NORMAL)
	{
		GLuint t;
		if(stil==DIFFUSE)
			t=tex;
		if(stil==NORMAL)
			t=texN;	

		float faktorSkaliranja=0.5+maxZivot/zivot*0.5;
		if(faktorSkaliranja>2)
			faktorSkaliranja=2;

		float faktorBoje=zivot/maxZivot;

		glPushMatrix();
		glTranslatef(poz.x+dim.x/2, poz.y+dim.y/2, 0);	
		glScalef(faktorSkaliranja,faktorSkaliranja,0);
		glTranslatef(-dim.x,-dim.y,0);	

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor3f(faktorBoje,faktorBoje,faktorBoje);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,t);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(dim.x, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(dim.x, dim.y);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, dim.y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);	

		glDisable(GL_BLEND);
		glPopMatrix();	
	
		glColor3f(1.0, 1.0, 1.0);	
	}
}
