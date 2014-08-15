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

#ifndef MOB_H
#define MOB_H
#include "Object.h"
#include "Block.h"

class GlavnoStanje;
class Projektil;

class Mob : public Objekt
{
protected:			
	float akceleracija;	
	float rotacija;	
	GlavnoStanje* stanje;
	unsigned char** mapa;
	float punjenje;

	//NASLIJED:
	float brzina;
	float maxbrzina;
	GLuint textura, texturaN, texturaG;	
	short hp;
	float brzinaPunjenja;
	float domet;

public:
	
	virtual void Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa);
	virtual void SpawnEfekt();
	virtual void Update(float deltaT);
	virtual void Pucanje(Projektil* p, float deltaT);

	virtual void Render(unsigned char stil);	

	virtual void PrimiStetu(Projektil* p);
	virtual void Unisti();

	void DodajMoment(float x);
	void Rotiraj(float rot);	

	bool ProvjeraSudara();
	void SudarProjektila();	

	bool unisten;
};
#endif