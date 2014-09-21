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

#ifndef BLOCK_H
#define BLOCK_H
#include "Box.h"

#define MX 128
#define MY 128
#define BLOCK_SIZE 64

enum BlockType
{
    FLOOR, WALL, EMPTY, RED_DOOR, BLUE_DOOR, GREEN_DOOR
};

struct Side
{
	Vec2 v1,v2;
    Vec2 normal;
};

class GameState;

class Block
{
private:
    Vec2 pos;
    Vec2 size;
    unsigned char type;
    GameState* state;

    vector<Side> sides;
	GLuint tex, texN, texG;

    static float water_flow;
public:
    void Init(Vec2 pos, unsigned char type, GameState* state);

	void Render();	
	void RenderNormal();
	void RenderGlow();
};
#endif
