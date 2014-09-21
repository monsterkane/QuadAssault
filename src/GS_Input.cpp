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

void GameState::Input()
{
    static sf::Clock clock;
    float deltaT=clock.restart().asSeconds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        transition=T_FADEOUT;
	
	if(DEVMODE==false)
	{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player->Rotiraj(-150*deltaT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player->Rotiraj(150*deltaT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player->DodajMoment(1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player->DodajMoment(-1);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            player->Pucaj(mousePos+camera->DajPoz(),deltaT);
	}
	if(DEVMODE==true)
	{
		float speed=250;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			speed=750;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera->PromijeniPoz(camera->DajPoz()+Vec2(-speed*deltaT,0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera->PromijeniPoz(camera->DajPoz()+Vec2(speed*deltaT,0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera->PromijeniPoz(camera->DajPoz()+Vec2(0, -speed*deltaT));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera->PromijeniPoz(camera->DajPoz()+Vec2(0, speed*deltaT));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
			light_red+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			light_red-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
			light_green+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
			light_green-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
			light_blue+=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
			light_blue-=0.5*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
            light_intensity+=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
            light_intensity-=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			light_radius+=50*deltaT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			light_radius-=50*deltaT;
		if(light_red<0.0)
			light_red=0.0;
		if(light_red>1.0)
			light_red=1.0;
		if(light_green<0.0)
			light_green=0.0;
		if(light_green>1.0)
			light_green=1.0;
		if(light_blue<0.0)
			light_blue=0.0;
		if(light_blue>1.0)
			light_blue=1.0;
        if(light_intensity<0.0)
            light_intensity=0.0;
	}
}
