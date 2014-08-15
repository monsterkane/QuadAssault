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

void Oruzje::Init(GlavnoStanje* stanje)
{	
	this->stanje=stanje;
	poz.x=0;
	poz.y=0;
	dim.x=16;
	dim.y=32;

	punjenje=100;
	trenutnoPunjenje=punjenje;
	brzinaPunjenja=250;	
	potrebnaEnergija=1;
}

void Oruzje::Update(float deltaT)
{	
	if(trenutnoPunjenje<punjenje)
	{
		trenutnoPunjenje+=brzinaPunjenja*deltaT;
	}
	else
	{
		trenutnoPunjenje=punjenje;
	}
}
void Oruzje::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	this->absPoz=poz;
	this->smjer=smjer;
	this->mapa=mapa;
	this->vlasnik=vlasnik;	
}
void Oruzje::IspaliProjektil(Projektil* p)
{
	stanje->DodajProjektil(p);
	p->Init(absPoz,smjer,stanje,mapa,vlasnik);	
	stanje->DajIgraca()->OduzmiEnergiju(potrebnaEnergija);
}
void Oruzje::Render()
{
	float o=trenutnoPunjenje/punjenje*8;
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
void Oruzje::RenderNormal()
{
	float o=trenutnoPunjenje/punjenje*8;
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
void Oruzje::RenderGlow()
{
	float o=trenutnoPunjenje/punjenje*8;
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
float Oruzje::DajPotrebnuEnergiju()
{
	return potrebnaEnergija;
}