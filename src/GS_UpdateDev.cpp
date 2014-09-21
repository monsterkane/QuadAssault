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

void GlavnoStanje::UpdateDev(float deltaT)
{	
    while(igra->GetRW()->pollEvent(event))
	{
        if(event.type==sf::Event::Closed)
			gotovo=true;
        if(event.type==sf::Event::MouseMoved)
		{
            mis.x=event.mouseMove.x;
            mis.y=event.mouseMove.y;
		}

        if(event.type==sf::Event::MouseButtonPressed)
		{
            if(event.mouseButton.button==sf::Mouse::Left)
			{
				uim->LijeviKlik(mis);
				if(postavljaSvjetlo==true)
				{
					postavljaSvjetlo=false;
				}
				if(postavljaMobTrigger==3)
				{
					t3=mis+kamera->DajPoz();
					Mob* m=SpawnajMobPremaImenu("lasermob1");	
					triggeri.back()->InitMob(t1,t2,t3,m,this);
					postavljaMobTrigger=0;
				}
				if(postavljaMobTrigger==2)
				{
					t2=mis+kamera->DajPoz();
					postavljaMobTrigger=3;
				}
				if(postavljaMobTrigger==1)
				{
					t1=mis+kamera->DajPoz();
					postavljaMobTrigger=2;
				}

			}			
            if(event.mouseButton.button==sf::Mouse::Right)
			{					
				maps[(int)(kamera->DajPoz().x+mis.x)/BLOCK_SIZE][(int)(kamera->DajPoz().y+mis.y)/BLOCK_SIZE]=PostavljanjeBloka;
				InitBlokove();
			}
		}
        if(event.type==sf::Event::MouseButtonReleased)
		{
            if(event.mouseButton.button==sf::Mouse::Left)
			{
				uim->LijeviOtpust(mis);
			}
		}
        if(event.type==sf::Event::KeyPressed)
		{		
            if(event.key.code==sf::Keyboard::F1)
				DEVMODE=false;
            if(event.key.code==sf::Keyboard::F4)
			{
				if(ambijentnoSvjetlo.x==0.1f)
					ambijentnoSvjetlo=Vec3(0.8f, 0.8f, 0.8f);
				else
					ambijentnoSvjetlo=Vec3(0.1f, 0.1f, 0.1f);

			}
            if(event.key.code==sf::Keyboard::F6)
			{
				SpremiBlokove();				
				cout << "MAPS SAVED." << endl;
			}
            if(event.key.code==sf::Keyboard::G)
			{				
				cout << "X: " << kamera->DajPoz().x+mis.x << endl;
				cout << "Y: " << kamera->DajPoz().y+mis.y << endl;
			}
            if(event.key.code==sf::Keyboard::Num1)
				PostavljanjeBloka=FLOOR;			
            if(event.key.code==sf::Keyboard::Num2)
				PostavljanjeBloka=WALL;			
            if(event.key.code==sf::Keyboard::Num3)
				PostavljanjeBloka=EMPTY;			
            if(event.key.code==sf::Keyboard::Num4)
				PostavljanjeBloka=RED_DOOR;
            if(event.key.code==sf::Keyboard::Num5)
				PostavljanjeBloka=GREEN_DOOR;
            if(event.key.code==sf::Keyboard::Num6)
				PostavljanjeBloka=BLUE_DOOR;
			
		}
	}	
	if(postavljaSvjetlo==true)
	{
		postavljenoSvjetlo->radius=srad;
		postavljenoSvjetlo->Postavke(Vec3(sr,sg,sb),si);
		postavljenoSvjetlo->PromijeniPoz(mis+kamera->DajPoz());
	}

	uim->Update(deltaT, mis);
}
void GlavnoStanje::SpremiBlokove()
{
    ofstream of(nivo_datoteka_g.c_str());
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
		of << "block " << i*BLOCK_SIZE << " " << j*BLOCK_SIZE << " " << (int)maps[i][j] << "\n";		
	}
	for(int i=0; i<svjetla.size(); i++)
	{
		if(svjetla[i]->staticno==true)
		{
		of << "light " << svjetla[i]->DajPoz().x << " " << svjetla[i]->DajPoz().y 
			<< " " << svjetla[i]->radius << " " << svjetla[i]->intenzitet << " " << svjetla[i]->boja.x << " " << svjetla[i]->boja.y << 
			" " << svjetla[i]->boja.z << "\n";
		}
	}
	of.close ();
}

