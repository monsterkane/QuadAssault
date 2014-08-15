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

#ifndef TRIGGER_H
#define TRIGGER_H
#include "Object.h"
#include "Mob.h"
#include "Message.h"

#define AKTIVIRAN 0
#define DEAKTIVIRAN 1

#define MOB 0
#define PORUKA 1
#define KRAJ 2

class GlavnoStanje;

class Trigger : public Objekt
{
private:
	GlavnoStanje* stanje;
	Mob* mob;
	Vec2 meta;

	Poruka* poruka;	
	
public:
	void InitMob(Vec2 v1, Vec2 v2, Vec2 meta, Mob* mob, GlavnoStanje* stanje);
	void InitPoruka(Vec2 v1, Vec2 v2, Poruka* poruka, GlavnoStanje* stanje);
	void InitKraj(Vec2 v1, Vec2 v2, GlavnoStanje* stanje);
	void Update(float deltaT);
	void Render();

	bool status; //aktiviran ili deaktiviran

	unsigned char tip; //tip triggera (mob, vrata, cinematic)
};

#endif