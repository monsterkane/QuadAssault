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

#include "GUI_Functions.h"

GlavnoStanje* extStanje;

///POSTAVLJANJE SVJETLA - GUMB FUNKCIJA
void PosSvjetGUI()
{
	extStanje->PostaviSvjetlo();
}
void PosTrigGUI()
{
	extStanje->PostaviMobTrigger();
}
void GlavnoStanje::PostaviSvjetlo()
{
	if(postavljaSvjetlo==false)
	{
		postavljaSvjetlo=true;
		postavljenoSvjetlo=DodajSvjetlo(true);
		postavljenoSvjetlo->Init(mis, 128, this);
		postavljenoSvjetlo->Postavke(Vec3(1.0, 1.0, 1.0), 8);
	}
}
void GlavnoStanje::PostaviMobTrigger()
{
	if(postavljaMobTrigger==0)
	{		
		postavljaMobTrigger=1;		
		triggeri.push_back(new Trigger());	
	}
}

///GENERIRANJE PRAzNOG LEVELA FUNKCIJA
void GenPrazniLevelGUI()
{
	extStanje->GenerirajPrazanLevel();
}

void SpremiLevelGUI()
{
	extStanje->SpremiBlokove();
}
