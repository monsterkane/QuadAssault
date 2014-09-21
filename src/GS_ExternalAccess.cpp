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

Svjetlo* GlavnoStanje::DodajSvjetlo(bool staticno)
{
	svjetla.push_back(new Svjetlo());
	svjetla.back()->staticno=staticno;
	return svjetla.back();
}
Projektil* GlavnoStanje::DodajProjektil(Projektil* p)
{
	projektili.push_back(p);
	return projektili.back();
}
Explosion* GlavnoStanje::DodajExploziju()
{
	explozije.push_back(new Explosion());
	return explozije.back();
}
Cestica* GlavnoStanje::DodajCesticu(Cestica* c)
{
	cestice.push_back(c);
	return cestice.back();
}
Mob* GlavnoStanje::DodajMoba(Mob* m)
{
	mobovi.push_back(m);
	return mobovi.back();
}
Poruka* GlavnoStanje::DodajPoruku(Poruka* p)
{
	poruke.push_back(p);
	return poruke.back();
}
Stvar* GlavnoStanje::DodajStvar(Stvar* s)
{
	stvari.push_back(s);
	return stvari.back();
}
sf::Sound* GlavnoStanje::DodajZvuk(sf::Sound* z, Zvuk* zvuk)
{
	bool sadrzi=false;
	for(int i=0; i<zvukovi.size(); i++)
        if(zvukovi[i]->getBuffer()==&zvuk->buffer)
		{
			sadrzi=true;
			delete z;
			z=zvukovi[i];
            z->stop();
			break;
		}
	if(sadrzi==false)
	{		
		zvukovi.push_back(z);		
        zvukovi.back()->setBuffer(zvuk->buffer);
		return zvukovi.back();
	}
	if(sadrzi==true)
		return z;
}
Igrac* GlavnoStanje::DajIgraca()
{
	return igrac;
}
vector<Mob*>* GlavnoStanje::DajMobove()
{
	return &mobovi;
}
vector<Projektil*>* GlavnoStanje::DajProjektile()
{
	return &projektili;
}
unsigned char** GlavnoStanje::DajMapu()
{
	return maps;
}
ManagerZvuka* GlavnoStanje::DajMZ()
{
	return mz;
}
vector<sf::Font>* GlavnoStanje::DajFontove()
{
	return &fontovi;
}
void GlavnoStanje::ZavrsiNivo()
{
	nivoZavrsen=true;
}
