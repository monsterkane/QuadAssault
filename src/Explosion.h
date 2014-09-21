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

#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Object.h"
#include "Light.h"

class GameState;

class Explosion : public Objekt
{
protected:
	
	float radius;
    Svjetlo* light;

    bool dead; // if you die, the intensity is reduced, if not, then increases

    float growthRate; // the speed at which the intensity is increasing
    float deathRate; // the speed at which the intensity is decreasing
    float intensity, maxIntensity;

    Vec3 color; // light color

    GameState* state;

public:
    Explosion();
    ~Explosion();
    void Init(Vec2 pos, float radius, GameState* state);
    void Setup(float intensity, float growthRate, float deathRate);
    void SetColor(Vec3 color);
	void Update(float deltaT);
	void Render();	

    bool destroyed;
};

#endif
