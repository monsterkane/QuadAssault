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

void GlavnoStanje::Izlaz()
{
	IzbrisiFBO();	

	ObrisiMapu();

	for(int i=0; i<shaderi.size(); i++)
		delete shaderi[i];
	shaderi.clear();	
	for(int i=0; i<projektili.size(); i++)
		delete projektili[i];
	projektili.clear();
	for(int i=0; i<mobovi.size(); i++)	
		delete mobovi[i];	
	mobovi.clear();	
	for(int i=0; i<explozije.size(); i++)
		delete explozije[i];
	explozije.clear();
	for(int i=0; i<stvari.size(); i++)
		delete stvari[i];
	stvari.clear();
	for(int i=0; i<triggeri.size(); i++)
		delete triggeri[i];
	triggeri.clear();
	for(int i=0; i<cestice.size(); i++)
		delete cestice[i];
	cestice.clear();
	for(int i=0; i<zvukovi.size(); i++)	
	{
        zvukovi[i]->stop();
		delete zvukovi[i];
	}
	zvukovi.clear();
	for(int i=0; i<svjetla.size(); i++)
		delete svjetla[i];
	svjetla.clear();	

	delete uim;

	for(int i=0; i<poruke.size(); i++)
		delete poruke[i];
	poruke.clear();
	fontovi.clear();	

    muzika.stop();

	delete kamera;
	
	mz->Brisi();
	mt->Brisi();	
	
	delete mz;
	delete mt;	
}

ManagerTextura* GlavnoStanje::DajMT()
{
	return mt;
}
