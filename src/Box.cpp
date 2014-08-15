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

#include "Box.h"

void Sprite(Vec2 pos, Vec2 size, GLuint tex)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0, 0.0); glVertex2f(pos.x+size.x, pos.y);
    glTexCoord2f(1.0, 1.0); glVertex2f(pos.x+size.x, pos.y+size.y);
    glTexCoord2f(0.0, 1.0); glVertex2f(pos.x, pos.y+size.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}
void SpriteT(Vec2 pos, Vec2 size, float rot, GLuint tex)
{
	glPushMatrix();
    glTranslatef(pos.x+size.x/2, pos.y+size.y/2, 0);
	glRotatef(rot,0,0,1);
    glTranslatef(-size.x/2,-size.y/2,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);

    float matrix[16];
    glGetFloatv(GL_MODELVIEW, matrix);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(size.x, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(size.x, size.y);
    glTexCoord2f(0.0, 1.0); glVertex2f(0.0, size.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}

bool Box::Collision(Box* a)
{
	if(v2.x<a->v1.x)return false;
	if(v2.y<a->v1.y)return false;		

	if(v1.x>a->v2.x)return false;
	if(v1.y>a->v2.y)return false;		

	return true;
}
