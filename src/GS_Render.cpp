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
#include "SharedVariables.h"

void GameState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();

	RenderLightOnFBO();	
	RenderGeometryOnFBO();	

	RenderScene();	
	
	if(messages.size()!=0)
		messages[0]->RenderOkvir();
	if(messages.size()!=0)
		messages[0]->Render();	

	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Sprite(mousePos-Vec2(16,16),Vec2(32,32),textureManager->DajTexturu(0)->id);
	glDisable(GL_BLEND);

	glPushMatrix();
    glTranslatef(32, igra->GetRW()->getSize().y-32, 0);
	player->RenderHP_Bar();
	glPopMatrix();	

	glPushMatrix();
    glTranslatef(igra->GetRW()->getSize().x-232, igra->GetRW()->getSize().y-32, 0);
	player->RenderEnergija_Bar();
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(transition_color, transition_color, transition_color);
    Sprite(Vec2(0.0, 0.0), Vec2(igra->GetRW()->getSize().x, igra->GetRW()->getSize().y), NULL);
	glDisable(GL_BLEND);	

	if(DEVMODE==true)
		uiManager->Render();

	if(transition==T_FADEOUT && transition_color==0.0 && gotovo==false)
	{
		gotovo=true;	
		if(levelCompleted==true || player->JeUnisten()==true)
			odabir_levela_odmah=true;
		else
			odabir_levela_odmah=false;		
		gotovo=true;
	}
}


void GameState::RenderObjects(unsigned char stationary) 
{	
	for(int i=0; i<things.size(); i++)
		things[i]->Render(stationary);
	for(int i=0; i<mobs.size(); i++)
		mobs[i]->Render(stationary);
	player->Render(stationary);
	for(int i=0; i<missiles.size(); i++)
		missiles[i]->Render(stationary);
	for(int i=0; i<particles.size(); i++)	
		particles[i]->Render(stationary);		
}
void GameState::RenderGeometry()
{		
    int kx1=camera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=camera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blocks[i][j].Render();
	}
}
void GameState::RenderGeometryNormal()
{		
    int kx1=camera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=camera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blocks[i][j].RenderNormal();
	}	
}
void GameState::RenderGeometryGlow()
{		
    int kx1=camera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=camera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blocks[i][j].RenderGlow();
	}	
}

