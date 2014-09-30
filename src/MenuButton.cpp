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

#include "MenuButton.h"
#include "MenuState.h"
#include "Game.h"
#include "Box.h"

void MenuGumb::Init(Vec2 p, Vec2 d, string text, sf::Font font, bool omogucen, MenuStanje* stanje)
{
	this->pos=p;
	this->dim=d;
	this->text=text;
	this->stanje=stanje;
	this->font=font;
	this->omogucen=omogucen;

	stanje->DajIgru()->GetRW()->pushGLStates();	
    t.setFont(this->font);
	if(omogucen==true)
        t.setColor(sf::Color(50,255,50));
	else
        t.setColor(sf::Color(150,150,150));
    t.setCharacterSize(30);
    t.setString(text);
    t.setPosition(pos.x+dim.x/2-t.getLocalBounds().width/2 , pos.y+dim.y/2-t.getLocalBounds().height/2 );
	stanje->DajIgru()->GetRW()->popGLStates();
}
void MenuGumb::Update(float deltaT)
{
	if(omogucen==true)
	{
		Vec2 mis=stanje->DajMis();	
		if(mis.x>=pos.x && mis.x<pos.x+dim.x
			&& mis.y>=pos.y && mis.y<pos.y+dim.y)	
			odabran=true;	
		else
			odabran=false;
	}
}
void MenuGumb::Render(sf::Font font)
{	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	if(omogucen==true)
	{
		if(odabran==true)
			glColor3f(0.0, 0.5, 0.0);
		else
			glColor3f(0.0, 0.25, 0.0);
	}
	else
	{
		glColor3f(0.05, 0.05, 0.05);
	}

	glBegin(GL_QUADS);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y+dim.y);
	glVertex2f(pos.x, pos.y+dim.y);
	glEnd();

	if(omogucen==true)
	{
		if(odabran==true)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.5, 0.0);
	}
	else
	{
		glColor3f(0.1, 0.1, 0.1);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y+dim.y);
	glVertex2f(pos.x, pos.y+dim.y);
	glEnd();	

	glColor3f(1.0, 1.0, 1.0);

	stanje->DajIgru()->GetRW()->pushGLStates();	
    stanje->DajIgru()->GetRW()->draw(t);
	stanje->DajIgru()->GetRW()->popGLStates();

	glDisable(GL_BLEND);
}
