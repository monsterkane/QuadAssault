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

#ifndef SP_H
#define SP_H
#include "Thing.h"
#include "TrashParticle.h"
#include "Light.h"

class SmecePickup : public Stvar
{
protected:	
	Vec2 smjer;
	float brzina;

	float cesticaTimer; //dok dosegne 0, spawna cesticu

	Svjetlo* s;

public:
	void Init(Vec2 poz, GameState* stanje);
	void Update(float deltaT);
	bool ProvjeraSudara();
	void Render(unsigned char stil);
	void Unisti();
	void Pokupi(Igrac* igrac);
};

#endif
