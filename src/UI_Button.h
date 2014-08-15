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

#ifndef UI_GUMB
#define UI_GUMB
#include "UI_Element.h"

class ManagerTextura;

class UI_Gumb : public UI_Element
{
private:
	void (*funkcija)();

	GLuint tex;
public:
	void Init(UI_Prozor* prozor, Vec2 poz, Vec2 dim, void (*funkcija)(), GLuint tex);
	void Update(float deltaT);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);
};

#endif