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

#ifndef MS_H
#define MS_H
#include "State.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Vec2.h"
#include "MenuButton.h"

#define T_FADEIN 0 
#define T_FADEOUT 1
#define T_NEMA 2 //stanje izme�u tranzicija

#define GLAVNI_MENU 0
#define O_IGRI 1
#define NIVO_ODABIR 2

struct Nivo
{
	string datoteka;
	string datoteka_g;
	MenuGumb gumb;
};

class MenuStanje : public Stanje
{
private:
	ManagerTextura* mt;	
	
	Vec2 mis;	
	
	vector<sf::Font> fontovi;	
	vector<Nivo> nivoi;

	unsigned char stanje;

	MenuGumb startGumb;
	MenuGumb oigriGumb;
	MenuGumb izlazGumb;
	MenuGumb natragGumb;

	bool misOtpusten;

	Vec2 mapa_offs;

	bool updateanoJednom;

	unsigned char tranzicija; //prelazak na tamno (fade to black, ne znak kak se to zove na hrvatskom)
	float tBoja; //boja tranzicije
	float brzinaFadeanja;

    sf::Text oigriText;
	
public:
	bool Init(Game* igra);
	void Input();
	void Update(float deltaT);	
	void Render();
	void Izlaz();	

	void RenderLoading();

	Vec2 DajMis();
};
#endif
