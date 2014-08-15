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
#include "MenuState.h"

void GlavnoStanje::Input()
{
    static sf::Clock clock;
    float deltaT=clock.restart().asSeconds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		tranzicija=T_FADEOUT;
	
	if(DEVMODE==false)
	{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			igrac->Rotiraj(-150*deltaT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			igrac->Rotiraj(150*deltaT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			igrac->DodajMoment(1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			igrac->DodajMoment(-1);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			igrac->Pucaj(mis+kamera->DajPoz(),deltaT);
	}
	if(DEVMODE==true)
	{
		float speed=250;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			speed=750;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(-speed*deltaT,0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(speed*deltaT,0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(0, -speed*deltaT));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(0, speed*deltaT));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
			sr+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			sr-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
			sg+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
			sg-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
			sb+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
			sb-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			si+=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			si-=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			srad+=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			srad-=50*deltaT;
		if(sr<0.0)
			sr=0.0;
		if(sr>1.0)
			sr=1.0;
		if(sg<0.0)
			sg=0.0;
		if(sg>1.0)
			sg=1.0;
		if(sb<0.0)
			sb=0.0;
		if(sb>1.0)
			sb=1.0;
		if(si<0.0)
			si=0.0;
	}
}
