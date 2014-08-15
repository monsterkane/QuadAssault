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

void GlavnoStanje::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();

	RenderSvjetlostNaFBO();	
	RenderGeometrijuNaFBO();	

	RenderScenu();	
	
	if(poruke.size()!=0)
		poruke[0]->RenderOkvir();
	if(poruke.size()!=0)
		poruke[0]->Render();	

	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Sprite(mis-Vec2(16,16),Vec2(32,32),mt->DajTexturu(0)->id);
	glDisable(GL_BLEND);

	glPushMatrix();
    glTranslatef(32, igra->GetRW()->getSize().y-32, 0);
	igrac->RenderHP_Bar();
	glPopMatrix();	

	glPushMatrix();
    glTranslatef(igra->GetRW()->getSize().x-232, igra->GetRW()->getSize().y-32, 0);
	igrac->RenderEnergija_Bar();
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(tBoja, tBoja, tBoja);
    Sprite(Vec2(0.0, 0.0), Vec2(igra->GetRW()->getSize().x, igra->GetRW()->getSize().y), NULL);
	glDisable(GL_BLEND);	

	if(DEVMODE==true)
		uim->Render();

	if(tranzicija==T_FADEOUT && tBoja==0.0 && gotovo==false)
	{
		gotovo=true;	
		if(nivoZavrsen==true || igrac->JeUnisten()==true)
			odabir_levela_odmah=true;
		else
			odabir_levela_odmah=false;		
		gotovo=true;
	}
}


void GlavnoStanje::RenderObjekte(unsigned char stil) 
{	
	for(int i=0; i<stvari.size(); i++)
		stvari[i]->Render(stil);
	for(int i=0; i<mobovi.size(); i++)
		mobovi[i]->Render(stil);
	igrac->Render(stil);
	for(int i=0; i<projektili.size(); i++)
		projektili[i]->Render(stil);
	for(int i=0; i<cestice.size(); i++)	
		cestice[i]->Render(stil);		
}
void GlavnoStanje::RenderGeometriju()
{		
    int kx1=kamera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=kamera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].Render();
	}
}
void GlavnoStanje::RenderGeometrijuNormal()
{		
    int kx1=kamera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=kamera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].RenderNormal();
	}	
}
void GlavnoStanje::RenderGeometrijuGlow()
{		
    int kx1=kamera->DajPoz().x/BLOCK_SIZE-1;
    int ky1=kamera->DajPoz().y/BLOCK_SIZE-1;
    int kx2=igra->GetRW()->getSize().x/BLOCK_SIZE+2;
    int ky2=igra->GetRW()->getSize().y/BLOCK_SIZE+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].RenderGlow();
	}	
}

