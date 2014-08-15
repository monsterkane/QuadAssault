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

#ifndef STANJE_H
#define STANJE_H
#include "Dependencies.h"

class Game;

class Stanje
{
protected:
	bool gotovo;	

	sf::Event event;

	Game* igra;		
	
public:		
	virtual bool Init(Game* igra)=0;	
	virtual void Input()=0;
	virtual void Update(float deltaT)=0;	
	virtual void Render()=0;
	virtual void Izlaz()=0;		

	bool Gotovo();
	Game* DajIgru();

	bool PrviUpdate;
};

#endif
