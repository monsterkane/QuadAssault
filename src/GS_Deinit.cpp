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

void GameState::Izlaz()
{
    DeleteFBO();

    DeleteMap();

    for(int i=0; i<shaders.size(); i++)
        delete shaders[i];
    shaders.clear();
    for(int i=0; i<missiles.size(); i++)
        delete missiles[i];
    missiles.clear();
    for(int i=0; i<mobs.size(); i++)
        delete mobs[i];
    mobs.clear();
    for(int i=0; i<explosions.size(); i++)
        delete explosions[i];
    explosions.clear();
    for(int i=0; i<things.size(); i++)
        delete things[i];
    things.clear();
    for(int i=0; i<triggers.size(); i++)
        delete triggers[i];
    triggers.clear();
    for(int i=0; i<particles.size(); i++)
        delete particles[i];
    particles.clear();
    for(int i=0; i<sounds.size(); i++)
	{
        sounds[i]->stop();
        delete sounds[i];
	}
    sounds.clear();
    for(int i=0; i<lights.size(); i++)
        delete lights[i];
    lights.clear();

    delete uiManager;

    for(int i=0; i<messages.size(); i++)
        delete messages[i];
    messages.clear();
    fonts.clear();

    music.stop();

    delete camera;
	
    soundManager->Brisi();
    textureManager->Brisi();
	
    delete soundManager;
    delete textureManager;
}

ManagerTextura* GameState::GetTM()
{
    return textureManager;
}
