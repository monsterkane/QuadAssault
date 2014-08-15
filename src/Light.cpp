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

#include "Light.h"
#include "Game.h"
#include "State.h"
#include "GameState.h"

Svjetlo::Svjetlo()
{
}
Svjetlo::~Svjetlo()
{	
}

void Svjetlo::Init(Vec2 poz, float radius, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->radius=radius;
	this->stanje=stanje;

	this->smjer=Vec2(0.0, 0.0);
	this->kut=0.0;

	unisteno=false;	
}
void Svjetlo::Postavke(Vec3 boja, float intenzitet)
{
	this->boja=boja;
	this->intenzitet=intenzitet;
}
void Svjetlo::PostavkeKuta(Vec2 smjer, float kut)
{
	this->smjer=smjer;
	this->kut=kut;
}
void Svjetlo::PostaviExplozija(bool explozija)
{
	this->explozija = explozija;
}
void Svjetlo::Update(float deltaT)
{
}
void Svjetlo::RenderNaFBO(Shader* s, Objekt* kamera, GLuint normalmapa)
{
	if(poz.x+radius>kamera->DajPoz().x && 
        poz.x-radius<kamera->DajPoz().x+stanje->DajIgru()->GetRW()->getSize().x
		&& poz.y+radius>kamera->DajPoz().y && 
        poz.y-radius<kamera->DajPoz().y+stanje->DajIgru()->GetRW()->getSize().y)
	{
		s->Bind();

		glColor3f(1,1,1);		
		
		float lightX, lightY, lightZ;		
	
		lightX=poz.x-kamera->DajPoz().x;
		lightY=poz.y-kamera->DajPoz().y;
		
		int svjetloLoc = glGetUniformLocation(s->ID, "pozSvjetla");
		glUniform2f(svjetloLoc, lightX, lightY);

		int bojaSvjetlaLoc = glGetUniformLocation(s->ID, "bojaSvjetla");
		glUniform3f(bojaSvjetlaLoc, boja.x, boja.y, boja.z);		

		int smjerLoc = glGetUniformLocation(s->ID, "smjer");
		glUniform2f(smjerLoc, smjer.x, smjer.y);	

		int kutLoc = glGetUniformLocation(s->ID, "kut");
		glUniform1f(kutLoc, kut);	

		int visinaZaslonaLoc = glGetUniformLocation(s->ID, "visinaZaslona");
        glUniform1f(visinaZaslonaLoc,stanje->DajIgru()->GetRW()->getSize().y);

		int radiusLoc = glGetUniformLocation(s->ID, "radius");
		glUniform1f(radiusLoc,radius);

		int intenzitetSvjetla = glGetUniformLocation(s->ID, "intenzitet");
		glUniform1f(intenzitetSvjetla,intenzitet);	

		int jeExplozija = glGetUniformLocation(s->ID, "jeExplozija");
		if(explozija==true)
			glUniform1i(jeExplozija,1);	
		else
			glUniform1i(jeExplozija,0);

		int normalmapaLoc = glGetUniformLocation(s->ID, "nMapa");
		glActiveTextureARB(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, normalmapa);
		glUniform1i(normalmapaLoc, 0);		
			
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(stanje->DajIgru()->GetRW()->getSize().x, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(stanje->DajIgru()->GetRW()->getSize().x, stanje->DajIgru()->GetRW()->getSize().y);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0, stanje->DajIgru()->GetRW()->getSize().y);
		glEnd();	

		s->UnBind();	

		glActiveTextureARB(GL_TEXTURE0);
	}
}
void Svjetlo::Unisti()
{
	unisteno=true;
}
