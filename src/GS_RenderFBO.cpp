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

#include "GameState.h"

void GameState::RenderLightOnFBO()
{
    /* lightmap */
    RenderNormalOnFBO();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, lightmap, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(ambientLight.x, ambientLight.y, ambientLight.z, 1.0f);
	glLoadIdentity();	
		
	glEnable(GL_BLEND);	
	glBlendFunc(GL_ONE,GL_ONE);

    /* glow */
	glPushMatrix();
		glTranslatef(-camera->DajPoz().x, -camera->DajPoz().y, 0);
        RenderGeometryGlow();
        RenderObjects(GLOW);
	glPopMatrix();

    /* light */
	for(int i=0; i<lights.size(); i++)
	{		
		lights[i]->RenderNaFBO(shaders[0],camera, normalmap);	
		if(lights[i]->unisteno==true)
		{
			delete lights[i];
			lights.erase(lights.begin()+i);
		}				
	}
	glDisable(GL_BLEND);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GameState::RenderNormalOnFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, normalmap, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();	
    //Sprite(Vec2(0,0),Vec2(igra->DajRW()->getSize().x, igra->DajRW()->getSize().y),mt->DajTexturu(3)->id);
	glTranslatef(-camera->DajPoz().x, -camera->DajPoz().y, 0);			
        RenderGeometryNormal();
        RenderObjects(NORMAL);
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GameState::RenderGeometryOnFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, geometry, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();
    //Sprite(Vec2(0,0),Vec2(igra->DajRW()->getSize().x, igra->DajRW()->getSize().y),mt->DajTexturu(1)->id);
	glTranslatef(-camera->DajPoz().x, -camera->DajPoz().y, 0);	
        RenderGeometry();
        RenderObjects(DIFFUSE);
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);	
}

void GameState::RenderScene()
{		
	shaders[1]->Bind();
	
    int geometryLoc, lightmapLoc, ambientLoc;
		
	glEnable(GL_TEXTURE_2D);
    geometryLoc = glGetUniformLocation(shaders[1]->ID, "geometry");
	glActiveTextureARB(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, geometry);
    glUniform1i(geometryLoc, 0);

    lightmapLoc = glGetUniformLocation(shaders[1]->ID, "lightmaps");
	glActiveTextureARB(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightmap);
    glUniform1i(lightmapLoc, 1);

    ambientLoc = glGetUniformLocation(shaders[1]->ID, "environment");
    glUniform3f(ambientLoc, ambientLight.x, ambientLight.y, ambientLight.z);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);

    sf::Vector2u window_size = igra->GetRW()->getSize();
    glTexCoord2f(1.0, 1.0); glVertex2f(window_size.x, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(window_size.x, window_size.y);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, window_size.y);
	glEnd();
	shaders[1]->UnBind();
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0);	
}
