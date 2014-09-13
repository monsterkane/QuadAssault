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

#ifndef CESTICA_H
#define CESTICA_H
#include "Object.h"

class GameState;

class Cestica : public Objekt
{
protected:
	GLuint tex, texN;	
	GameState* stanje;

	float zivot; //smanjuje se postepeno	
	float maxZivot; //za rendering
public:
	virtual void Init(Vec2 poz, GameState* stanje);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);

	bool unisten; //ako je true, uklanja se iz igre
};

#endif
