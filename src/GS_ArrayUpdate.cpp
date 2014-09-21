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

void GameState::UpdateSequences(float deltaT)
{
	for(int i=0; i<missiles.size(); i++)
	{
		missiles[i]->Update(deltaT);
        if(missiles[i]->unisten==true)
		{
			missiles[i]->Unisti();
			delete missiles[i];
			missiles.erase(missiles.begin()+i);
		}
	}	
	for(int i=0; i<explosions.size(); i++)
	{
		explosions[i]->Update(deltaT);
        if(explosions[i]->destroyed==true)
		{
			delete explosions[i];
			explosions.erase(explosions.begin()+i);
		}
	}
	for(int i=0; i<mobs.size(); i++)
	{
		mobs[i]->Update(deltaT);
        if(mobs[i]->unisten==true)
		{
			mobs[i]->Unisti();
			delete mobs[i];
			mobs.erase(mobs.begin()+i);
		}
	}
	for(int i=0; i<particles.size(); i++)
	{
		particles[i]->Update(deltaT);
        if(particles[i]->unisten==true)
		{
			delete particles[i];
			particles.erase(particles.begin()+i);
		}
	}
	for(int i=0; i<triggers.size(); i++)
	{
		triggers[i]->Update(deltaT);
		if(triggers[i]->status==DEAKTIVIRAN)
		{
			delete triggers[i];
			triggers.erase(triggers.begin()+i);
		}
	}
	for(int i=0; i<things.size(); i++)
	{
		things[i]->Update(deltaT);
        if(things[i]->unisten==true)
		{
			things[i]->Unisti();
			delete things[i];
			things.erase(things.begin()+i);			
		}
	}
	for(int i=0; i<sounds.size(); i++)
	{
        if(sounds[i]->getStatus()!=sf::Sound::Playing)
		{
			delete sounds[i];
			sounds.erase(sounds.begin()+i);				
		}
	}	
	if(messages.size()!=0)
	{
		messages[0]->Update(deltaT);
        if(messages[0]->unisten==true)
		{
			delete messages[0];
			messages.erase(messages.begin());
		}
	}
}
