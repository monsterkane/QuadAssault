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

#include "UI_Menager.h"

UI_Menager::UI_Menager()
{
}
UI_Menager::~UI_Menager()
{	
	for(int i=0; i<prozori.size(); i++)
		delete prozori[i];
	prozori.clear();
}
void UI_Menager::Init(ManagerTextura* mt, Game* igra)
{
	this->mt=mt;
	this->igra=igra;	
}
void UI_Menager::Update(float deltaT, Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->Update(deltaT, mis);
}
void UI_Menager::Render()
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->Render();
}

ManagerTextura* UI_Menager::DajMT()
{
	return mt;
}

void UI_Menager::DodajProzor(UI_Prozor* p)
{
	prozori.push_back(p);
}
vector<UI_Prozor*> UI_Menager::DajProzore()
{
	return prozori;
}

void UI_Menager::LijeviKlik(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->LijeviKlik(mis);
}
void UI_Menager::LijeviOtpust(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->LijeviOtpust(mis);
}
void UI_Menager::DesniKlik(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->DesniKlik(mis);
}
void UI_Menager::DesniOtpust(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->DesniOtpust(mis);
}