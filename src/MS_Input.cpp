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

#include "MenuState.h"
#include "Game.h"
#include "GameState.h"
#include "SharedVariables.h"

void MenuStanje::Input()
{
    static sf::Clock clock;
    float deltaT=clock.restart().asSeconds();
	
	if(tranzicija==T_NEMA)
	{
		if(stanje==GLAVNI_MENU)
		{
			if(misOtpusten==true)
			{
				if(startGumb.odabran==true)
				{						
					stanje=NIVO_ODABIR;
				}
				if(oigriGumb.odabran==true)
				{					
					stanje=O_IGRI;
				}
				if(izlazGumb.odabran==true)
				{
					tranzicija=T_FADEOUT;			
				}
				misOtpusten=false;
			}
		}
		if(stanje==NIVO_ODABIR)
		if(misOtpusten==true)
		{
			if(natragGumb.odabran==true)
				stanje=GLAVNI_MENU;
			for(int i=0; i<nivoi.size(); i++)
			{
				if(nivoi[i].gumb.odabran==true)
				{
					RenderLoading();
					nivo_datoteka=nivoi[i].datoteka;
					nivo_datoteka_g=nivoi[i].datoteka_g;
					nivo_trenutni=i;
					igra->SetState(new GlavnoStanje(), true);
					break;
				}
			}
			misOtpusten=false;
		}
		if(stanje==O_IGRI)
		if(misOtpusten==true)
		{
			if(natragGumb.odabran==true)
				stanje=GLAVNI_MENU;
		}
	}
	misOtpusten=false;	
}
