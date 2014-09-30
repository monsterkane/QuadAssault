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

#include "Weapon.h"
#include "GameState.h"
#include "Projectile.h"

void Weapon::Init(GameState* state)
{	
    this->state=state;
    pos.x=0;
    pos.y=0;
	dim.x=16;
	dim.y=32;

    charging=100;
    currentCharging=charging;
    chargingSpeed=250;
    requiredEnergy=1;
}

void Weapon::Update(float deltaT)
{	
    if(currentCharging<charging)
	{
        currentCharging+=chargingSpeed*deltaT;
	}
	else
	{
        currentCharging=charging;
	}
}
void Weapon::Fire(Vec2 pos, Vec2 direction, unsigned char** map, bool owner)
{
    this->absPos=pos;
    this->direction=direction;
    this->map=map;
    this->owner=owner;
}
void Weapon::FireProjectile(Projektil* p)
{
    state->GetProjectile(p);
    p->Init(absPos, direction, state, map, owner);
    state->GetPlayer()->OduzmiEnergiju(requiredEnergy);
}
void Weapon::Render()
{
    float o=currentCharging/charging*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void Weapon::RenderNormal()
{
    float o=currentCharging/charging*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texN);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void Weapon::RenderGlow()
{
    float o=currentCharging/charging*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texG);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
float Weapon::GetRequiredEnergy()
{
    return requiredEnergy;
}
