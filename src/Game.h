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

#ifndef GAME_H
#define GAME_H
#include "Dependencies.h"
#include "State.h"

class Game
{
private:
	sf::RenderWindow rw;		

    GLfloat width, height;

    bool done;

    vector<Stanje*> states;
public:		
    bool Init(char* configFile); // initializes the game, using information from an external config file.
    void Loop(); // takes place every frame, updates current state and renders content
    void Deinit(); // frees memory and exits

	int Rand(int i1, int i2);

    void SetState(Stanje* state, bool destroy);

    sf::RenderWindow* GetRW();
};

#endif
