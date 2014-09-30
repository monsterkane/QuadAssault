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

#include "UI_Window.h"
#include "UI_Menager.h"

UI_Prozor::UI_Prozor()
{
}
UI_Prozor::~UI_Prozor()
{
	for(int i=0; i<elementi.size(); i++)
		delete elementi[i];
	elementi.clear();
}
void UI_Prozor::Init(UI_Menager* m, Vec2 poz, Vec2 dim, string naziv)
{
	this->manager=manager;
	this->pos=poz;
	this->dim=dim;
	this->naziv=naziv;
}
void UI_Prozor::Update(float deltaT, Vec2 mis)
{
	if(podignut==true)
	{
		pos.x+=mis.x-misPrije.x;
		pos.y+=mis.y-misPrije.y;
		misPrije=mis;
	}
	for(int i=0; i<elementi.size(); i++)
		elementi[i]->Update(deltaT);
}
void UI_Prozor::Render()
{
	//TIJELO PROZORA
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glColor3f(0.0, 0.25, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y);
	glVertex2f(pos.x+dim.x, pos.y+dim.y);
	glVertex2f(pos.x, pos.y+dim.y);
	glEnd();
	glDisable(GL_BLEND);

	//NASLOVNICA (TRAKA)
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0); glVertex2f(pos.x, pos.y);
	glColor3f(0.0, 1.0, 0.0); glVertex2f(pos.x+dim.x, pos.y);
	glColor3f(0.0, 0.0, 0.0); glVertex2f(pos.x+dim.x, pos.y+16);
	glColor3f(0.0, 0.0, 0.0); glVertex2f(pos.x, pos.y+16);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);

	for(int i=0; i<elementi.size(); i++)
		elementi[i]->Render();
}

void UI_Prozor::LijeviKlik(Vec2 mis)
{
	if(mis.x>=pos.x && mis.y>=pos.y
		&& mis.y<pos.y+16 && mis.x<pos.x+dim.x)
	{
			podignut=true;
			misPrije=mis;
	}
	for(int i=0; i<elementi.size(); i++)
		elementi[i]->LijeviKlik(mis);
}
void UI_Prozor::LijeviOtpust(Vec2 mis)
{
	podignut=false;
	for(int i=0; i<elementi.size(); i++)
		elementi[i]->LijeviOtpust(mis);
}
void UI_Prozor::DesniKlik(Vec2 mis)
{
	for(int i=0; i<elementi.size(); i++)
		elementi[i]->DesniKlik(mis);
}
void UI_Prozor::DesniOtpust(Vec2 mis)
{
	for(int i=0; i<elementi.size(); i++)
		elementi[i]->DesniOtpust(mis);
}

void UI_Prozor::DodajElement(UI_Element* e)
{
	elementi.push_back(e);
}
vector<UI_Element*> UI_Prozor::DajElemente()
{
	return elementi;
}

UI_Menager* UI_Prozor::DajMenagera()
{
	return manager;
}