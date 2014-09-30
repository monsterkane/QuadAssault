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

#ifndef WEAPON_H
#define WEAPON_H
#include "Object.h"

class GameState;
class Projektil;

class Weapon : public Objekt
{
protected:
	GLuint tex, texN, texG;
    GameState* state;

    Vec2 absPos, direction;
    unsigned char** map;
    bool owner;
	
    float charging, currentCharging;
    float chargingSpeed;
    float requiredEnergy;
	
public:
    virtual void Init(GameState* state);
	virtual void Update(float deltaT);	
	virtual void Render();
	virtual void RenderNormal();
	virtual void RenderGlow();
    virtual void Fire(Vec2 pos, Vec2 direction, unsigned char** map, bool owner);
    virtual void FireProjectile(Projektil* p);

    float GetRequiredEnergy();
};

#endif
