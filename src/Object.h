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

#ifndef OBJEKT_H
#define OBJEKT_H
#include "Vec2.h"
#include "Dependencies.h"

#define DIFFUSE 0
#define NORMAL 1
#define GLOW 2

class Objekt
{
protected:
	Vec2 poz,dim;	
public:
	Objekt();
	~Objekt();
	Vec2 DajPoz(); //daje poziciju objekta
	Vec2 DajDim();
	Vec2 DajSredinu();
	virtual void PromijeniPoz(Vec2 poz); //mijenja poziciju objekta
	virtual void PromijeniDim(Vec2 dim);
};

#endif

