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

#ifndef VEC2_H
#define VEC2_H
#include "Dependencies.h"

class Vec2
{
public:
	float x,y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();

	Vec2 operator+ (Vec2 drugi);		
	Vec2 operator- (Vec2 drugi);
	void Mnozi(float faktor);
	void Normaliziraj();
	float Duljina();
};

class Vec3
{
public:
	float x,y,z;

	Vec3();
	Vec3(float x, float y, float z);
	~Vec3();
};

#endif
