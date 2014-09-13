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

#ifndef PORUKA_H
#define PORUKA_H
#include "Dependencies.h"
#include "Object.h"

class GameState;

class Poruka : public Objekt
{
private:
    sf::Text p_text;
    sf::Text text;
	float trajanje; //trajanje poruke u sekundama
	float timer; //pocinje od nule	

	GLuint portret;

	string zvuk;	

	bool SvirajZvuk;

	sf::Sound* z;

	GameState* stanje;
public:
	void Init(string posiljatelj, string sadrzaj, float trajanje, string zvuk, GameState* stanje);
	void Update(float deltaT);
	void RenderOkvir();
	void Render();
	bool unisten;
};

#endif
