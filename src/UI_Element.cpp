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

#include "UI_Element.h"
#include "UI_Window.h"

void UI_Element::Init(UI_Prozor* prozor, Vec2 poz)
{
	this->prozor=prozor;
	this->pos=poz;
	odabran=false;
}
void UI_Element::Update(float deltaT)
{	
}
void UI_Element::Render()
{	
}

void UI_Element::LijeviKlik(Vec2 mis)
{
}
void UI_Element::LijeviOtpust(Vec2 mis)
{
}
void UI_Element::DesniKlik(Vec2 mis)
{
}
void UI_Element::DesniOtpust(Vec2 mis)
{
}