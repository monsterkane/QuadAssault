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

#ifndef UI_MENAGER_H
#define UI_MENAGER_H
#include "Dependencies.h"
#include "TextureManager.h"
#include "Game.h"
#include "UI_Window.h"

class UI_Menager
{
private:
	ManagerTextura* mt;
	Game* igra;
	
	vector<UI_Prozor*> prozori;
public:
	UI_Menager();
	~UI_Menager();
	void Init(ManagerTextura* mt, Game* igra);
	void Update(float deltaT, Vec2 mis);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);

	void DodajProzor(UI_Prozor* p);
	vector<UI_Prozor*> DajProzore();

	ManagerTextura* DajMT();
};

#endif
