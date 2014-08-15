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

#ifndef MT_H
#define MT_H
#include "Dependencies.h"

struct Textura
{
	Textura();
	Textura(char* file, GLuint id);
	~Textura();

	char* file;
	GLuint id;				
};

class ManagerTextura
{
private:
	vector<Textura> texture;
public:
	ManagerTextura();		
	~ManagerTextura();		

	vector<Textura>* DajTexture();		

	Textura* DajTexturu(int i);		
	Textura* DajTexturu(char* name);		

	void BrisiTexturu(int i);		
	void BrisiTexturu(char* name);

	bool UcitajTexturu(char* name);
	void Brisi();
};

#endif