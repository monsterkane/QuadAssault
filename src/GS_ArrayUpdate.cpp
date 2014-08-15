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

void GlavnoStanje::UpdateajNizove(float deltaT)
{
	for(int i=0; i<projektili.size(); i++)
	{
		projektili[i]->Update(deltaT);
        if(projektili[i]->unisten==true)
		{
			projektili[i]->Unisti();
			delete projektili[i];
			projektili.erase(projektili.begin()+i);
		}
	}	
	for(int i=0; i<explozije.size(); i++)
	{
		explozije[i]->Update(deltaT);
        if(explozije[i]->destroyed==true)
		{
			delete explozije[i];
			explozije.erase(explozije.begin()+i);
		}
	}
	for(int i=0; i<mobovi.size(); i++)
	{
		mobovi[i]->Update(deltaT);
        if(mobovi[i]->unisten==true)
		{
			mobovi[i]->Unisti();
			delete mobovi[i];
			mobovi.erase(mobovi.begin()+i);
		}
	}
	for(int i=0; i<cestice.size(); i++)
	{
		cestice[i]->Update(deltaT);
        if(cestice[i]->unisten==true)
		{
			delete cestice[i];
			cestice.erase(cestice.begin()+i);
		}
	}
	for(int i=0; i<triggeri.size(); i++)
	{
		triggeri[i]->Update(deltaT);
		if(triggeri[i]->status==DEAKTIVIRAN)
		{
			delete triggeri[i];
			triggeri.erase(triggeri.begin()+i);
		}
	}
	for(int i=0; i<stvari.size(); i++)
	{
		stvari[i]->Update(deltaT);
        if(stvari[i]->unisten==true)
		{
			stvari[i]->Unisti();
			delete stvari[i];
			stvari.erase(stvari.begin()+i);			
		}
	}
	for(int i=0; i<zvukovi.size(); i++)
	{
        if(zvukovi[i]->getStatus()!=sf::Sound::Playing)
		{
			delete zvukovi[i];
			zvukovi.erase(zvukovi.begin()+i);				
		}
	}	
	if(poruke.size()!=0)
	{
		poruke[0]->Update(deltaT);
        if(poruke[0]->unisten==true)
		{
			delete poruke[0];
			poruke.erase(poruke.begin());
		}
	}
}
