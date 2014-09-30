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

#ifndef UI_PROZOR
#define UI_PROZOR
#include "Dependencies.h"
#include "Object.h"
#include "UI_Element.h"

class UI_Menager;

class UI_Prozor : public Objekt
{
private:
	UI_Menager* manager;

	string naziv;

	vector<UI_Element*> elementi;

	bool podignut;
	Vec2 misPrije;
public:
	UI_Prozor();
	~UI_Prozor();
	void Init(UI_Menager* manager, Vec2 pos, Vec2 dim, string naziv);
	void Update(float deltaT, Vec2 mis);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);

	void DodajElement(UI_Element* e);
	vector<UI_Element*> DajElemente();

	UI_Menager* DajMenagera();
};

#endif