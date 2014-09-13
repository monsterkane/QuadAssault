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

void GameState::UpdateDev(float deltaT)
{	
    while(igra->GetRW()->pollEvent(event))
	{
        if(event.type==sf::Event::Closed)
			gotovo=true;
        if(event.type==sf::Event::MouseMoved)
		{
            mousePos.x=event.mouseMove.x;
            mousePos.y=event.mouseMove.y;
		}

        if(event.type==sf::Event::MouseButtonPressed)
		{
            if(event.mouseButton.button==sf::Mouse::Left)
			{
                uiManager->LijeviKlik(mousePos);
                if(lightSet==true)
				{
                    lightSet=false;
				}
                if(mobTriggerSet==3)
				{
                    trigger_spawn=mousePos+camera->DajPoz();
                    Mob* m=SpawnMobByName("lasermob1");
                    triggers.back()->InitMob(trigger_begin,trigger_end,trigger_spawn,m,this);
                    mobTriggerSet=0;
				}
                if(mobTriggerSet==2)
				{
                    trigger_end=mousePos+camera->DajPoz();
                    mobTriggerSet=3;
				}
                if(mobTriggerSet==1)
				{
                    trigger_begin=mousePos+camera->DajPoz();
                    mobTriggerSet=2;
				}

			}			
            if(event.mouseButton.button==sf::Mouse::Right)
			{					
                map[(int)(camera->DajPoz().x+mousePos.x)/BLOCK_SIZE][(int)(camera->DajPoz().y+mousePos.y)/BLOCK_SIZE]=blockType;
                InitBlocks();
			}
		}
        if(event.type==sf::Event::MouseButtonReleased)
		{
            if(event.mouseButton.button==sf::Mouse::Left)
			{
                uiManager->LijeviOtpust(mousePos);
			}
		}
        if(event.type==sf::Event::KeyPressed)
		{		
            if(event.key.code==sf::Keyboard::F1)
				DEVMODE=false;
            if(event.key.code==sf::Keyboard::F4)
			{
                if(ambientLight.x==0.1f)
                    ambientLight=Vec3(0.8f, 0.8f, 0.8f);
				else
                    ambientLight=Vec3(0.1f, 0.1f, 0.1f);

			}
            if(event.key.code==sf::Keyboard::F6)
			{
                SaveBlocks();
                cout << "MAP SAVED." << endl;
			}
            if(event.key.code==sf::Keyboard::G)
			{				
                cout << "X: " << camera->DajPoz().x+mousePos.x << endl;
                cout << "Y: " << camera->DajPoz().y+mousePos.y << endl;
			}
            if(event.key.code==sf::Keyboard::Num1)
                blockType=FLOOR;
            if(event.key.code==sf::Keyboard::Num2)
                blockType=WALL;
            if(event.key.code==sf::Keyboard::Num3)
                blockType=EMPTY;
            if(event.key.code==sf::Keyboard::Num4)
                blockType=RED_DOOR;
            if(event.key.code==sf::Keyboard::Num5)
                blockType=GREEN_DOOR;
            if(event.key.code==sf::Keyboard::Num6)
                blockType=BLUE_DOOR;
			
		}
	}	
    if(lightSet==true)
	{
		light->radius=light_radius;
        light->Postavke(Vec3(light_red,light_green,light_blue),light_intensity);
        light->PromijeniPoz(mousePos+camera->DajPoz());
	}

    uiManager->Update(deltaT, mousePos);
}
void GameState::SaveBlocks()
{
    ofstream of(nivo_datoteka_g.c_str());
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
        of << "blok " << i*BLOCK_SIZE << " " << j*BLOCK_SIZE << " " << (int)map[i][j] << "\n";
	}
    for(int i=0; i<lights.size(); i++)
	{
        if(lights[i]->staticno==true)
		{
        of << "svjetlo " << lights[i]->DajPoz().x << " " << lights[i]->DajPoz().y
            << " " << lights[i]->radius << " " << lights[i]->intenzitet << " " << lights[i]->boja.x << " " << lights[i]->boja.y <<
            " " << lights[i]->boja.z << "\n";
		}
	}
	of.close ();
}

