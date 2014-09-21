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

#ifndef ORUZJE_H
#define ORUZJE_H
#include "Object.h"

class GlavnoStanje;
class Projektil;

class Oruzje : public Objekt
{
protected:
	GLuint tex, texN, texG;
	GlavnoStanje* stanje;

	Vec2 absPoz, smjer;
	unsigned char** maps;
	bool vlasnik;
	
	float punjenje, trenutnoPunjenje;
	float brzinaPunjenja;
	float potrebnaEnergija;
	
public:
	virtual void Init(GlavnoStanje* stanje);
	virtual void Update(float deltaT);	
	virtual void Render();
	virtual void RenderNormal();
	virtual void RenderGlow();
	virtual void Pucaj(Vec2 poz, Vec2 smjer, unsigned char** maps, bool vlasnik);
	virtual void IspaliProjektil(Projektil* p);

	float DajPotrebnuEnergiju();
};

#endif