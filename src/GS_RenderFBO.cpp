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

void GlavnoStanje::RenderSvjetlostNaFBO()
{
	//LIGHTMAPA	
	RenderNormalNaFBO();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, lightmapa, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(ambijentnoSvjetlo.x, ambijentnoSvjetlo.y, ambijentnoSvjetlo.z, 1.0f);
	glLoadIdentity();	
		
	glEnable(GL_BLEND);	
	glBlendFunc(GL_ONE,GL_ONE);

	//RENDERIRA SE SVE GLOW
	glPushMatrix();
		glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);
		RenderGeometrijuGlow();
		RenderObjekte(GLOW);
	glPopMatrix();

	//RENDERIRAJU SE SVJETLA
	for(int i=0; i<svjetla.size(); i++)
	{		
		svjetla[i]->RenderNaFBO(shaderi[0],kamera, normalmapa);	
		if(svjetla[i]->unisteno==true)
		{
			delete svjetla[i];
			svjetla.erase(svjetla.begin()+i);
		}				
	}
	glDisable(GL_BLEND);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GlavnoStanje::RenderNormalNaFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, normalmapa, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();	
    //Sprite(Vec2(0,0),Vec2(igra->DajRW()->getSize().x, igra->DajRW()->getSize().y),mt->DajTexturu(3)->id);
	glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);			
		RenderGeometrijuNormal();		
		RenderObjekte(NORMAL);
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GlavnoStanje::RenderGeometrijuNaFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, geometrija, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();
    //Sprite(Vec2(0,0),Vec2(igra->DajRW()->getSize().x, igra->DajRW()->getSize().y),mt->DajTexturu(1)->id);
	glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);	
		RenderGeometriju();
		RenderObjekte(DIFFUSE);			
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);	
}

void GlavnoStanje::RenderScenu()
{		
	shaderi[1]->Bind();
	
	int geometrijaLoc, lightmapaLoc, ambijentLoc;
		
	glEnable(GL_TEXTURE_2D);
    geometrijaLoc = glGetUniformLocation(shaderi[1]->ID, "geometrija");
	glActiveTextureARB(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, geometrija);
	glUniform1i(geometrijaLoc, 0);	

	lightmapaLoc = glGetUniformLocation(shaderi[1]->ID, "lightmapa");
	glActiveTextureARB(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightmapa);
	glUniform1i(lightmapaLoc, 1);

	ambijentLoc = glGetUniformLocation(shaderi[1]->ID, "ambijent");
	glUniform3f(ambijentLoc, ambijentnoSvjetlo.x, ambijentnoSvjetlo.y, ambijentnoSvjetlo.z);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);

    sf::Vector2u window_size = igra->GetRW()->getSize();
    glTexCoord2f(1.0, 1.0); glVertex2f(window_size.x, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(window_size.x, window_size.y);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, window_size.y);
	glEnd();
	shaderi[1]->UnBind();
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0);	
}
