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

void MenuStanje::Update(float deltaT)
{
    while(igra->GetRW()->pollEvent(event))
	{
        if(event.type==sf::Event::Closed)
			gotovo=true;
        if(event.type==sf::Event::KeyPressed)
		{
            if(event.key.code==sf::Keyboard::Escape)
			{
				if(stanje==GLAVNI_MENU)
					gotovo=true;
				else
					stanje=GLAVNI_MENU;
			}
		}
        if(event.type==sf::Event::MouseButtonReleased)
		{
            if(event.mouseButton.button==sf::Mouse::Left)
				misOtpusten=true;
		}
        if(event.type==sf::Event::MouseMoved)
		{
            mis.x=event.mouseMove.x;
            mis.y=event.mouseMove.y;
		}		
	}	
	
	if(tranzicija==T_FADEIN)
	{
		tBoja+=brzinaFadeanja*deltaT;
		if(tBoja>1.0f)
		{
			tranzicija=T_NEMA;
			tBoja=1.0f;
		}
	}
	if(tranzicija==T_FADEOUT)
	{
		tBoja-=brzinaFadeanja*deltaT;
		if(tBoja<0.0f)
		{
			tBoja=0.0f;
		}
	}	
	
	if(tranzicija==T_NEMA)
	{
		if(stanje==GLAVNI_MENU)
		{
			startGumb.Update(deltaT);
			oigriGumb.Update(deltaT);
			izlazGumb.Update(deltaT);	
		}
		if(stanje==NIVO_ODABIR)
		{
			natragGumb.Update(deltaT);
			for(int i=0; i<nivoi.size(); i++)
				nivoi[i].gumb.Update(deltaT);
		}
		if(stanje==O_IGRI)		
			natragGumb.Update(deltaT);
	}	
}

Vec2 MenuStanje::DajMis()
{
	return mis;
}
