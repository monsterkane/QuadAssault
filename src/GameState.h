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

#ifndef GS_H
#define GS_H
#include "State.h"
#include "Block.h"
#include "Projectile.h"
#include "TextureManager.h"
#include "UI_Menager.h"
#include "Player.h"
#include "Explosion.h"
#include "Mob.h"
#include "LaserMob1.h"
#include "PlasmaMob1.h"
#include "MinigunMob1.h"
#include "Particle.h"
#include "Trigger.h"
#include "Thing.h"
#include "WeaponPickup.h"
#include "SoundManager.h"
#include "Message.h"
#include "MenuState.h"

class GlavnoStanje : public Stanje
{
private:

	bool DEVMODE;
	
	Svjetlo* postavljenoSvjetlo;
	float sr,sg,sb, si, srad; //color mounted lights

	int PostavljanjeBloka; //types of blocks which are set
	bool postavljaSvjetlo;

	unsigned char postavljaMobTrigger;	
	Trigger* postavljeniTrigger;
	Vec2 t1, t2, t3; //beginning, end and spawnpoint trigger

	unsigned char** maps;
	Block** blokovi;

	float gameOverTimer; //until reaches zero, the game goes to the main menu
	bool nivoZavrsen;

	Igrac* igrac;

	vector<Projektil*> projektili;
	vector<Explosion*> explozije;	
	vector<Svjetlo*> svjetla;
	vector<Shader*> shaderi;
	vector<Mob*> mobovi;	

	UI_Menager* uim;

	ManagerTextura* mt;
	ManagerZvuka* mz;

	Objekt* kamera;
	Vec2 mis;

	GLuint fbo, fbo_rb;	
	
	GLuint lightmapa;
	GLuint normalmapa;
	GLuint geometrija;
	Vec3 ambijentnoSvjetlo;
	
	sf::Music muzika;

	vector<Cestica*> cestice;
	vector<Trigger*> triggeri;
	vector<Stvar*> stvari;
	vector<sf::Sound*> zvukovi;
	vector<sf::Font> fontovi;
	vector<Poruka*> poruke;

	unsigned char tranzicija; //prelazak na tamno (fade to black, ne znak kak se to zove na hrvatskom)
	float tBoja; //boja tranzicije
	float brzinaFadeanja;

public:
	bool Init(Game* igra);
	void Input();
	void Update(float deltaT);	
	void UpdateDev(float deltaT);
	void Render();
	void Izlaz();	

	bool PostaviFBO();
	void IzbrisiFBO();

	void UcitajMapu();
	void InitBlokove();
	void SpremiBlokove();
	Mob* SpawnajMobPremaImenu(string ime);

	void UpdateajNizove(float deltaT);

	unsigned char** DajMapu();
	Block* DajBlok(short x, short y);	
	Igrac* DajIgraca();
	vector<Mob*>* DajMobove();
	vector<Projektil*>* DajProjektile();
	vector<sf::Font>* DajFontove();

	Svjetlo* DodajSvjetlo(bool staticno);
	Explosion* DodajExploziju();
	Projektil* DodajProjektil(Projektil* p);
	Cestica* DodajCesticu(Cestica* c);
	sf::Sound* DodajZvuk(sf::Sound* z, Zvuk* zvuk);
	Mob* DodajMoba(Mob* m);
	Poruka* DodajPoruku(Poruka* p);
	Stvar* DodajStvar(Stvar* s);	
	
	void RenderObjekte(unsigned char stil);

	void RenderGeometriju();
	void RenderGeometrijuNormal();
	void RenderGeometrijuGlow();

	void RenderNormalNaFBO();
	void RenderGeometrijuNaFBO();
	void RenderSvjetlostNaFBO();	
	void RenderScenu();	

	void ZavrsiNivo();
	void ObrisiMapu();

	ManagerTextura* DajMT();
	ManagerZvuka* DajMZ();

	///GUI - FUNKCIJE
	void PostaviSvjetlo();
	void PostaviMobTrigger();
	void GenerirajPrazanLevel();
};
#endif
