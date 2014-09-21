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

Svjetlo* GameState::GetLight(bool stationary)
{
	lights.push_back(new Svjetlo());
	lights.back()->staticno=stationary;
	return lights.back();
}
Projektil* GameState::GetProjectile(Projektil* p)
{
	missiles.push_back(p);
	return missiles.back();
}
Explosion* GameState::GetExplosion()
{
	explosions.push_back(new Explosion());
	return explosions.back();
}
Cestica* GameState::GetParticle(Cestica* c)
{
	particles.push_back(c);
	return particles.back();
}
Mob* GameState::GetMob(Mob* m)
{
	mobs.push_back(m);
	return mobs.back();
}
Poruka* GameState::GetMessage(Poruka* m)
{
    messages.push_back(m);
	return messages.back();
}
Stvar* GameState::GetThing(Stvar* t)
{
    things.push_back(t);
	return things.back();
}
sf::Sound* GameState::GetSound(sf::Sound* s, Zvuk* sound)
{
    bool contains=false;
	for(int i=0; i<sounds.size(); i++)
        if(sounds[i]->getBuffer()==&sound->buffer)
		{
            contains=true;
            delete s;
            s=sounds[i];
            s->stop();
			break;
		}
    if(contains==false)
	{		
        sounds.push_back(s);
        sounds.back()->setBuffer(sound->buffer);
		return sounds.back();
	}
    if(contains==true)
        return s;
}
Igrac* GameState::GetPlayer()
{
	return player;
}
vector<Mob*>* GameState::GetMobs()
{
	return &mobs;
}
vector<Projektil*>* GameState::GetProjectiles()
{
	return &missiles;
}
unsigned char** GameState::GetMap()
{
	return map;
}
ManagerZvuka* GameState::GetSM()
{
	return soundManager;
}
vector<sf::Font>* GameState::GetFonts()
{
	return &fonts;
}
void GameState::CompleteLevel()
{
    levelCompleted=true;
}
