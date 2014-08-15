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

#include "Block.h"
#include "GameState.h"

float Block::water_flow;

void Block::Init(Vec2 poz, unsigned char type, GlavnoStanje* state)
{
    this->pos=poz;
    this->type=type;
	
    size=Vec2(BLOCK_SIZE,BLOCK_SIZE);
    this->state=state;
		
    if(type==EMPTY)
	{
        tex=state->DajMT()->DajTexturu("../data/prazninaDiffuse.tga")->id;
        texN=state->DajMT()->DajTexturu("../data/prazninaNormal.tga")->id;
	}
    if(type==WALL)
	{
        tex=state->DajMT()->DajTexturu("../data/Block.tga")->id;
        texN=state->DajMT()->DajTexturu("../data/zid1Normal.tga")->id;
	}
    if(type==RED_DOOR || type==BLUE_DOOR || type==GREEN_DOOR)
	{
        tex=state->DajMT()->DajTexturu("../data/vrataDiffuse.tga")->id;
        texN=state->DajMT()->DajTexturu("../data/vrataNormal.tga")->id;
        texG=state->DajMT()->DajTexturu("../data/vrataGlow.tga")->id;
	}
    if(type==FLOOR)
	{		
        tex=state->DajMT()->DajTexturu("../data/pod1Diffuse.tga")->id;
        texN=state->DajMT()->DajTexturu("../data/prazninaNormal2.tga")->id;
	}
    water_flow=0.0;
}
void Block::Render()
{	
	glColor3f(1,1,1);	
    Sprite(pos,size,tex);
	glColor3f(1,1,1);	
}
void Block::RenderNormal()
{	
	glColor3f(1,1,1);	
    Sprite(pos,size,texN);
	glColor3f(1,1,1);		
}
void Block::RenderGlow()
{
    if(type!=EMPTY && (type==RED_DOOR || type==BLUE_DOOR || type==GREEN_DOOR) )
	{
		glColor3f(1,1,1);	
        if(type==RED_DOOR)
			glColor3f(1.0, 0.2, 0.2);
        if(type==BLUE_DOOR)
			glColor3f(0.2, 0.2, 1.0);
        if(type==GREEN_DOOR)
			glColor3f(0.2, 1.0, 0.2);
        Sprite(pos,size,texG);
		glColor3f(1,1,1);
	}
}

		
