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

#ifndef IGRAC_H
#define IGRAC_H
#include "Object.h"
#include "Block.h"
#include "Weapon.h"
#include "Message.h"

class GlavnoStanje;
class Svjetlo;

class Igrac : public Objekt
{
private:		
	float brzina; //najveca moguca brzina kretanja	

	bool unisten;

	float akceleracija;

	float rotacijaTorza;
	float rotacija;

	float hp; //zdravlje	
	float energija; //za pucanje

	Oruzje* oruzja[4];
	bool oruzjeSlot[4];
	bool puca; //je li pucanje u tijeku

	Svjetlo* farovi;

	GLuint textura, texturaN;

	GLuint tracnica_tex, tracnica_normal;
	GLuint podloga_tex, podloga_normal;

	GlavnoStanje* stanje;

	float pomak_tracnica;

	unsigned char** mapa;

public:
	Igrac();
	~Igrac();
	void Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa);
	void Update(float deltaT, Vec2 mis);
	void UpdateFarove();
	void Render(unsigned char stil);	

	void DodajMoment(float x);
	void Rotiraj(float rot);

	void RenderPodlogu(unsigned char stil);
	void RenderTorzo(unsigned char stil);
	void RenderTracnice(unsigned char stil);
	void RenderOruzje(float x, float y, Oruzje* oruzje, unsigned char stil);

	void RenderHP_Bar();
	void RenderEnergija_Bar();

	void Pucaj(Vec2 misPoz, float deltaT);

	bool ProvjeraSudara();
	void SudarProjektila();
	void PrimiStetu(Projektil* p);

	bool JeUnisten();
	void OduzmiEnergiju(float e);
	void DodajHP(float kolicina);

	void DodajOruzje(Oruzje* o);

	Poruka* gameOverPoruka;
};
#endif
