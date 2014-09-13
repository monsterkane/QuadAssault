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

#include "Message.h"
#include "GameState.h"
#include "Game.h"

void Poruka::Init(string posiljatelj, string sadrzaj, float trajanje, string zvuk, GameState* stanje)
{	
	this->trajanje=trajanje;
	this->stanje=stanje;
	timer=0.0;
	unisten=false;

	this->poz.x=64;
	this->poz.y=64;
		
    stanje->DajIgru()->GetRW()->pushGLStates();
    p_text.setString(posiljatelj);
    p_text.setPosition(poz.x+48, poz.y+4);
    p_text.setFont(stanje->GetFonts()->at(0));
    p_text.setCharacterSize(24);
    p_text.setColor(sf::Color(25,255,25));

    text.setString(sadrzaj);
    text.setPosition(poz.x+48, poz.y+4+24);
    text.setFont(stanje->GetFonts()->at(0));
    text.setCharacterSize(24);
    text.setColor(sf::Color(255,255,255));
    stanje->DajIgru()->GetRW()->popGLStates();

	this->zvuk=zvuk;
	SvirajZvuk=true;	

    portret=stanje->GetTM()->DajTexturu("../data/portret2.tga")->id;
}
void Poruka::Update(float deltaT)
{
	if(timer<trajanje)
		timer+=deltaT;
	else
	{
		if(z!=NULL)
            z->stop();
		unisten=true;		
		z=NULL;
	}
	if(SvirajZvuk==true)
	{
		z = stanje->GetSound(new sf::Sound(),
			stanje->GetSM()->DajZvuk((char*)zvuk.c_str()));			
        z->play();
		
		SvirajZvuk=false;
	}
	
}
void Poruka::RenderOkvir()
{
    stanje->DajIgru()->GetRW()->pushGLStates();
    float sirina=text.getLocalBounds().width;
    stanje->DajIgru()->GetRW()->popGLStates();

	glColor3f(0.0, 0.25, 0.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);		
	glBegin(GL_QUADS); //PUNI KVADRAT PO CIJELOM
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x+32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x+32+sirina+48,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x+32+sirina+48,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x+32,poz.y+64);
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1.0, 1.0, 1.0);	

	glEnable(GL_TEXTURE_2D);//PORTRET
	glBindTexture(GL_TEXTURE_2D, portret);
	glBegin(GL_QUADS); 
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x-32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x+32,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x+32,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x-32,poz.y+64);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.1, 1.0, 0.1);	

	glBegin(GL_LINE_LOOP); //ZELENI OBRUB
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x-32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x-32+sirina+112,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x-32+sirina+112,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x-32,poz.y+64);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);	
}
void Poruka::Render()
{		
    stanje->DajIgru()->GetRW()->pushGLStates();
    stanje->DajIgru()->GetRW()->draw(p_text);
    stanje->DajIgru()->GetRW()->draw(text);
    stanje->DajIgru()->GetRW()->popGLStates();
}
