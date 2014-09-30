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

#include "Player.h"
#include "Box.h"
#include "GameState.h"
#include "Laser.h"
#include "Plasma.h"
#include "Light.h"

void Igrac::Render(unsigned char stil)
{		
	if(unisten==false)
	{
		if(stil==DIFFUSE) //SJENA
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
			glTranslatef(4,4,0);
			glColor4f(0.0, 0.0, 0.0, 0.5);	
			RenderPodlogu(stil);
			RenderTracnice(stil);
			RenderTorzo(stil);	
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glPopMatrix();
			glDisable(GL_BLEND);
		}

		if(stil==DIFFUSE || stil==NORMAL)
		{
			glColor3f(1.0, 1.0, 1.0);	
			RenderPodlogu(stil);
			RenderTracnice(stil);
			RenderTorzo(stil);	
			glColor3f(1.0, 1.0, 1.0);
		}	

		for(int i=0; i<4; i++)
			if(oruzjeSlot[i]==true)
				RenderOruzje(oruzja[i]->DajPoz().x, oruzja[i]->DajPoz().y, oruzja[i], stil);
	}
}
void Igrac::RenderPodlogu(unsigned char stil)
{
	GLuint tex;
	if(stil==DIFFUSE)
		tex=podloga_tex;
	if(stil==NORMAL)
		tex=podloga_normal;

	glPushMatrix();	
	SpriteT(pos,dim,rotacija,tex);	
	glPopMatrix();
}
void Igrac::RenderTorzo(unsigned char stil)
{
	GLuint tex;	
	if(stil==DIFFUSE)
		tex=textura;	
	if(stil==NORMAL)
		tex = texturaN;	
	glPushMatrix();	
	SpriteT(pos,dim,rotacijaTorza+90,tex);			
	glPopMatrix();	
}
void Igrac::RenderTracnice(unsigned char stil)
{
	float razmak_tracnica=8;
	float odmak=24;

	GLuint tex;
	if(stil==DIFFUSE)
		tex=tracnica_tex;
	if(stil==NORMAL)
		tex=tracnica_normal;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);

	glPushMatrix();
	glTranslatef(DajSredinu().x, DajSredinu().y,0);
	glRotatef(rotacija,0,0,1);
	glTranslatef(-odmak-razmak_tracnica, -dim.y/2,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, pomak_tracnica); glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, pomak_tracnica); glVertex2f(dim.x/4, 0.0);
	glTexCoord2f(1.0, pomak_tracnica+1.0); glVertex2f(dim.x/4, dim.y);	
	glTexCoord2f(0.0, pomak_tracnica+1.0); glVertex2f(0.0, dim.y);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);

	glPushMatrix();
	glTranslatef(DajSredinu().x, DajSredinu().y,0);
	glRotatef(rotacija,0,0,1);
	glTranslatef(odmak-razmak_tracnica, -dim.y/2,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, pomak_tracnica); glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, pomak_tracnica); glVertex2f(dim.x/4, 0.0);
	glTexCoord2f(1.0, pomak_tracnica+1.0); glVertex2f(dim.x/4, dim.y);	
	glTexCoord2f(0.0, pomak_tracnica+1.0); glVertex2f(0.0, dim.y);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
void Igrac::RenderOruzje(float x, float y, Weapon* oruzje, unsigned char stil)
{
	glPushMatrix();
	glTranslatef(DajSredinu().x,DajSredinu().y,0);
	glRotatef(rotacijaTorza+90,0,0,1);
	glTranslatef(x,y,0);
	if(stil==DIFFUSE)
		oruzje->Render();
	if(stil==NORMAL)
		oruzje->RenderNormal();
	if(stil==GLOW)
		oruzje->RenderGlow();
	glPopMatrix();
}
void Igrac::RenderHP_Bar()
{
	float faktor=2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);	
	
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.5, 0.0); glVertex2f(0.0, 0.0);
	glColor3f(0.0, 0.5, 0.0); glVertex2f(hp*faktor, 0.0);
	glColor3f(0.0, 0.1, 0.0); glVertex2f(hp*faktor, 16.0);
	glColor3f(0.0, 0.1, 0.0); glVertex2f(0.0, 16.0);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.75, 0.0); glVertex2f(0.0, 0.0);
	glColor3f(0.0, 0.75, 0.0); glVertex2f(100*faktor, 0.0);
	glColor3f(0.0, 0.25, 0.0); glVertex2f(100*faktor, 16.0);
	glColor3f(0.0, 0.25, 0.0); glVertex2f(0.0, 16.0);
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1.0, 1.0, 1.0);
}
void Igrac::RenderEnergija_Bar()
{
	float faktor=2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);	
	
	if(energija>=0.0)			
	{
		glBegin(GL_QUADS);
		glColor3f(0.2, 0.2, 0.5); glVertex2f(0.0, 0.0);
		glColor3f(0.2, 0.2, 0.5); glVertex2f(energija*faktor, 0.0);
		glColor3f(0.05, 0.05, 0.1); glVertex2f(energija*faktor, 16.0);
		glColor3f(0.05, 0.05, 0.1); glVertex2f(0.0, 16.0);
		glEnd();	
	}

	glBegin(GL_LINE_LOOP);
	glColor3f(0.2, 0.3, 0.75); glVertex2f(0.0, 0.0);
	glColor3f(0.2, 0.3, 0.75); glVertex2f(100*faktor, 0.0);
	glColor3f(0.1, 0.1, 0.25); glVertex2f(100*faktor, 16.0);
	glColor3f(0.1, 0.1, 0.25); glVertex2f(0.0, 16.0);
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1.0, 1.0, 1.0);
}
