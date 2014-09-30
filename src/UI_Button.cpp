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

#include "UI_Button.h"
#include "UI_Window.h"
#include "UI_Menager.h"
#include "Box.h"

void UI_Gumb::Init(UI_Prozor* prozor, Vec2 poz, Vec2 dim, void (*funkcija)(), GLuint tex)
{
	UI_Element::Init(prozor,poz);
	this->funkcija=funkcija;	
	this->dim=dim;
	this->tex=tex;
}
void UI_Gumb::Update(float deltaT)
{	
}
void UI_Gumb::Render()
{		
	if(odabran==true)
		glColor3f(0.25, 0.25, 0.25);
	else
		glColor3f(1.0, 1.0, 1.0);
	Sprite(prozor->DajPoz()+pos,dim,tex);
	glColor3f(1.0, 1.0, 1.0);
}

void UI_Gumb::LijeviKlik(Vec2 mis)
{	
	if(mis.x>=prozor->DajPoz().x+pos.x && mis.y>=prozor->DajPoz().y+pos.y
		&& mis.y<prozor->DajPoz().y+pos.y+dim.y && mis.x<prozor->DajPoz().x+pos.x+dim.x)
		odabran=true;
}
void UI_Gumb::LijeviOtpust(Vec2 mis)
{	
	odabran=false;
	if(mis.x>=prozor->DajPoz().x+pos.x && mis.y>=prozor->DajPoz().y+pos.y
		&& mis.y<prozor->DajPoz().y+pos.y+dim.y && mis.x<prozor->DajPoz().x+pos.x+dim.x)
	(*funkcija)();
}
void UI_Gumb::DesniKlik(Vec2 mis)
{
}
void UI_Gumb::DesniOtpust(Vec2 mis)
{
}
