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
#include "Box.h"

void MenuStanje::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();	

    sf::Vector2u windows_size = igra->GetRW()->getSize();
	if(stanje==GLAVNI_MENU)
    {
        Sprite(Vec2(0.0, 0.0), Vec2(windows_size.x, windows_size.y), mt->DajTexturu(1)->id);
		startGumb.Render(fontovi[0]);
		oigriGumb.Render(fontovi[0]);
		izlazGumb.Render(fontovi[0]);
	}

	if(stanje==NIVO_ODABIR)
	{
        Sprite(Vec2(0.0, 0.0), Vec2(windows_size.x, windows_size.y), mt->DajTexturu(2)->id);
		natragGumb.Render(fontovi[0]);
		for(int i=0; i<nivoi.size(); i++)
			nivoi[i].gumb.Render(fontovi[0]);
	}
	if(stanje==O_IGRI)		
	{
        Sprite(Vec2(0.0, 0.0), Vec2(windows_size.x, windows_size.y), mt->DajTexturu(2)->id);
		natragGumb.Render(fontovi[0]);

        igra->GetRW()->pushGLStates();
            igra->GetRW()->draw(oigriText);
        igra->GetRW()->popGLStates();
	}	

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Sprite(mis-Vec2(16,16),Vec2(32,32),mt->DajTexturu(0)->id);
	
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(tBoja, tBoja, tBoja);
    Sprite(Vec2(0.0, 0.0), Vec2(windows_size.x, windows_size.y), NULL);

	glDisable(GL_BLEND);

	if(tranzicija==T_FADEOUT && tBoja==0.0 && gotovo==false)
	{
		gotovo=true;			
	}
}

void MenuStanje::RenderLoading()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();

    sf::Vector2u windows_size = igra->GetRW()->getSize();
    Sprite(Vec2(0.0, 0.0), Vec2(windows_size.x, windows_size.y),mt->DajTexturu(2)->id);

    igra->GetRW()->pushGLStates();
	sf::Text t;
    t.setFont(fontovi[0]);
    t.setColor(sf::Color(50,255,50));
    t.setCharacterSize(35);
    t.setString("Loading Data...");
    t.setPosition(windows_size.x/2-t.getLocalBounds().width/2,
                  windows_size.y/2-t.getLocalBounds().height/2);
    igra->GetRW()->draw(t);
    igra->GetRW()->popGLStates();

    igra->GetRW()->display();
}
