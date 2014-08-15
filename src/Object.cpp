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

#include "Object.h"

Vec2 Objekt::DajPoz()
{
	return poz;
}
void Objekt::PromijeniPoz(Vec2 poz)
{
	this->poz=poz;
}
Vec2 Objekt::DajDim()
{
	return dim;
}
Vec2 Objekt::DajSredinu()
{
	return poz+Vec2(dim.x/2,dim.y/2);
}
void Objekt::PromijeniDim(Vec2 dim)
{
	this->dim=dim;
}
Objekt::Objekt()
{
}
Objekt::~Objekt()
{		
}