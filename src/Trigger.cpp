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

#include "Trigger.h"
#include "GameState.h"
#include "SharedVariables.h"

void Trigger::InitMob(Vec2 v1, Vec2 v2, Vec2 meta, Mob* mob, GameState* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->meta=meta;
	this->mob=mob;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=MOB;
}
void Trigger::InitPoruka(Vec2 v1, Vec2 v2, Poruka* poruka, GameState* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=PORUKA;
	this->poruka=poruka;	
}
void Trigger::InitKraj(Vec2 v1, Vec2 v2, GameState* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=KRAJ;
}
void Trigger::Update(float deltaT)
{
	if(status==AKTIVIRAN)
	{
		Box k1;
		k1.v1=poz;
		k1.v2=poz+dim;
		Box k2;
		k2.v1=stanje->GetPlayer()->DajPoz();
		k2.v2=stanje->GetPlayer()->DajPoz()+
			stanje->GetPlayer()->DajDim();
		if(k1.Collision(&k2))
		{
			if(tip==MOB)
			{
				stanje->GetMob(mob);
				mob->Init(meta,stanje,stanje->GetMap());
				mob->SpawnEfekt();
			}
			if(tip==PORUKA)
			{
				stanje->GetMessage(poruka);						
			}
			if(tip==KRAJ)
			{
				stanje->CompleteLevel();
				//SPREMANJE INFORMACIJA O OTKLJUCAVANJU				
				if(nivo_trenutni<BROJ_NIVOA-1)
					nivo_omogucen[nivo_trenutni+1]=true;
				
                ofstream of("../data/levelLock.gdf");
				for(int i=0; i<BROJ_NIVOA; i++)
				{
					of << nivo_omogucen[i] << " ";	
				}
				of.close();
				//
			}
			status=DEAKTIVIRAN;
		}		
	}
}
void Trigger::Render()
{
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(poz.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y+dim.y);
	glVertex2f(poz.x, poz.y+dim.y);
	glEnd();
}
