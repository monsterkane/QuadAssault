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

#include "Vec2.h"

Vec2::Vec2()
{
}
Vec2::Vec2(float x, float y)
{
	this->x=x;
	this->y=y;
}
Vec2::~Vec2()
{
}

Vec3::Vec3()
{
}
Vec3::Vec3(float x, float y, float z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
Vec3::~Vec3()
{
}

Vec2 Vec2::operator+ (Vec2 drugi)
{
	return Vec2(x+drugi.x,y+drugi.y);
}
Vec2 Vec2::operator- (Vec2 drugi)
{
	return Vec2(x-drugi.x,y-drugi.y);
}
void Vec2::Mnozi(float faktor)
{
	x*=faktor;
	y*=faktor;	
}
void Vec2::Normaliziraj()
{
	float d=(float)sqrt(x*x+y*y);
	if(d==0)
		d=1.0;
	x/=d;			
	y/=d;				
}
float Vec2::Duljina()
{
	return (float)sqrt(x*x+y*y);
}
