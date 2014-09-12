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
#include "SharedVariables.h"

bool MenuStanje::Init(Game* igra)
{
	this->igra=igra;
	gotovo=false;	

	mt=new ManagerTextura();
    mt->UcitajTexturu("../data/kurzor.tga");
    mt->UcitajTexturu("../data/Menu1.tga");
    mt->UcitajTexturu("../data/MenuLoading1.tga");
	
	fontovi.push_back(sf::Font());
    fontovi.back().loadFromFile("../data/DijalogFont.TTF");

	Vec2 poz;
    sf::Vector2u window_size = igra->GetRW()->getSize();

    poz.x=window_size.x/2 - 224;
    poz.y=window_size.y/2 + window_size.y/8;
	startGumb.Init(Vec2(poz.x, poz.y), Vec2(128, 64), "Start", fontovi[0], true, this);
	oigriGumb.Init(Vec2(poz.x+128+32, poz.y), Vec2(128, 64), "About", fontovi[0], true, this);
	izlazGumb.Init(Vec2(poz.x+256+64, poz.y), Vec2(128, 64), "Exit", fontovi[0], true, this);

    natragGumb.Init(Vec2(32, window_size.y-96), Vec2(128, 64), "Back", fontovi[0], true, this);

	mapa_offs=Vec2(0,0);

	updateanoJednom=false;
	misOtpusten=false;

	tranzicija=T_FADEIN;
	tBoja=0.0f;
	brzinaFadeanja=1;	

	stanje=GLAVNI_MENU;

	igra->GetRW()->pushGLStates();	
        oigriText.setFont(fontovi[0]);
        oigriText.setColor(sf::Color(50,255,25));
        oigriText.setCharacterSize(30);
		string text="";
		text+="QuadAssault v1.0\n";
		text+="----------------\n";
		text+="You control a tank which in itself can handle various weapons.\n";		
		text+="Movement: W or up arrow, down arrow or S\n";		
		text+="Revolution: A or left arrow, right arrow or D\n";		
		text+="Shooting: Left mouse button\n";		
		text+="---------------------\n";
		text+="Made by Marko Stanic, 4.A-2\n";
		text+="Supervisor: Dario Jembrek, prof.\n";
		text+="Trade schools Koprivnica\n";
		text+="---------------------\n";
		text+="Contact :\n";
		text+="Mail/MSN : mstani19@gmail.com\n";
		text+="Blog : staniks.blogspot.com\n";
		text+="Youtube : www.youtube.com/geomancer120\n";
		text+="\n";
		text+="The game is written in C++, using Microsoft Visual Studio IDE-a.\n";
		text+="The game uses a library of functions and classes OpenGL and SFML, and shaders is\n";
		text+="koristen scripting language GLSL. Not used outside engine, but it was written\n";
		text+="own, special to the game.\n";
        oigriText.setString(text);
        oigriText.setPosition(32, 32);
	igra->GetRW()->popGLStates();

    ifstream file("../data/nivoLista.gdf",ios::in);
	string linija;
	while(getline(file,linija))
	{
		istringstream lstring(linija,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{
			if(vrijednost=="[NIVO]")
			{				
				nivoi.push_back(Nivo());
			}
			if(vrijednost=="datoteka")
			{
				getline(lstring,vrijednost,' ');
                nivoi.back().datoteka="../data/"+vrijednost;
			}
			if(vrijednost=="datoteka_g")
			{
				getline(lstring,vrijednost,' ');
                nivoi.back().datoteka_g="../data/"+vrijednost;
			}
		}
        ;
	}
	file.close();
	if(odabir_levela_odmah==NULL)
		odabir_levela_odmah=false;
	if(odabir_levela_odmah==true)
		stanje=NIVO_ODABIR;
    ifstream in("../data/nivoLock.gdf");
	for(int i=0; i<BROJ_NIVOA; i++)
	{
		in >> nivo_omogucen[i];	
	}
	in.close();
	for(int i=0; i<nivoi.size(); i++)
	{		
        string text="Mission ";
        std::stringstream parser;
        parser << i+1;
        text += parser.str();
        parser.str("");
        parser.clear();
		
        nivoi[i].gumb.Init(Vec2(window_size.x/2-64, 64+i*96),
			Vec2(128,64), text, fontovi[0], nivo_omogucen[i], this);
	}

    return true;
}
