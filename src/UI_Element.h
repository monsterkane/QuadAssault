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

#ifndef UI_ELEMENT
#define UI_ELEMENT
#include "Dependencies.h"
#include "Object.h"

class UI_Menager;
class UI_Prozor;

class UI_Element : public Objekt
{
protected:
	UI_Prozor* prozor;

	bool odabran; //je li kliknut
public:
	virtual void Init(UI_Prozor* prozor, Vec2 pos);
	virtual void Update(float deltaT);
	virtual void Render();

	virtual void LijeviKlik(Vec2 mis);
	virtual void LijeviOtpust(Vec2 mis);
	virtual void DesniKlik(Vec2 mis);	
	virtual void DesniOtpust(Vec2 mis);
};

#endif