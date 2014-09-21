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

#ifndef PROJEKTIL_H
#define PROJEKTIL_H
#include "Object.h"
#include "Light.h"

#define IGRAC 0
#define NEPRIJATELJ 1

class GlavnoStanje;

class Projektil : public Objekt
{
protected:
	Vec2 smjer;
	float brzina;

	float domet, domet_timer;

	GlavnoStanje* stanje;
	Svjetlo* svjetlo;

	unsigned char** maps;

	float steta;

public:
	Projektil();
	~Projektil();
	virtual void Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** maps, bool vlasnik);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);
	virtual void Unisti();

	float DajStetu();

	bool unisten;
	bool vlasnik;
};

#endif
