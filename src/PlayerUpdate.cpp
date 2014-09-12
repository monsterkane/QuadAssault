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

#include "Player.h"
#include "Box.h"
#include "GameState.h"
#include "Laser.h"
#include "Plasma.h"
#include "Light.h"

void Igrac::Update(float deltaT, Vec2 mis)
{
	if(unisten==false)
	{
		Vec2 moment;
		moment.x=cos((rotacija-90)/180.0*3.14)*akceleracija;
		moment.y=sin((rotacija-90)/180.0*3.14)*akceleracija;	

		poz.y+=moment.y*brzina*deltaT;
		if(ProvjeraSudara())
			poz.y-=moment.y*brzina*deltaT;
		poz.x+=moment.x*brzina*deltaT;
		if(ProvjeraSudara())
			poz.x-=moment.x*brzina*deltaT;
	
		if(moment.x!=0 || moment.y!=0)
		{
			if(akceleracija>0)
				pomak_tracnica+=deltaT;
			else
				pomak_tracnica-=deltaT;
			if(pomak_tracnica>1.0)
				pomak_tracnica=0.0;
			if(pomak_tracnica<0.0)
				pomak_tracnica=1.0;
		}
		akceleracija=0;

		SudarProjektila();

		rotacijaTorza=atan2((mis.y-poz.y-dim.y/2),(mis.x-poz.x-dim.x/2))*180/3.14;

		for(int i=0; i<4; i++)
		{
			if(unisten==false)
				if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
					oruzja[i]->Update(deltaT);
		}

		UpdateFarove();

		if(puca==false)
		{
			if(energija<100.0)
				energija+=10*deltaT;
			if(energija>100.0)
				energija=100.0;		
		}
		else
			puca=false;

		if(hp<=0.0)
		{
			hp=0.0;
			unisten=true;
			
			Explosion* e=stanje->DodajExploziju();
			e->Init(DajSredinu(),512,stanje);
			e->Setup(256,3000,200);

			sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
				stanje->DajMZ()->DajZvuk("../data/Zvukovi/explozija1.wav"));		
            z->play();

			gameOverPoruka=new Poruka();
			gameOverPoruka->Init("Base", "All units lost, mission Failed.", 4, "../data/Zvukovi/blip.wav", stanje);
			stanje->DodajPoruku(gameOverPoruka);	

			farovi->Postavke(Vec3(0,0,0), 0);
		}
	}
}
void Igrac::UpdateFarove()
{
	Vec2 smjer;
	smjer.x=cos((rotacijaTorza+180)/180.0*3.14);
	smjer.y=sin((rotacijaTorza+180)/180.0*3.14);	
	smjer.Normaliziraj();	
	farovi->PostavkeKuta(smjer,2);

	Vec2 slot;
	slot.x=cos((rotacijaTorza)/180.0*3.14);
	slot.y=sin((rotacijaTorza)/180.0*3.14);
	slot.Mnozi(34);
	farovi->PromijeniPoz(DajSredinu()+slot);
}
void Igrac::DodajMoment(float x)
{
	akceleracija=x;
}
void Igrac::Rotiraj(float rot)
{
	rotacija+=rot;
	if(rotacija>360.0)
		rotacija=0.1;
	if(rotacija<0.0)
		rotacija=359.9;	
}
